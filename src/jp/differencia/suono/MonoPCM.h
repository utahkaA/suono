#ifndef MONO_PCM_H
#define MONO_PCM_H

#include <stdlib.h>

typedef struct {
    uint32_t fs;
    uint8_t bits;
    uint32_t length;
    double *data;
} MonoPCM;

void new_MonoPCM(MonoPCM* self, uint32_t fs, uint8_t bits, uint32_t duration);
void free_MonoPCM(MonoPCM* self);

#endif