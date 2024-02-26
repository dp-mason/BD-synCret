Not much here yet...

Run what little is here with:

```
cargo build --target wasm32-unknown-unknown
```

for smaller exec, compile with ```--release``` flag

test with:

```
extism call target/wasm32-unknown-unknown/debug/my_plugin.wasm greet --input "867.5309"
```

USEFUL LINKS:
- https://extism.org/docs/quickstart/plugin-quickstart/
- https://github.com/extism/rust-pdk#readme
- https://docs.rs/extism-pdk/latest/extism_pdk/
- TODO: ADD MORE OF THE LINKS YOU HAVE BOOKMARKED

WOW, ok, so it looks like this works, there are a good number of things that need to be done before I share thisi:
- fix the path to the wasm module so that it is not an absolute path, there was some trouble with constructing the manifest string
- major restructure to improve the way that everything is organized
- after reorganization, change the makefile or something so that the wasm module gets rebuilt when the rust source changes
- add automation so that .wasm output file that is built gets moved to where it needs to be in the vcv module (make file? script?)
- make it so that the rust code can accept v/oct input and proper time information and produces voltages -10.0 to 10.0 so proper tuned waves can be played/generated. make the process function in c++ vcv module do as little as possible simply handing off the values to Rust
