#ifndef SIN_WAVE_MONO_H
#define SIN_WAVE_MONO_H

#include <stdint.h>
#include "MonoPCM.h"

typedef struct {
    MonoPCM pcm;
    double amp;
    double freq;
} SinWaveMono;

void new_SinWaveMono(SinWaveMono* self, uint32_t fs, uint8_t bits, int duration, double amp, double freq);
uint32_t getFs_SinWaveMono(SinWaveMono* self);
uint8_t getBits_SinWaveMono(SinWaveMono* self);
uint32_t getLength_SinWaveMono(SinWaveMono* self);
void write_SinWaveMono(SinWaveMono* self, char* fileName);
void free_SinWaveMono(SinWaveMono* self);

#endif