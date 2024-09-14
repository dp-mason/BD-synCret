/**
 * A simple example of saw wave generator plugin
 */

// ----------EXPOSED TO THE USER (BEGIN)----------
// Phase represents the percentage progress that the wave has made through the wavelength
//  10                          
//    |\    |\    |\    @\    @ 
//    | \   | \   | \   | \   | 
//  --|--@--|--@--|--\--|--\--|--
//    |   \ |   \ |   \ |   \ | 
//    |    \|    \|    \|    \| 
// -10   ▲     ▲        ▲     ▲ 
//       │     │        │     │ 
//      0.5   0.5      0.0   0.0 
//               PHASE

// lfoOne and lfoTwo are the current values (-10 to 10) of two "Low Frequency Oscillators", 
// waves that can be used to change certain factors over time. for example, amplitude. 
// Changing the amplitude would make the wave louder and quieter over time. Think of it like 
// automatically turning a knob up and down according to a slow sine wave.

// "Modulation" is the word typically used to describe these sorts of repeated augmentations 

// PHASE is a global constant in order to allow for smooth pitch modulation (like vibrato) between calls

PHASE = new Float32Array([0.0])

function compute_saw(timeElapsed, freq, lfoOne, lfoTwo) {
  // Any frequency modulation should be done before the phase is calculated
  PHASE[0] = (PHASE[0] + (freq * timeElapsed)) % 1.0; // gets the remainder in order to compute the current phase
  amplitude = (PHASE[0] - 0.5) * -2.0 * lfoOne; // calculates output amplitude of saw from 10 to -10 "modulated" by LFO One
  return amplitude
}
// ----------EXPOSED TO THE USER (END)----------


const OUTBUF_SAMPLES = 256;
// const FLOAT32_BYTES  = 4;
const floatbuf = new Float32Array(OUTBUF_SAMPLES).fill(0.0);
input_buffer = new Float32Array(4).fill(0.0);


function batch_compute_wf() {
  input_buffer = new Float32Array(Host.inputBytes());
  const sample_time = input_buffer[0];
  const freq_hz = input_buffer[1];
  const lfo_one = input_buffer[2];
  const lfo_two = input_buffer[3];
  
  for (let sample = 0; sample < floatbuf.length; sample++) {
    floatbuf[sample] = compute_saw(sample_time, freq_hz, lfo_one, lfo_two);
  }

  Host.outputBytes(floatbuf.buffer);
}

module.exports = { batch_compute_wf };
