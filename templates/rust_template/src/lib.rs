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
    let freq_hz: f32 = f32::from_le_bytes(input[4..8].try_into().unwrap());
    let lfo_one: f32 = f32::from_le_bytes(input[8..12].try_into().unwrap());
    let lfo_two: f32 = f32::from_le_bytes(input[12..16].try_into().unwrap());
    
    let mut outbuf: Vec<u8> = vec![0; OUTBUF_SAMPLES * FLOAT32_BYTES];

    for index in 0..OUTBUF_SAMPLES {
        
        // Computes the value of this individual sample and puts it where it belongs in the output buffer
        outbuf[index * FLOAT32_BYTES..index * FLOAT32_BYTES + 4].copy_from_slice(
            &pitched_sine(sample_time, freq_hz, lfo_one, lfo_two).unwrap().to_le_bytes(),
        );
    }

    Ok(outbuf)
}

pub fn pitched_sine(
    time_elapsed:f32,
    freq_hz:f32,
    lfo_one:f32,
    lfo_two:f32,
) -> FnResult<f32> {
   
    // Accumulate the phase
    unsafe {
        // TODO: using this mutable static feels bad, is there another way?
        PHASE = (PHASE + (freq_hz * time_elapsed)).fract();
    }
    
    unsafe {
        // TODO: using this mutable static feels bad, is there another way?
        // Compute the sine output
        let sine_amplitude:f32 = f32::sin(2.0 * 3.14159 * PHASE) * lfo_one;
        Ok(sine_amplitude)
    }
}