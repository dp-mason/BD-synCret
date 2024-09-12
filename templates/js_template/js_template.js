/**
 * A simple example of saw wave generator plugin
 */

// ----------EXPOSED TO THE USER (BEGIN)----------
// Phase represents the percentage progress that the wave has made through the wavelength
//  10                          
//    |\    |\    |\    |\    | 
//    | \   | \   | \   | \   | 
//  --|--\--|--\--|--\--|--\--| 
//    |   \ |   \ |   \ |   \ | 
//    |    \|    \|    \|    \| 
// -10   ▲     ▲        ▲     ▲ 
//       │     │        │     │ 
//      0.5   0.5      0.0   0.0 
//               PHASE

// lfoOne and lfoTwo are the current values (-10 to 10) of two "Low Frequency Oscillators", 
// waves that can be used to change certain factors over time. for example, amplitude. 
// Changing the amplitude would make the wave loader and quieter over time. Think of it like 
// automatically turning a knob up and down according to a slow sine wave.

function compute_saw(timeElapsed, freq, lfoOne, lfoTwo) {
  phase = (freq * timeElapsed) % 1.0;   // gets the remainder in order to compute the current phase
  return (phase - 0.5) * -2.0 * lfoOne; // returns output amplitude from 10 to -10 "modulated" by LFO One
}
// ----------EXPOSED TO THE USER (END)----------


const OUTBUF_SAMPLES = 256;
const FLOAT32_BYTES  = 4;
// const floatbuf = new Float32Array(128).fill(0.0);
// const input_buffer = new ArrayBuffer(8).fill(0.0);
const timeElapsed = new Float32Array([0.0]);
const floatbuf = new Float32Array(OUTBUF_SAMPLES).fill(0.0);
input_buffer = new Float32Array(2).fill(0.0);


function batch_compute_wf() {
  input_buffer = new Float32Array(Host.inputBytes());
  const sample_time = input_buffer[0];
  const voct_pitch = input_buffer[1];

  
  const freq = 261.6256 * Math.pow(2.0, voct_pitch)
  
  for (let sample = 0; sample < floatbuf.length; sample++) {
    timeElapsed[0] += sample_time;
    floatbuf[sample] = compute_saw(timeElapsed[0], freq, 10.0, 10.0);
    // phase[0] = (phase[0] + (freq * sample_time)) % 1.0;
  }

  Host.outputBytes(floatbuf.buffer);
}

module.exports = { batch_compute_wf };
