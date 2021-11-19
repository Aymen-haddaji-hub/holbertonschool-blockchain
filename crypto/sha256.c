#include "hblk_crypto.h"

/**
 * sha256 - a function that computes the hash of a sequence of bytes.
 * @s: Sequence of bytes to be hashed
 * @len: Bytes to hash
 * @digest: array to store resulting hash in
 *
 * Return: pointer to digest, NULL on error
 */

uint8_t *sha256(int8_t const *s, size_t len,
		uint8_t digest[SHA256_DIGEST_LENGTH])
{
	uint8_t *x;

	if (!s || !digest)
		return (NULL);

	x = SHA256((const unsigned char *)s, len, digest);
	return (x);
}
