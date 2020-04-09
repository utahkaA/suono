#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "jp/differencia/suono/SinWaveMono.h"
#include "jp/differencia/suono/SawtoothWaveMono.h"

void createSinWaveMono(void) {
  uint32_t fs = 44100;
  uint8_t bits = 16;
  uint32_t duration = 1;
  double amp = 0.1;
  double freq = 500.0;

  SinWaveMono sinWave;
  new_SinWaveMono(&sinWave, fs, bits, duration, amp, freq);

  uint32_t length = getLength_SinWaveMono(&sinWave);
  printf("fs: %d\n", getFs_SinWaveMono(&sinWave));
  printf("bits: %" PRIu8 "\n", getBits_SinWaveMono(&sinWave));
  printf("length: %d\n", length);

  write_SinWaveMono(&sinWave, "sin_wave_500.wav");
  free_SinWaveMono(&sinWave);
}

void createSawtoothWaveMono(void) {
  uint32_t fs = 44100;
  uint8_t bits = 16;
  uint32_t duration = 1;
  double gain = 0.1;
  double f0 = 500.0;
  uint32_t numOvertones = 64;

  SawtoothWaveMono sawtoothWave;
  new_SawtoothWaveMono(&sawtoothWave, fs, bits, duration, gain, f0, numOvertones);
  
  printf("fs: %d\n", getFs_SawtoothWaveMono(&sawtoothWave));
  printf("bits: %" PRIu8 "\n", getBits_SawtoothWaveMono(&sawtoothWave));
  printf("length: %d\n", getLength_SawtoothWaveMono(&sawtoothWave));

  write_SawtoothWaveMono(&sawtoothWave, "sawtooth_wave_500.wav");
  free_SawtoothWaveMono(&sawtoothWave);
}

int main(void) {
    createSawtoothWaveMono();
    return 0;
}
