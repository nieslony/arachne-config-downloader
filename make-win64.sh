#!/bin/bash

# mingw64-gcc-c++.x86_64

BUILD=build-win64
NAME="Arachne Config Downloader"
VERSION=1.2.3
DEST_DIR="$BUILD/dest/Win64"
NO_JOBS=$( cat /proc/cpuinfo | awk 'BEGIN { n=1; } /^processor/ { n++; } END { print n; }' )
MISSING_DLLS="Qt5Gui Qt5Core Qt5Widgets Qt5Network libgcc_s_seh-1 libstdc++-6 libgcc_s_seh-1 iconv libpcre2-16-0 zlib1 zlib1"
MISSING_DLLS="$MISSING_DLLS libharfbuzz-0 libpng16-16 libwinpthread-1 libglib-2.0-0 libintl-8 libpcre-1"

mkdir -v build-win64
rsync -av src build-win64
cat nbproject/qt-Release.pro \
    | awk '/^QT \+=.* K/ { print ""; next; } { print $0; }' \
    > $BUILD/qt-Release.pro


cat arachnecdl.wxs \
    | sed -e "s/@NAME@/$NAME/g" \
    | sed -e "s/@VERSION@/$VERSION/g" \
    | awk 'function uuid() {
        cmd = "uuidgen"
        cmd | getline ret_uuid ;
        close(cmd);

        return ret_uuid;
    }

    {
        gsub("@GUID@", uuid());
        print $0;
    }' \
    > $BUILD/arachnecdl.wxs

mingw64-qmake-qt5 -after \
    CONFIG-=debug \
    CONFIG+=release \
    DESTDIR=$DEST_DIR \
    OBJECTS_DIR=$BUILD/Release/Win64 \
    MOC_DIR=$BUILD/Release/Win64 \
    QMAKE_CXX=/usr/bin/x86_64-w64-mingw32-g++ \
    QMAKE_CC=/usr/bin/x86_64-w64-mingw32-gcc \
    -o $BUILD/Makefile.win64 $BUILD/qt-Release.pro || exit 1

cd $BUILD
mingw64-make -j$NO_JOBS -f Makefile.win64 || exit 1

wixl -v arachnecdl.wxs
msiinfo suminfo arachnecdl.msi

mkdir -vp dlls
for i in $MISSING_DLLS ; do
    cp -v /usr/x86_64-w64-mingw32/sys-root/mingw/bin/$i.dll dlls
done
cp -v /usr/x86_64-w64-mingw32/sys-root/mingw/lib/qt5/plugins/platforms/qwindows.dll dlls


