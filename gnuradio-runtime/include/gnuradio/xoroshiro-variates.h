/*
  Copyright (C) 2017 Marcus Müller

  All rights reserved.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1, as
  published by the Free Software Foundation.  This program is
  distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
  License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

// Built on XOROSHIRO128+ by David Blackman and Sebastiano Vigna
// see http://xoroshiro.di.unimi.it/xoroshiro128plus.c
#ifndef INCLUDED_XOROSHIRO_VARIATES_H
#define INCLUDED_XOROSHIRO_VARIATES_H
#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <math.h>

/*! \brief rotating left shift helper
 * According to the original authors, this will on most platforms reduce to a single instruction
 */
static inline uint64_t rotl(const uint64_t x, const int k) {
  return (x << k) | (x >> (64 - k));
}

/*! \brief Convert the uint64_t output of the RNG to a uniform float32 on [0,1]
 */
static inline float uint64_to_f(const uint64_t in) {
  // Float32 has 24 significant bits.
  return (in >> (64-24)) * ( ((float)1.0f) / (UINT64_C(1) << 24));
}
/*! \brief Convert the uint32_t output of the RNG to a uniform float32 on [0,1]
 */
static inline float uint32_to_f(const uint32_t in) {
  // Float32 has 24 significant bits.
  return (in >> (32-24)) * ( ((float)1.0f) / (UINT32_C(1) << 24));
}
/*! \brief Convert the uint64_t output of the RNG to a uniform double (float64) on [0,1]
 */
static inline double uint64_to_d(const uint64_t in) {
  // Float64 has 53 significant bits.
  return (in >> (64-53)) * ( ((double)1.0) / (UINT64_C(1) << 53));
}

/*! \brief generate the next random number and update the state.
 * This is the workhorse, here!
 */
static inline uint64_t xoroshiro128p_next(uint64_t *state) {
  const uint64_t s0 = state[0];
  uint64_t s1 = state[1];
  const uint64_t result = s0 + s1;

  s1 ^= s0;
  state[0] = rotl(s0, 55) ^ s1 ^ (s1 << 14); // a, b
  state[1] = rotl(s1, 36); // c

  return result;
}


/*! \brief Advance the internal state by 2^64 steps; useful when coordinating multiple independent RNGs
  This is the jump function for the generator. It is equivalent
   to 2^64 calls to next(); it can be used to generate 2^64
   non-overlapping subsequences for parallel computations. */

static inline void xoroshiro128p_jump(uint64_t *state) {
  static const uint64_t JUMP[] = { 0xbeac0467eba5facb, 0xd86b048b86aa9922 };

  uint64_t s0 = 0;
  uint64_t s1 = 0;
  for(int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
    for(int b = 0; b < 64; b++) {
      if (JUMP[i] & UINT64_C(1) << b) {
        s0 ^= state[0];
        s1 ^= state[1];
      }
      xoroshiro128p_next(state);
    }

  state[0] = s0;
  state[1] = s1;
}

/*! \brief step of the SPLITMIX64 RNG; only used internally for seeding
 * This RNG isn't as good as XOROSHIRO128+, so it's only used to initialize a 128 bit state from a seed.
 */
static inline uint64_t splitmix64_next(uint64_t *state) {
  uint64_t z = (*state += 0x9e3779b97f4a7c15);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
  z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
  return z ^ (z >> 31);
}

/*! \brief Seed the 128 bit state from a 64 bit seed
 */
static void xoroshiro128p_seed(uint64_t *state, const uint64_t seed) {
  state[0] = seed;
  state[1] = splitmix64_next(state);
  xoroshiro128p_jump(state);
}

/*! \brief Use the Central Limit Theorem to generate a Normal RNG
 */
static inline float xoroshiro128p_cltf(uint64_t *state, const uint32_t iterations) {
  // expected value of a [0;2^32-1] uniformly discrete variable
  // 2^31 - 1/2
  static const int32_t mu_32 = (UINT64_C(1) << 31) - 1 ; // +0.5, see sum -= iterations/2
  // variance: ((b-a+1)^2 - 1)/12; b = 2^32 - 1, a = 0
  //          =((2^32)^2 -1)  /12
  //          =( 2^64 - 1)    /12
  //          =  2^64 / 12 - 1/12
  //          =  2^62 / 3  - 1/12
  // close enough
  //         ~=  2^31 / sqrt(3)
  static const float std_32 = 1239850262.2531197f;
  int64_t sum = 0;
  for(uint32_t _ = 0; _ < iterations; _++) {
    sum +=  (xoroshiro128p_next(state) >> 32) - mu_32;
  }
  sum += iterations / 2;
  float val = (float)sum / std_32 / sqrtf(iterations);
  return val;
}

#ifdef __cplusplus
}
#endif
#endif // Include guard
