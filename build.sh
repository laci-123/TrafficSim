#!/bin/sh

name="trafficsim"

case "$1" in
    "release")
        profile="wasm-release"
        wasm_path="./target/wasm32-unknown-unknown/wasm-release/$name.wasm"
        ;;
    *)
        profile="dev"
        wasm_path="./target/wasm32-unknown-unknown/debug/$name.wasm"
        ;;
esac

set -x

cargo build --target wasm32-unknown-unknown --profile "$profile"
wasm-bindgen --no-typescript --target web --out-dir ./web --out-name "$name" "$wasm_path"
mkdir -p ./web/assets
cp -u ./assets/* ./web/assets/
