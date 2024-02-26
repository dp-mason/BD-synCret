#include "plugin.hpp"

struct RustismOsc : Module
{
	enum ParamId
	{
		PITCH_PARAM,
		PARAMS_LEN
	};
	enum InputId
	{
		PITCH_INPUT,
		INPUTS_LEN
	};
	enum OutputId
	{
		SINE_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId
	{
		BLINK_LIGHT,
		LIGHTS_LEN
	};

	RustismOsc()
	{
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(PITCH_PARAM, 0.f, 1.f, 0.f, "");
		configInput(PITCH_INPUT, "");
		configOutput(SINE_OUTPUT, "");
	}

	const char *manifest = "{\"wasm\": [{\"path\":\"/home/david/.Rack2/plugins/rustism/res/oscillator.wasm\"}]}";
	// const char *manifest = "{\"wasm\": [{\"url\": "
    //                        "\"https://github.com/extism/plugins/releases/latest/"
    //                        "download/count_vowels.wasm\"}]}";


	char *errmsg = NULL;
	ExtismPlugin *plugin = extism_plugin_new((const uint8_t *)manifest, strlen(manifest), NULL, 0, true, &errmsg);
	// TODO: not sure why the block below seems to be throwing an error that would suggest that something is 
	// wrong with the line above
	// if(plugin == NULL){
	// 	DEBUG(stderr, "ERROR: %s\n", errmsg);
	// 	extism_plugin_new_error_free(errmsg);
	// 	exit(1);
	// }

	void process(const ProcessArgs &args) override
	{
		// call the wasm function once per second
		//if( args.frame % (int64_t(args.sampleRate)) == 0 ){
		float timeInput = float(args.frame * args.sampleTime)*440.0*2.0;
		// DEBUG("CALLING WASM FUNCTION AT TIME %f", seconds );
		
		int rc = extism_plugin_call(plugin, "rust_wasm_sine",(const uint8_t *)&timeInput, sizeof(args.sampleTime));
		// if (rc == EXTISM_SUCCESS) {
		// 	DEBUG("GOOD");
		// }
		//DEBUG( "PLUGIN INSTALL PATH = %s", manifest );
		// 	fprintf(stderr, "ERROR: %s\n", extism_plugin_error(plugin));
		// 	exit(2);
		// } else {
		//size_t outlen = extism_plugin_output_length(plugin);
		const uint8_t *rust_wasm_out_mem = extism_plugin_output_data(plugin);
		//DEBUG( "FLOAT OUTPUT ROM WASM = %f", *((float*)(rust_wasm_out_mem)));

		outputs[SINE_OUTPUT].setVoltage(*((float*)(rust_wasm_out_mem)) * 10.0);
		//}
	}
};

struct RustismOscWidget : ModuleWidget
{
	RustismOscWidget(RustismOsc *module)
	{
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/RustismOsc.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 46.063)), module, RustismOsc::PITCH_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.24, 77.478)), module, RustismOsc::PITCH_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 108.713)), module, RustismOsc::SINE_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(15.24, 25.81)), module, RustismOsc::BLINK_LIGHT));
	}
};

Model *modelRustismOsc = createModel<RustismOsc, RustismOscWidget>("RustismOsc");