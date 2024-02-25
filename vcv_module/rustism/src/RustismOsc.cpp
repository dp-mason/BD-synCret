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

	const char *manifest = "{\"wasm\": [{\"url\": "
						   "\"../../rust_src/target/wasm32-unknown-unknown/debug/oscillator.wasm\"}]}";

	// char *errmsg = NULL;
	// ExtismPlugin *plugin = extism_plugin_new(
	// 	(const uint8_t *)manifest, strlen(manifest), NULL, 0, true, &errmsg);
	// if (plugin == NULL)
	// {
	// 	fprintf(stderr, "ERROR: %s\n", errmsg);
	// 	extism_plugin_new_error_free(errmsg);
	// 	exit(1);
	// }

	void process(const ProcessArgs &args) override
	{
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