#ifndef NTT_H_
#define NTT_H_

#include <stdint.h>
#include "params.h"

#define QINV 58728449 // q^(-1) mod 2^32
#define MONT -4186625 // 2^32 % Q

int32_t montgomery_reduce(int64_t a);
int32_t reduce32(int32_t a);
int32_t caddq(int32_t a);
int32_t freeze(int32_t a);
//#define ntt DILITHIUM_NAMESPACE(_ntt)
void ntt(int32_t a[N]);

//#define invntt_tomont DILITHIUM_NAMESPACE(_invntt_tomont)
void invntt_tomont(int32_t a[N]);

#endif
