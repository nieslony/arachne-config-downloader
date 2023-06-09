#!/bin/bash

function log {
    echo
    echo -e "\e[1;33m--- $(date) --- $@ ---\e[0m"
}

SRC_DIR=$( dirname $0 )
QMAKE_FILE="$SRC_DIR/ArachneConfigDownloader.pro"
MINGW_DLL_DIR=/usr/x86_64-w64-mingw32/sys-root/mingw/bin
COMPONENT_INCLUDE=dlls.wxi
COMPONENT_REF_INCLUDE=componentsref.wxi
EXE_FILE=release/ArachneConfigDownloader.exe
MSI_FILE=ArachneConfigDownloader.msi
NO_JOBS=$( cat /proc/cpuinfo | awk 'BEGIN { n=1; } /^processor/ { n++; } END { print n; }' )
VERSION="$( cat $SRC_DIR/*spec | awk '/Version:/ { print $NF; }' )"
NAME="$( cat $SRC_DIR/*spec | awk '/Name:/ { print $NF; }' )"
MSI_GUID="$( uuid )"

log Creating Makefile
mingw64-qmake-qt5 -after \
    CONFIG-=Debug \
    CONFIG+=Release \
    QMAKE_CXX=/usr/bin/x86_64-w64-mingw32-g++ \
    QMAKE_CC=/usr/bin/x86_64-w64-mingw32-gcc \
    $QMAKE_FILE || exit 1

log Build
make -j $NO_JOBS || exit 1

log Find DLL dependencies
LINKED_DLLS=$(
    nm $EXE_FILE |
        awk -v dll_dir=$MINGW_DLL_DIR '/ I .*dll$/ {
            dll = $3;
            sub("_head_", "", dll);
            sub("_dll$", ".dll", dll);
            gsub("_", "?", dll);
            print dll_dir "/" dll; }
            '
)
DEPEND_LINKED_DLLS=$(
    nm $LINKED_DLLS \
    | awk -v dll_dir=$MINGW_DLL_DIR '/ I .*dll$/ {
        dll = $3;
        sub("_head_", "", dll);
        sub("_dll$", ".dll", dll);
        gsub("_", "?", dll);
        print dll_dir "/" dll; }
        ' \
    | sort -u
)

log Copy required DLLs
mkdir -v dlls
for i in $LINKED_DLLS $DEPEND_LINKED_DLLS ; do
    cp -v "$i" dlls
done

log Creating component include
cat <<EOF > $COMPONENT_INCLUDE
<?xml version="1.0" encoding="utf-8"?>
<Include>
EOF

cat <<EOF > $COMPONENT_REF_INCLUDE
<?xml version="1.0" encoding="utf-8"?>
<Include>
EOF

for i in dlls/* ; do
echo Including $i
cat <<EOF >> $COMPONENT_INCLUDE
    <Component Id='$i' Guid="$(uuid)">
        <File Id='$i' Source='$i' KeyPath='yes'/>
    </Component>
EOF

echo "<ComponentRef Id='$i'/>" >> $COMPONENT_REF_INCLUDE
done
cat <<EOF >> $COMPONENT_INCLUDE
</Include>
EOF
cat <<EOF >> $COMPONENT_REF_INCLUDE
</Include>
EOF

log Creating MSI
cat $SRC_DIR/arachnecdl.wxs \
    | sed -e "s/@GUID@/$MSI_GUID/g" -e "s/@NAME@/$NAME/g" -e "s/@VERSION@/$VERSION/g" \
    > arachnecdl_parsed.wxs
wixl --verbose arachnecdl_parsed.wxs --output $MSI_FILE

log MSI info
msiinfo suminfo $MSI_FILE
