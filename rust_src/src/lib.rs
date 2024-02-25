use extism_pdk::*;

pub fn calc_value(time: f32) -> f32 {
    time.sin()
}

#[plugin_fn]
pub fn rust_wasm_sine(input_time: f32) -> FnResult<f32> {
    Ok( calc_value(input_time) )
}
