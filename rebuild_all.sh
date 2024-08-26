(cd templates/rust_src; ./rebuild.sh;);
cp templates/rust_src/target/wasm32-unknown-unknown/release/oscillator.wasm vcv_module/res;

(cd templates/rust_template; ./rebuild.sh;);
cp templates/rust_template/target/wasm32-unknown-unknown/release/rust_template.wasm vcv_module/res;

(cd vcv_module; ./dev_build_and_install.sh;);
