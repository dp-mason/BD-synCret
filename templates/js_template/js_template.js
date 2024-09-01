/**
 * A simple example of saw wave generator plugin
 */

const OUTBUF_SAMPLES = 128;
const FLOAT32_BYTES  = 4;

function compute_saw(phase) {
  return (phase - 0.5) * -20.0; // returs output 10 to -10
}

function batch_compute_wf() {
  const input_buffer = new ArrayBuffer(Host.inputBytes()).buffer;
  const view = new DataView(input_buffer);
  const sample_time = view.getFloat32(0, true);
  const voct_pitch = view.getFloat32(4, true);

  outbuf = new ArrayBuffer(OUTBUF_SAMPLES * FLOAT32_BYTES);
  outbuf = new Float32Array(outbuf);
  phase = 0.0 // TODO: accumulate phase somehow between calls to batch_compute_wf
  freq = 261.6256 * Math.pow(2.0, voct_pitch)
  
  for (let sample = 0; sample < outbuf.length; sample++) {
    // outbuf[sample] = compute_saw(phase);
    // phase += (freq * sample_time) % 1;
    outbuf[sample] = 4.0;
  }

  // const arrayBuffer = new ArrayBuffer(512);
  
  // // Create a Uint8Array of size 512
  // const uint8Array = new Uint8Array(arrayBuffer);

  // // Fill the Uint8Array with a specific value, e.g., 255
  // const fillValue = 255; // Choose any value from 0 to 255

  // uint8Array.fill(fillValue);

  Host.outputBytes(new ArrayBuffer(outbuf));
}

module.exports = { batch_compute_wf };
