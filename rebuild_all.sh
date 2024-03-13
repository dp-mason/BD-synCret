(cd rust_src; ./rebuild.sh;);
cp rust_src/target/wasm32-unknown-unknown/release/oscillator.wasm vcv_module/rustism/res;
(cd vcv_module; ./dev_build_and_install.sh;);
