/**
 * A simple example of saw wave generator plugin
 */

const OUTBUF_SAMPLES = 256;
const FLOAT32_BYTES  = 4;
// const floatbuf = new Float32Array(128).fill(0.0);
// const input_buffer = new ArrayBuffer(8).fill(0.0);
const phase = new Float32Array([0.0]);
const floatbuf = new Float32Array(OUTBUF_SAMPLES).fill(0.0);
input_buffer = new Float32Array(2).fill(0.0);

function compute_saw(phase) {
  return (phase - 0.5) * -20.0; // returs output 10 to -10
}

function batch_compute_wf() {
  input_buffer = new Float32Array(Host.inputBytes());
  const sample_time = input_buffer[0];
  const voct_pitch = input_buffer[1];

  const freq = 261.6256 * Math.pow(2.0, voct_pitch)

  for (let sample = 0; sample < floatbuf.length; sample++) {
    floatbuf[sample] = compute_saw(phase);
    phase[0] = (phase[0] + (freq * sample_time)) % 1.0;
  }

  Host.outputBytes(floatbuf.buffer);
}

module.exports = { batch_compute_wf };
