git clone git@github.com:extism/extism.git extism && \
cd extism && \
make;
sudo make install DEST=/usr/local;
cd ..;

curl https://get.extism.org/cli | sh;

read -p "Would you like to install the Rust PDK? (y/n) " response
# Convert the response to lowercase
response=$(echo "$response" | tr '[:upper:]' '[:lower:]')
if [[ "$response" == "y" || "$response" == "yes" ]]; then
    echo "Install Rust PDK..."
    # Rust Prereqs
    sudo apt install pkg-config && \
    rustup target add wasm32-unknown-unknown;
fi

read -p "Would you like to install the JavaScript PDK? (y/n) " response
# Convert the response to lowercase
response=$(echo "$response" | tr '[:upper:]' '[:lower:]')
if [[ "$response" == "y" || "$response" == "yes" ]]; then
    # JS Prereqs
    curl https://raw.githubusercontent.com/extism/js-pdk/main/install.sh | sh;
fi

read -p "Would you like to install the Go PDK? (y/n) " response
# Convert the response to lowercase
response=$(echo "$response" | tr '[:upper:]' '[:lower:]')
if [[ "$response" == "y" || "$response" == "yes" ]]; then
    # Go Prereqs
    echo "TODO"
fi

read -p "Would you like to install the C Language PDK? (y/n) " response
# Convert the response to lowercase
response=$(echo "$response" | tr '[:upper:]' '[:lower:]')
if [[ "$response" == "y" || "$response" == "yes" ]]; then
    # C Prereqs
    echo "TODO"
fi

read -p "Would you like to install the Zig PDK? (y/n) " response
# Convert the response to lowercase
response=$(echo "$response" | tr '[:upper:]' '[:lower:]')
if [[ "$response" == "y" || "$response" == "yes" ]]; then
    # Zig Prereqs
    echo "TODO"
fi
