#!/bin/bash

VERSION=0.1.0
PACKAGE=ArachneConfigDownloader
PKG_VERSION="$PACKAGE-$VERSION"

git archive \
    --format=tar.gz \
    --prefix $PKG_VERSION/ \
    --output=$PKG_VERSION.tar.gz \
    HEAD
