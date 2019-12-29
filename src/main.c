#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "wave.h"

int main(void) {
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
  return 0;
}
