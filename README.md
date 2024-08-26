# BD-synCret for VCV Rack

An embedded VCV Rack Wasm host powered by Extism 

## What? Why?

This is an experiment to see if a VCV Rack plugin can be written in a language other than C++ via Web Assembly with the help of Extism. The idea occurred to me after a very short googling session seemed to suggest almost all audio programming is done in C++. It probably makes sense to program audio in C++ and there is no reason for anyone to switch, but hell, why not investigate ways to inject different languages into C++ infrastructure.

![Module Panel Design](/vcv_module/res/BD_synCret.svg)

## Quick Start

Currently only tested on linux, but if you'd like to create scripts on your platform that do what the .sh files in here do then it should work for you. If you are non-linux visit the [install page for Extism](https://extism.org/docs/install/) to get started.

Download and install all prerequisites:
```
./get_prereqs.sh
```

Set your Rack User dir if it isn't already in your .bashrc. This is where the dirs that contain your patch files and your plugins live.
```
export RACK_USER_DIR=/home/<user>/.local/share/Rack2
```

Build the plugin:
```
./rebuild_all.sh
```

## TODO

- Implement examples in a couple more languages?
- Implement more complex, varied wave types

## Appendix

USEFUL LINKS:
- https://extism.org/docs/quickstart/plugin-quickstart/
- https://github.com/extism/rust-pdk#readme
- https://docs.rs/extism-pdk/latest/extism_pdk/
- https://community.vcvrack.com/t/getting-loaded-plugin-path/10543
- https://docs.rs/extism/latest/extism/trait.FromBytesOwned.html
- https://docs.rs/extism/latest/extism/all.html#traits
- https://www.metricpanda.com/rival-fortress-update-35-avoiding-automatic-structure-padding-in-c/
