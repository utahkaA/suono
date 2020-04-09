#include <stdint.h>
#include "MonoPCM.h"

/**
 * MonoPCM 構造体の変数を作成する (コンストラクタ)
 * @param (self) MonoPCM 構造体の変数
 * @param (fs) サンプリング周波数
 * @param (bits) 量子化ビット数
 * @param (duration) 音声データの長さ [sec]
 */
void new_MonoPCM(MonoPCM* self, uint32_t fs, uint8_t bits, uint32_t duration) {
    self->fs = fs;
    self->bits = bits;
    self->length = fs * duration;
    self->data = (double*) calloc(self->length, sizeof(double));
}

/**
 * MonoPCM 構造体の変数のメモリを開放する
 * @param (self) MonoPCM 構造体の変数
 */
void free_MonoPCM(MonoPCM* self) {
    free(self->data);
}