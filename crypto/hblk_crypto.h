#ifndef HBLK_CRYPTO_H
#define HBLK_CRYPTO_H

#include <stdint.h>
#include <openssl/sha.h>
#include <openssl/ec.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NID_secp256k1 714
#define EC_PUB_LEN 65


uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH]);
EC_KEY *ec_create(void);
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN]);

#endif /* HBLK_CRYPTO_H */
