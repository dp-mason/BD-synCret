use extism_pdk::*;

static mut PHASE:f32 = 0.0;

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


// TODO: this function computes one sample, I would like to test buffering
// the output but this logic should be abstracted away from the single sample calc
#[plugin_fn]
pub fn rust_wasm_sine(
    input: Vec<u8>
) -> FnResult<f32> {
   
    // Compute the frequency from the pitch parameter and input
    // The default frequency is C4 = 261.6256f
    
    let sample_time:f32 = f32::from_le_bytes((input[0..4]).try_into().unwrap());
    //let frame:i64 = i64::from_le_bytes((input[16..24]).try_into().unwrap());
    let voct_pitch:f32 = f32::from_le_bytes((input[4..8]).try_into().unwrap());
    
    let freq:f32 = 261.6256 * f32::powf(2.0, voct_pitch);

    // Accumulate the phase
    unsafe{
        PHASE = (PHASE + (freq * sample_time)).fract();
        // Compute the sine output
        let sine:f32 = f32::sin(2.0 * 3.14159 * PHASE);
        
        Ok(10.0 * sine)
    }

}