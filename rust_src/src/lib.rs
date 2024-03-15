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

#[plugin_fn]
pub fn rust_wasm_sine(
    input: f32,
    // input: Vec<u8>
) -> FnResult<f32> {
    
    Ok(0.233)

}
    
    // // Compute the frequency from the pitch parameter and input
    // // The default frequency is C4 = 261.6256f
    
    // let sample_rate_bytes:[u8;4] = (input[0..4]).try_into().unwrap();
    // let sample_rate:f32 = f32::from_le_bytes(sample_rate_bytes);

    // let sample_time_bytes:[u8;4] = (input[4..8]).try_into().unwrap();
    // let sample_time:f32 = f32::from_le_bytes(sample_time_bytes);

    // let voct_bytes:[u8;4] = [
    //     input[8],
    //     input[9],
    //     input[10],
    //     input[11],
    // ];
    // let voct_voltage:f32 = f32::from_le_bytes(voct_bytes);
    
    // let frame_bytes:[u8;8] = (input[12..20]).try_into().unwrap();
    // let frame:i64 = i64::from_le_bytes(frame_bytes);
    
    // let freq:f32 = 261.6256 * f32::powf(2.0, voct_voltage);

    // // Accumulate the phase
    // unsafe{
    //     PHASE = (PHASE + (freq * sample_time)).fract();
    //     // Compute the sine output
    //     let sine:f32 = f32::sin(2.0 * 3.14159 * PHASE);
    //     Ok( 10.0 * sine )
    // }

