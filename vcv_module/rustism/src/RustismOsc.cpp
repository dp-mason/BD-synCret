#include "plugin.hpp"

struct WasmInput
{
	float sample_rate;
    float sample_time;
    int64_t frame;
    float pitch;
    float phase;
};


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

	// TODO: replace absolute file path with output of (asset::plugin(pluginInstance, "res/oscillator.wasm")
	const char *manifest = "{\"wasm\": [{\"path\":\"/home/david/.Rack2/plugins/rustism/res/oscillator.wasm\"}]}";

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
		WasmInput input = WasmInput {
			args.sampleRate,
			args.sampleTime,
			args.frame,
			inputs[PITCH_INPUT].getVoltage(),
			0.f
		};

		int rc = extism_plugin_call(plugin, "rust_wasm_sine",(const uint8_t *)&input, sizeof(args.sampleTime));
		if (rc != EXTISM_SUCCESS) {
			DEBUG("EXTISM PLUGIN CALL FAILURE");
		}
		
		const uint8_t *rust_wasm_out_mem = extism_plugin_output_data(plugin);

		outputs[SINE_OUTPUT].setVoltage(*((float*)(rust_wasm_out_mem)));
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