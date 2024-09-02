use extism_pdk::*;

// TODO: this is bad I think, will not translate well to other templates
static mut PHASE:f32 = 0.0;

const OUTBUF_SAMPLES:usize = 256;
const FLOAT32_BYTES:usize = 4;

// #[derive(serde::Deserialize)]
// #[derive(serde::Deserialize, FromBytes)]
// #[encoding(Json)]
// struct VcvInput {
//     sample_rate: f32,
//     sample_time: f32,
//     frame: i64,
//     pitch: f32,
//     phase: f32
// }

#[plugin_fn]
pub fn batch_compute_wf(input: Vec<u8>) -> FnResult<Vec<u8>> {
    let sample_time: f32 = f32::from_le_bytes(input[0..4].try_into().unwrap());
    let voct_pitch: f32 = f32::from_le_bytes(input[4..8].try_into().unwrap());
    
    let freq: f32 = 261.6256 * f32::powf(2.0, voct_pitch);

    let mut outbuf: Vec<u8> = vec![0; OUTBUF_SAMPLES * FLOAT32_BYTES];

    for index in 0..OUTBUF_SAMPLES {
        // Accumulate the phase
        unsafe {
            // TODO: using this mutable static is bade, remove
            PHASE = (PHASE + (freq * sample_time)).fract();
        }
        // Computes the value of this individual sample and puts it where it belongs in the output buffer
        outbuf[index * FLOAT32_BYTES..index * FLOAT32_BYTES + 4].copy_from_slice(
            &pitched_sine(voct_pitch, freq).unwrap().to_le_bytes(),
        );
    }

    Ok(outbuf)
}

// TODO: this function computes one sample, I would like to test buffering
// the output but this logic should be abstracted away from the single sample calc
//#[plugin_fn]
pub fn pitched_sine(
    voct_pitch:f32,
    freq:f32
) -> FnResult<f32> {
   
    // Compute the frequency from the pitch parameter and input
    // The default frequency is C4 = 261.6256f

    // Compute the sine output
    unsafe{
        // TODO: using this mutable static is bade, remove
        let sine:f32 = f32::sin(2.0 * 3.14159 * PHASE);
        Ok(10.0 * sine)
    }
    
}