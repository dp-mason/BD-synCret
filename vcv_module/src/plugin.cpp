#include "plugin.hpp"


Plugin* pluginInstance;
extern Model* modelBD_synCret;

void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	p->addModel(modelBD_synCret);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
