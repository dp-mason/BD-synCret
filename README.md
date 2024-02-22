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

TODO:
- Is it actually necessary to provide all input in the form of a string?
- Can extism plugins be used with C++, if so, how?

USEFUL LINKS:
- https://extism.org/docs/quickstart/plugin-quickstart/
- https://github.com/extism/rust-pdk#readme
- https://docs.rs/extism-pdk/latest/extism_pdk/
