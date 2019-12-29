#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct {
  uint32_t fs;
  uint8_t bits;
  uint32_t length;
  double *data;
} MonoPCM;

void new_MonoPCM(MonoPCM* self, uint32_t fs, uint8_t bits, uint32_t duration) {
  self->fs = fs;
  self->bits = bits;
  self->length = fs * duration;
  self->data = calloc(self->length, sizeof(double));
}

void free_MonoPCM(MonoPCM* self) {
  free(self->data);
}

typedef struct {
  MonoPCM pcm;
  double amp;
  double freq;
} SinWaveMono;

void _new_SinWaveMono(SinWaveMono* self) {
  uint32_t length = ((MonoPCM *)self)->length;
  double amp = self->amp;
  uint32_t fs = ((MonoPCM *)self)->fs;

  for (int n = 0; n < length; n++) {
    ((MonoPCM *)self)->data[n] = amp * sin(2.0 * M_PI * self->freq * n / fs);
  }
}

void new_SinWaveMono(SinWaveMono* self,
                    uint32_t fs, uint8_t bits, int duration,
                    double amp, double freq) {
  new_MonoPCM((MonoPCM *)self, fs, bits, duration);
  self->amp = amp;
  self->freq = freq;
  _new_SinWaveMono(self);
}

uint32_t getFs_SinWaveMono(SinWaveMono* self) {
  return (self->pcm).fs;
}

uint8_t getBits_SinWaveMono(SinWaveMono* self) {
  return (self->pcm).bits;
}

uint32_t getLength_SinWaveMono(SinWaveMono* self) {
  return (self->pcm).length;
}

void write_SinWaveMono(SinWaveMono* self, char* fileName) {
  uint8_t riffChunkId[] = "RIFF";
  uint32_t riffChunkSize = 36 + self->pcm.length * 2;
  uint8_t fileFormatType[] = "WAVE";

  uint8_t fmtChunkId[] = "fmt ";
  uint32_t fmtChunkSize = 16;
  uint16_t waveFormatType = 1;
  uint16_t channel = 1;
  uint32_t fs = self->pcm.fs;
  uint32_t bytes = self->pcm.fs * self->pcm.bits / 8;
  uint16_t blockSize = self->pcm.bits / 8;
  uint16_t bits = self->pcm.bits;

  uint8_t dataChunkId[] = "data";
  uint32_t dataChunkSize = self->pcm.length * 2;

  FILE* stream = fopen(fileName, "wb");
  fwrite(riffChunkId, sizeof(uint8_t), 4, stream);
  fwrite(&riffChunkSize, sizeof(uint32_t), 1, stream);
  fwrite(fileFormatType, sizeof(uint8_t), 4, stream);

  fwrite(fmtChunkId, sizeof(uint8_t), 4, stream);
  fwrite(&fmtChunkSize, sizeof(uint32_t), 1, stream);
  fwrite(&waveFormatType, sizeof(uint16_t), 1, stream);
  fwrite(&channel, sizeof(uint16_t), 1, stream);
  fwrite(&fs, sizeof(uint32_t), 1, stream);
  fwrite(&bytes, sizeof(uint32_t), 1, stream);
  fwrite(&blockSize, sizeof(uint16_t), 1, stream);
  fwrite(&bits, sizeof(uint16_t), 1, stream);

  fwrite(dataChunkId, sizeof(uint8_t), 4, stream);
  fwrite(&dataChunkSize, sizeof(uint32_t), 1, stream);

  double MAX_VAL = 65536.0;
  double MIN_VAL = 0.0;
  for (uint32_t n = 0; n < self->pcm.length; n++) {
    double x = (self->pcm.data[n] + 1.0) / 2.0 * MAX_VAL;

    if (x > MAX_VAL) {
      x = MAX_VAL;
    } else if (x < 0.0) {
      x = MIN_VAL;
    }

    uint16_t _x = (uint16_t) ((int)(x + 0.5) - 32768);
    fwrite(&_x, sizeof(uint16_t), 1, stream);
  }

  fclose(stream);
}

void free_SinWaveMono(SinWaveMono* self) {
  free_MonoPCM((MonoPCM *)self);
}
