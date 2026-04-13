// randombytes.h
#pragma once
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void randombytes(uint8_t *x, size_t xlen);
void kyber_rng_init(void);

#ifdef __cplusplus
}
#endif
