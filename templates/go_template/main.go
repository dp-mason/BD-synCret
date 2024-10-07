// Note: run `go doc -all` in this package to see all of the types and functions available.
// ./pdk.gen.go contains the domain types from the host where your plugin will run.
package main

import (
	"math"
)

var PHASE float32 = 0.0

const OUTBUF_SAMPLES = 256

// ComputeSaw calculates the amplitude of a saw wave at a given time
func ComputeSaw(timeElapsed float32, freq float32, lfoOne float32, lfoTwo float32) float32 {
	// Frequency modulation before phase calculation
	PHASE = float32(math.Mod((float64(PHASE + (freq * timeElapsed))), 1.0))

	// Calculate amplitude (-10 to 10) and modulate with lfoOne
	amplitude := (PHASE - 0.5) * -2.0 * lfoOne
	return amplitude
}

// BatchComputeWF processes the input buffer and outputs the saw wave data
func BatchComputeWf() error {

	// sampleTime := math.Float32frombits(pdk.ParamU32(0))
	// freqHz := math.Float32frombits(pdk.ParamU32(1))
	// lfoOne := math.Float32frombits(pdk.ParamU32(2))
	// lfoTwo := math.Float32frombits(pdk.ParamU32(3))

	// outBuf := make([]float32, OUTBUF_SAMPLES)

	// for sample := 0; sample < len(outBuf); sample++ {
	// 	outBuf[sample] = ComputeSaw(sampleTime, freqHz, lfoOne, lfoTwo)
	// }

	// pdk.Output(unsafe.Slice((*byte)(unsafe.Pointer(&outBuf[0])), len(outBuf)*4))

	var sampleTime float32 = 0.0
	var freqHz float32 = 0.0
	var lfoOne float32 = 0.0
	var lfoTwo float32 = 0.0

	outBuf := make([]float32, OUTBUF_SAMPLES)

	for sample := 0; sample < len(outBuf); sample++ {
		outBuf[sample] = ComputeSaw(sampleTime, freqHz, lfoOne, lfoTwo)
	}

	return nil
}
