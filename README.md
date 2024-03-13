# Rustism Osc for VCV Rack

## What? Why?

This is an experiment to see if a VCV Rack plugin can be written in a language other than C++ via Web Assembly with the help of Extism. The idea occurred to me after a very short googling session seemed to suggest almost all audio programming is done in C++. It probably makes sense to program audio in C++ and there is no reason for anyone to switch, but hell, why not investigate ways to inject different languages into C++ infratructure.

## Quick Start

*Maybe you won't be able to tell from the way this is structured, but believe it or not I am a software release engineer by profession*

Download and install all prerequisites:
```
./get_prereqs.sh
```
Build the plugin:
```
./rebuild_all.sh
```

## TODO

WOW, ok, so it looks like this works, there are a good number of things that need to be done before I share this more widely:
- after reorganization, change the makefile or something so that the wasm module gets rebuilt when the rust source changes
- make it so that the rust code can accept v/oct input and proper time information and produces voltages -10.0 to 10.0 so proper tuned waves can be played/generated. make the process function in c++ vcv module do as little as possible simply handing off the values to Rust

## Appendix

USEFUL LINKS:
- https://extism.org/docs/quickstart/plugin-quickstart/
- https://github.com/extism/rust-pdk#readme
- https://docs.rs/extism-pdk/latest/extism_pdk/
- https://community.vcvrack.com/t/getting-loaded-plugin-path/10543
- https://docs.rs/extism/latest/extism/trait.FromBytesOwned.html
- https://docs.rs/extism/latest/extism/all.html#traits
- https://www.metricpanda.com/rival-fortress-update-35-avoiding-automatic-structure-padding-in-c/