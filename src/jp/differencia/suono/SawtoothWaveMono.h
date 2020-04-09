#ifndef SAWTOOTH_WAVE_MONO_H
#define SAWTOOTH_WAVE_MONO_H

#include <stdint.h>
#include "MonoPCM.h"

typedef struct {
    MonoPCM pcm;
    double gain;
    double f0;
} SawtoothWaveMono;

void new_SawtoothWaveMono(SawtoothWaveMono* self, uint32_t fs, uint8_t bits, uint32_t duration, double gain, double f0, uint32_t numOvertones);
uint32_t getFs_SawtoothWaveMono(SawtoothWaveMono* self);
uint8_t getBits_SawtoothWaveMono(SawtoothWaveMono* self);
uint32_t getLength_SawtoothWaveMono(SawtoothWaveMono* self);
void write_SawtoothWaveMono(SawtoothWaveMono* self, char* fileName);
void free_SawtoothWaveMono(SawtoothWaveMono* self);

#endif