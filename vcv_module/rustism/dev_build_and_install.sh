# Assumes you have your RACK_USER_DIR env set to wherever your ".Rack" folder is
rm -r $RACK_USER_DIR/plugins/*ustism*
make install;
cp -r $RACK_USER_DIR/plugins-lin-x64/*ustism* $RACK_USER_DIR/plugins
