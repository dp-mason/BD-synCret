#define EXTISM_IMPLEMENTATION
#include "extism-pdk.h"
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#define INPUT_SIZE 16
#define NUM_SAMPLES 256

static float PHASE = 0.0;

float compute_saw(float timeElapsed, float freq, float lfoOne, float lfoTwo) {
  PHASE = fmod(PHASE + (freq * timeElapsed), 1.0); // gets the remainder in order to compute the current phase  
  float amplitude = (PHASE - 0.5) * -2.0; // calculates output amplitude of saw from 10 to -10 "modulated" by LFO One

  return amplitude * lfoOne;
}

int32_t EXTISM_EXPORTED_FUNCTION(batch_compute_wf) {
  uint64_t inputLen = extism_input_length();
  if (inputLen != INPUT_SIZE) {
    inputLen = INPUT_SIZE;
  }

  // Load input
  static uint8_t inputData[INPUT_SIZE];
  extism_load_input(0, inputData, inputLen);

  float sample_time;
  memcpy(&sample_time, inputData, sizeof(float));
  float freq_hz;
  memcpy(&freq_hz, inputData + 4, sizeof(float));
  float lfo_one;
  memcpy(&lfo_one, inputData + 8, sizeof(float));
  float lfo_two;
  memcpy(&lfo_two, inputData + 12, sizeof(float));

  static uint8_t outputData[NUM_SAMPLES*4];
  for (size_t index = 0; index < NUM_SAMPLES; index = index+1)
  {
    float sample_val = compute_saw(sample_time, freq_hz, lfo_one, lfo_two);
    memcpy(outputData+(index*4), &sample_val, sizeof(float));
  }

  ExtismHandle handle = extism_alloc(NUM_SAMPLES*4);
  extism_store_to_handle(handle, 0, outputData, NUM_SAMPLES*4);

  // Set output
  extism_output_set_from_handle(handle, 0, NUM_SAMPLES*4);
  
  return 0;
}