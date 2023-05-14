#ifndef FIPS202_H_
#define FIPS202_H_

#include <stddef.h>
#include <stdint.h>

#define SHAKE128_RATE 168
#define SHAKE256_RATE 136
#define SHA3_256_RATE 136
#define SHA3_512_RATE 72

#define FIPS202_NAMESPACE(s) pqcrystals_fips202_ref##s

typedef struct {
  uint64_t s[25];
  unsigned int pos;
} keccak_state;


void shake128_init(keccak_state *state);

void shake128_absorb(keccak_state *state, const uint8_t *in, unsigned int inlen);

void shake128_finalize(keccak_state *state);

void shake128_squeezeblocks(uint8_t *out, unsigned int nblocks, keccak_state *state);

void shake128_squeeze(uint8_t *out, unsigned int outlen, keccak_state *state);

void shake256_init(keccak_state *state);

void shake256_absorb(keccak_state *state, const uint8_t *in, unsigned int inlen);

void shake256_finalize(keccak_state *state);

void shake256_squeezeblocks(uint8_t *out, unsigned int nblocks,  keccak_state *state);

void shake256_squeeze(uint8_t *out, unsigned int outlen, keccak_state *state);


void shake128(uint8_t *out, unsigned int outlen, const uint8_t *in, unsigned int inlen);

void shake256(uint8_t *out, unsigned int outlen, const uint8_t *in, unsigned int inlen);

void sha3_256(uint8_t h[32], const uint8_t *in, unsigned int inlen);

void sha3_512(uint8_t h[64], const uint8_t *in, unsigned int inlen);

#endif
