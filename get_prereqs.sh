sudo apt install pkg-config;
rustup target add wasm32-unknown-unknown;
curl https://get.extism.org/cli | sh;
git clone git@github.com:extism/extism.git extism;
cd extism;
make;
sudo make install DEST=/usr/local;
cd ..;
