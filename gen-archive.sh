#!/bin/bash

VERSION=$( awk '/^Version:/ { print $2; }' ArachneConfigDownloader.spec )
PACKAGE=ArachneConfigDownloader
PKG_VERSION="$PACKAGE-$VERSION"
TAR_FILE=$PKG_VERSION.tar.gz

echo Creating ${TAR_FILE}...
git archive \
    --format=tar.gz \
    --prefix $PKG_VERSION/ \
    --output=$PKG_VERSION.tar.gz \
    HEAD
