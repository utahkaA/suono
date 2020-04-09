#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "SawtoothWaveMono.h"

/**
 * [private] SawtoothWaveMono 構造体の変数を作成する
 * @param (self) SawtoothWaveMono 構造体の変数
 * @param (numOvertones) 足し合わせる倍音の数
 */
void _new_SawtoothWaveMono(SawtoothWaveMono* self, uint32_t numOvertones) {
    uint32_t fs = ((MonoPCM *) self)->fs;
    uint32_t length = ((MonoPCM *) self)->length;
    double gain = self->gain;
    double f0 = self->f0;

    /*
     * ノコギリ波の作成
     */
    for (int n = 1; n <= numOvertones; n++) {
        for (int t = 0; t < length; t++) {
            ((MonoPCM *) self)->data[t] += 1.0 / n * sin(2.0 * M_PI * n * f0 * t / fs);
        }
    }

    for (int t = 0; t < length; t++) {
        ((MonoPCM *) self)->data[t] *= gain;
    }
}

/**
 * SawtoothWaveMono 構造体の変数を作成する (コンストラクタ)
 * @param (self) SawtoothWaveMono 構造体変数
 * @param (fs) サンプリング周波数
 * @param (bits) 量子化ビット数
 * @param (duration) 音声データの長さ
 * @param (gain) ゲイン
 * @param (f0) 基本周波数
 * @param (numOvertones) 足し合わせる倍音の数
 */
void new_SawtoothWaveMono(SawtoothWaveMono* self, uint32_t fs, uint8_t bits, uint32_t duration, double gain, double f0, uint32_t numOvertones) {
    new_MonoPCM((MonoPCM *)self, fs, bits, duration);
    self->gain = gain;
    self->f0 = f0;
    _new_SawtoothWaveMono(self, numOvertones);
}

/**
 * fs の Getter
 * @param (self) SawtoothWaveMono 構造体の変数
 */
uint32_t getFs_SawtoothWaveMono(SawtoothWaveMono* self) {
    return (self->pcm).fs;
}

/**
 * bits の Getter
 * @param (self) SawtoothWaveMono 構造体の変数
 */
uint8_t getBits_SawtoothWaveMono(SawtoothWaveMono* self) {
    return (self->pcm).bits;
}

/**
 * length の Getter
 * @param (self) SawtoothWaveMono 構造体の変数
 */
uint32_t getLength_SawtoothWaveMono(SawtoothWaveMono* self) {
    return (self->pcm).length;
}

/**
 * SawtoothWaveMono を wav 形式で書き出す
 * @param (self) SawtoothWaveMono 構造体の変数
 * @param (fileName) 書き出すファイル名
 */
void write_SawtoothWaveMono(SawtoothWaveMono* self, char* fileName) {
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

/**
 * SawtoothWaveMono 構造体の変数のメモリを開放する
 * @param (self) SawtoothWaveMono 構造体の変数
 */
void free_SawtoothWaveMono(SawtoothWaveMono* self) {
    free_MonoPCM((MonoPCM *)self);
}