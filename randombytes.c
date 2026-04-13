// randombytes.c — hardware RNG for Kyber / ML-KEM on STM32F407 (STM32Duino core)
#include <stdint.h>
#include <stddef.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rng.h"

static RNG_HandleTypeDef hrng;

void kyber_rng_init(void) {
  __HAL_RCC_RNG_CLK_ENABLE();
  hrng.Instance = RNG;
  HAL_RNG_Init(&hrng);
}

// PQClean/PQM4 expect this symbol:
void randombytes(uint8_t *x, size_t xlen) {
  uint32_t v;
  size_t i = 0;
  while (i < xlen) {
    if (HAL_RNG_GenerateRandomNumber(&hrng, &v) == HAL_OK) {
      size_t n = (xlen - i < 4) ? (xlen - i) : 4;
      for (size_t j = 0; j < n; j++) {
        x[i + j] = (uint8_t)(v >> (8 * j));
      }
      i += n;
    }
  }
}
