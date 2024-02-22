use extism_pdk::*;

pub fn calc_value(time: f32) -> f32 {
    time.sin()
}

#[plugin_fn]
pub fn print_value(input_time: String) -> FnResult<String> {
    Ok( calc_value(input_time.parse::<f32>().unwrap()).to_string() )
    //Ok( format!("poop") )
}
