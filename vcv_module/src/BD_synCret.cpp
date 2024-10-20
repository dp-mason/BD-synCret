#define CACHESIZE 256

#include "plugin.hpp"
#include "osdialog.h"
#include <patch.hpp>

#pragma pack(1)
struct ProcArgs
{
	float sample_time;
    float freq_hz;
	float lfo_one;
	float lfo_two;
};

struct BD_synCret : Module {

	enum ParamId {
		P0_PARAM,
		P1_PARAM,
		P2_PARAM,
		P3_PARAM,
		P4_PARAM,
		P5_PARAM,
		P6_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		PITCH_INPUT,
		I1_INPUT,
		I2_INPUT,
		I3_INPUT,
		I4_INPUT,
		I5_INPUT,
		I6_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT_L_OUTPUT,
		OUT_R_OUTPUT,
		OUT_2_OUTPUT,
		OUT_3_OUTPUT,
		OUT_4_OUTPUT,
		OUT_5_OUTPUT,
		OUT_6_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	BD_synCret() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(P0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(P1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(P2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(P3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(P4_PARAM, 0.f, 1.f, 0.f, "");
		configParam(P5_PARAM, 0.f, 1.f, 0.f, "");
		configParam(P6_PARAM, 0.f, 1.f, 0.f, "");
		configInput(PITCH_INPUT, "");
		configInput(I1_INPUT, "");
		configInput(I2_INPUT, "");
		configInput(I3_INPUT, "");
		configInput(I4_INPUT, "");
		configInput(I5_INPUT, "");
		configInput(I6_INPUT, "");
		configOutput(OUT_L_OUTPUT, "");
		configOutput(OUT_R_OUTPUT, "");
		configOutput(OUT_2_OUTPUT, "");
		configOutput(OUT_3_OUTPUT, "");
		configOutput(OUT_4_OUTPUT, "");
		configOutput(OUT_5_OUTPUT, "");
		configOutput(OUT_6_OUTPUT, "");
	}

	std::string man_str = "";
	const char *manifest = man_str.c_str();

	char *errmsg = nullptr;
	ExtismPlugin *plugin = nullptr;

	const float* output_buf = nullptr;
	TextDisplay* text_display = nullptr;

	void process(const ProcessArgs& args) override {
		
		// exit early if the plugin has not been set
		if(plugin == nullptr){
			return;
		}

		// Fill the Output buffer with new audio data
		if (args.frame % CACHESIZE == 0) {
			
			const float freq_hz = 261.6256 * std::pow(2.0, inputs[PITCH_INPUT].getVoltage());

			ProcArgs proc_args = ProcArgs{
				args.sampleTime,
				freq_hz,
				inputs[I1_INPUT].isConnected() ? (float)inputs[I1_INPUT].getVoltage() : 1.0f,
				inputs[I2_INPUT].isConnected() ? (float)inputs[I1_INPUT].getVoltage() : 1.0f,
			};

			int rc = extism_plugin_call(plugin, "batch_compute_wf", (const uint8_t*)&proc_args, sizeof(ProcArgs));
			if (rc != EXTISM_SUCCESS) {
				if (plugin == NULL){
					DEBUG("Manifest: %s", manifest);
					DEBUG("ERROR: %s\n", errmsg);
					extism_plugin_new_error_free(errmsg);
					exit(1);
				}
				DEBUG("EXTISM PLUGIN CALL FAILURE: %s", extism_plugin_error(plugin));
			}

			output_buf = (float*)extism_plugin_output_data(plugin);

			if (output_buf == nullptr) {
            	DEBUG("ERROR: Output buffer is NULL");
            	return;
        	}
		}
		
		if (output_buf != nullptr) {
			outputs[OUT_L_OUTPUT].setVoltage(output_buf[args.frame % CACHESIZE]);
			outputs[OUT_R_OUTPUT].setVoltage(output_buf[args.frame % CACHESIZE]);
		}
		else {
			outputs[OUT_L_OUTPUT].setVoltage(-1.0);
			outputs[OUT_R_OUTPUT].setVoltage(-1.0);
		}

		return;
	}

	std::string selectPathVCV()
    {
		std::string proj_path = APP->patch->path.substr(0, APP->patch->path.rfind("/") + 1);

        osdialog_filters* filters = osdialog_filters_parse("WASM:wasm");
        char *filename = osdialog_file(OSDIALOG_OPEN, proj_path.c_str(), NULL, filters);
        osdialog_filters_free(filters);
        std::string filename_string(filename);
		DEBUG("Returning selected path to file: %s", filename_string.c_str());
        return(filename_string);
    }

	void load_wasm_from_path(std::string wasm_path){
		DEBUG("Loading wasm from supplied path");
		this->man_str = std::string("{\"wasm\": [{\"path\":\"" + wasm_path + "\"}]}");
		this->manifest = man_str.c_str();
		this->errmsg = nullptr;
		if (!plugin){
			free(plugin);
			plugin = nullptr;
		}
		DEBUG("New Manifest Contents:\n\n%s\n\n", manifest);
		this->plugin = extism_plugin_new((const uint8_t *)manifest, strlen(manifest), NULL, 0, true, &errmsg);
		DEBUG("Plugin Loaded Successfully");
		std::string label_string = wasm_path.substr(wasm_path.rfind("/") + 1, wasm_path.rfind(".wasm"));
		DEBUG("Label String: %s", label_string.c_str());
		this->text_display->text = label_string.c_str();

		return;
	}
};

// ----- Adapted from VoxGlitch WavBank Source code -----
//    https://github.com/clone45/voxglitch/blob/master/src/WavBank/WavBankWidget.hpp
struct WasmPathItem : MenuItem
{
	BD_synCret *module;

	void onAction(const event::Action &e) override
	{
		// #ifdef USING_CARDINAL_NOT_RACK
		//     WavBank *module = this->module;
		//     async_dialog_filebrowser(false, NULL, module->samples_root_dir.c_str(), "Load sample", [module](char *path) {
		//       if (path) {
		//         if (char *rpath = strrchr(path, CARDINAL_OS_SEP))
		//           *rpath = '\0';
		//         pathSelected(module, path);
		//         free(path);
		//       }
		//     });
		// #else
		pathSelected(module, module->selectPathVCV());
		// #endif
	}

	static void pathSelected(BD_synCret *module, std::string path)
	{
		DEBUG("Path Selected Function");
		if (path != ""){
			module->load_wasm_from_path(path);
		}
	}
};
// ------------------------------------------------------

struct BD_synCretWidget : ModuleWidget {
	BD_synCretWidget(BD_synCret* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/BD_synCret.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 46.063)), module, BD_synCret::P0_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(30.48, 46.243)), module, BD_synCret::P1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(45.72, 46.243)), module, BD_synCret::P2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(60.96, 46.243)), module, BD_synCret::P3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(76.2, 46.243)), module, BD_synCret::P4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(91.44, 46.243)), module, BD_synCret::P5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(106.68, 46.243)), module, BD_synCret::P6_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.24, 77.478)), module, BD_synCret::PITCH_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(30.48, 77.478)), module, BD_synCret::I1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(45.72, 77.478)), module, BD_synCret::I2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(60.96, 77.478)), module, BD_synCret::I3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(76.2, 77.478)), module, BD_synCret::I4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(91.44, 77.478)), module, BD_synCret::I5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(106.68, 77.478)), module, BD_synCret::I6_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 108.713)), module, BD_synCret::OUT_L_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(30.48, 108.713)), module, BD_synCret::OUT_R_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(45.72, 108.713)), module, BD_synCret::OUT_2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(60.96, 108.713)), module, BD_synCret::OUT_3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(76.2, 108.713)), module, BD_synCret::OUT_4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(91.44, 108.713)), module, BD_synCret::OUT_5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(106.68, 108.713)), module, BD_synCret::OUT_6_OUTPUT));

		TextDisplay* text_display = createWidget<TextDisplay>(Vec(RACK_GRID_WIDTH, 100.00));
		addChild(text_display);
		if(module){
			module->text_display = text_display;
		}
		
	}

	void appendContextMenu(Menu *menu) override
    {
		WasmPathItem *set_module_path_entry = new WasmPathItem;
		set_module_path_entry->text = "Set Path to Wasm Module";
		set_module_path_entry->module = dynamic_cast<BD_synCret *>(this->module);
        menu->addChild(set_module_path_entry);
	}
};

Model *modelBD_synCret = createModel<BD_synCret, BD_synCretWidget>("BD_synCret");