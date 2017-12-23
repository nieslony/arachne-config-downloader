#!/bin/bash

BUILD=build-win64

mkdir -v build-win64
qmake-qt5 -after -o $BUILD/Makefile.win64 nbproject/qt-Release.pro 
