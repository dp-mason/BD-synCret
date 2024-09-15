git clone git@github.com:extism/extism.git extism && \
cd extism && \
make;
sudo make install DEST=/usr/local;
cd ..;

curl https://get.extism.org/cli | sh;

# Rust Prereqs
sudo apt install pkg-config && \
rustup target add wasm32-unknown-unknown;

# JS Prereqs
curl https://raw.githubusercontent.com/extism/js-pdk/main/install.sh | sh;