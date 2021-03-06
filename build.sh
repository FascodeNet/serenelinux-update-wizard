#!/usr/bin/env bash
rm -rf build dist
mkdir build dist
cd build
cmake -GNinja ..
cmake --build . --target all
cp serenelinux-update-wizard ../dist/
lrelease-qt5 ../serenelinux-update-wizard_ja_JP.ts -qm ../dist/serenelinux-update-wizard_ja_JP.qm