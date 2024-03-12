use extism_pdk::*;

//static mut PHASE:f32 = 0.0;

// #[derive(serde::Deserialize)]
#[derive(serde::Deserialize, FromBytes)]
#[encoding(Json)]
struct VcvInput {
    sample_rate: f32,
    // sample_time: f32,
    // frame: i64,
    // pitch: f32,
    // phase: f32
}

#[plugin_fn]
pub fn rust_wasm_sine(
    //input: f32,
    input: Vec<u8>
) -> FnResult<f32> {
    // // Compute the frequency from the pitch parameter and input
    // // The default frequency is C4 = 261.6256f
    // let freq:f32 = 261.6256 * f32::powf(2.0, input.pitch);

    // // Accumulate the phase
    // unsafe{
    //     PHASE = (PHASE + (freq * input.sample_time)).fract();
    //     // Compute the sine output
    //     let sine:f32 = f32::sin(2.0 * 3.14159 * PHASE);
    //     Ok( 10.0 * sine )
    // }

    let bytes:[u8; 4] = (&input[0..4]).try_into().unwrap();
    let num = f32::from_le_bytes(bytes);

    //Ok(input)
    Ok(num)
}
