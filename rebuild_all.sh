rm vcv_module/res/*.wasm;

(cd templates/rust_template; ./rebuild.sh;);
cp templates/rust_template/target/wasm32-unknown-unknown/release/rust_template.wasm vcv_module/res;

(cd templates/js_template; extism-js -i js_template.d.ts js_template.js -o js_template.wasm;);
cp templates/js_template/js_template.wasm vcv_module/res;

(cd templates/go_template; tinygo build -target wasi -o go_template.wasm .);
cp templates/go_template/go_template.wasm vcv_module/res;

(cd templates/zig_template; zig-build);
cp templates/zig_template/zig-out/bin/plugin.wasm vcv_module/res/zig_template.wasm;

# Use the "clang" that comes with Wasi-SDK package, set it in your $PATH
(cd templates/c_template; clang -o c_template.wasm --target=wasm32-wasi -Wl,--no-entry c_template.c);
cp templates/c_template/c_template.wasm vcv_module/res;

(cd vcv_module; ./dev_build_and_install.sh;);
