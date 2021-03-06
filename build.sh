#!/usr/bin/env bash
mkdir build dist
cd build
cmake -GNinja ..
ninja -j8
cp serenelinux-update-wizard ../dist/
lrelease lrelease-qt5 ../serenelinux-update-wizard_ja_JP.ts -qm dist/serenelinux-update-wizard_ja_JP.qm