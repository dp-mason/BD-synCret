/**
 * A simple example of saw wave generator plugin
 */

const OUTBUF_SAMPLES = 128;
const FLOAT32_BYTES  = 4;

function compute_saw(phase) {
  return (phase - 0.5) * -20.0; // returs output 10 to -10
}

function batch_compute_wf() {
  // const input_buffer = new ArrayBuffer(Host.inputBytes()).buffer;
  // const view = new DataView(input_buffer);
  // const sample_time = view.getFloat32(0, true);
  // const voct_pitch = view.getFloat32(4, true);

  // outbuf = new ArrayBuffer(OUTBUF_SAMPLES * FLOAT32_BYTES);
  floatbuf = new Float32Array(OUTBUF_SAMPLES);
  // phase = 0.0 // TODO: accumulate phase somehow between calls to batch_compute_wf
  // freq = 261.6256 * Math.pow(2.0, voct_pitch)

  for (let sample = 0; sample < floatbuf.length; sample++) {
    // outbuf[sample] = compute_saw(phase);
    floatbuf[sample] = 10.0;
  }

  // Host.outputBytes(buffer)
  Host.outputBytes(floatbuf.buffer);
}

module.exports = { batch_compute_wf };
