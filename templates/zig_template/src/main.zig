const schema = @import("schema.zig");

const allocator = std.heap.wasm_allocator;

const std = @import("std");
const math = @import("std").math;

var PHASE: f32 = 0.0;

const OUTBUF_SAMPLES = 256;


// ComputeSaw calculates the amplitude of a saw wave at a given time
fn ComputeSaw(timeElapsed: f32, freq: f32, lfoOne: f32, lfoTwo: f32) f32 {
    _ = lfoTwo;
    // Frequency modulation before phase calculation
    const result = math.modf(PHASE + (freq * timeElapsed));
    PHASE = result.fpart;

    // Calculate amplitude (-10 to 10) and modulate with lfoOne
    const amplitude = (PHASE - 0.5) * -2.0 * lfoOne;
    return amplitude;
}


///
pub fn batchComputeWf() !void {
    const plugin = schema.extism.Plugin.init(allocator);
    const input_mem = plugin.getInput() catch unreachable;
    defer allocator.free(input_mem);


    const sampleTime:f32 = @bitCast(input_mem[0..4].*);
	const freqHz:f32 = @bitCast(input_mem[4..8].*);
	const lfoOne:f32 = @bitCast(input_mem[8..12].*);
	const lfoTwo:f32 = @bitCast(input_mem[12..16].*);

    var output:[OUTBUF_SAMPLES*4]u8 = [_]u8{0} ** (OUTBUF_SAMPLES*4);
    for(0..OUTBUF_SAMPLES) |i| {
        const res_bytes:[4]u8 = @bitCast(ComputeSaw(sampleTime, freqHz, lfoOne, lfoTwo));
        @memcpy(output[(i*4)..(i*4+4)], &res_bytes);
    }

    plugin.output(&output);
    
    return;
}
