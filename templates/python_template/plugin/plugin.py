import extism  # noqa: F401 # pyright: ignore

from typing import List, Optional

# import extism.runtime
# import extism.wasm  # noqa: F401

PHASE = 0.0

def compute_saw(timeElapsed, freq, lfoOne, lfoTwo):
  # Any frequency modulation should be done before the phase is calculated
  PHASE = (PHASE + (freq * timeElapsed)) % 1.0; # gets the remainder in order to compute the current phase
  amplitude = (PHASE - 0.5) * -2.0 * lfoOne; # calculates output amplitude of saw from 10 to -10 "modulated" by LFO One
  return amplitude

OUTBUF_SAMPLES = 256;
FLOAT32_BYTES  = 4;

@extism.plugin_fn
def batch_compute_wf():
    input_buffer = extism.input_bytes()
    # sample_time = input_buffer[0]
    # freq_hz = input_buffer[1]
    # lfo_one = input_buffer[2]
    # lfo_two = input_buffer[3]

    # for sample in range(0, OUTBUF_SAMPLES) {
    # floatbuf[sample] = compute_saw(sample_time, freq_hz, lfo_one, lfo_two);
    # }

    # Host.outputBytes(floatbuf.buffer);
    return

def batch_compute_wf():
    raise Exception("Unimplemented: batch_compute_wf")
