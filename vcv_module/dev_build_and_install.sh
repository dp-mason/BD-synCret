# Assumes you have your RACK_USER_DIR env set to wherever your ".Rack" folder is
make clean; 
make install;
cp -r $RACK_USER_DIR/plugins-lin-x64/*synCret* $RACK_USER_DIR/plugins;
