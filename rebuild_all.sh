(cd templates/rust_src; ./rebuild.sh;);
cp templates/rust_src/target/wasm32-unknown-unknown/release/oscillator.wasm vcv_module/res;

(cd templates/rust_template; ./rebuild.sh;);
cp templates/rust_template/target/wasm32-unknown-unknown/release/rust_template.wasm vcv_module/res;

(cd templates/js_template; extism-js -i js_template.d.ts js_template.js -o js_template.wasm;);
cp templates/js_template/js_template.wasm vcv_module/res;

(cd templates/go_template; tinygo build -target wasi -o go_template.wasm .);
cp templates/go_template/go_template.wasm vcv_module/res;

(cd templates/zig_template; zig-build);
cp templates/zig_template/zig-out/bin/plugin.wasm vcv_module/res/zig_template.wasm;

(cd vcv_module; ./dev_build_and_install.sh;);
