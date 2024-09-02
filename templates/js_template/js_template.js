/**
 * A simple example of saw wave generator plugin
 */

const OUTBUF_SAMPLES = 128;
const FLOAT32_BYTES  = 4;
const floatbuf = new Float32Array(128).fill(10.0);
phase = 0.0; 

function compute_saw(phase) {
  return (phase - 0.5) * -20.0; // returs output 10 to -10
}

function batch_compute_wf() {
  // const input_buffer = new ArrayBuffer(Host.inputBytes()).buffer;
  // const view = new DataView(input_buffer);
  // const sample_time = view.getFloat32(0, true);
  // const voct_pitch = view.getFloat32(4, true);
  const sample_time = 0.00002272727;
  const voct_pitch = 1.0;

  //phase = 0.0 // TODO: accumulate phase somehow between calls to batch_compute_wf
  freq = 261.6256 * Math.pow(2.0, voct_pitch)

  for (let sample = 0; sample < floatbuf.length; sample++) {
    floatbuf[sample] = compute_saw(phase);
    // //floatbuf[sample] = 3.0;
    phase = (phase + (freq * sample_time)) % 1.0;
    // phase += sample_time;
  }

  

  // Host.outputBytes(buffer)
  Host.outputBytes(floatbuf.buffer);
}

module.exports = { batch_compute_wf };
