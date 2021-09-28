#!/bin/bash

VERSION=$( cat *spec | awk '/Version:/ { print $2; }' )
NAME=$( cat *spec | awk '/Name:/ { print $2; }' )
TAR_FN=$NAME-$VERSION.tar.gz

rm -vf $NAME-*.tar.gz

echo Creating $TAR_FN...
tar -cvzf $TAR_FN \
    --transform=s/^./$NAME-$VERSION/ \
    --owner root --group root \
    ./src \
    ./doc \
    ./icons \
    ./nbproject/qt-Release.pro 
