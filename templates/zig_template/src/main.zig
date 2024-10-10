const schema = @import("schema.zig");

const allocator = std.heap.wasm_allocator;

const std = @import("std");
const math = @import("std").math;

var PHASE: f32 = 0.0;

const OUTBUF_SAMPLES = 256;


// ComputeSaw calculates the amplitude of a saw wave at a given time
fn ComputeSaw(timeElapsed: f32, freq: f32, lfoOne: f32, lfoTwo: f32) f32 {
    // Frequency modulation before phase calculation
    PHASE = math.fmod(PHASE + (freq * timeElapsed), 1.0);

    // Calculate amplitude (-10 to 10) and modulate with lfoOne
    const amplitude = (PHASE - 0.5) * -2.0 * lfoOne * lfoTwo;
    return amplitude;
}


///
pub fn batchComputeWf() !void {
    const plugin = schema.extism.Plugin.init(allocator);
    const input_mem = plugin.getInput() catch unreachable;
    defer allocator.free(input_mem);

    return;
}
