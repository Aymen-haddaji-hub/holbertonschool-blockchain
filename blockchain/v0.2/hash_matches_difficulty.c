#include "blockchain.h"

/**
 * hash_matches_difficulty - Checks if a hash matches a given difficulty
 * @hash: Hash to be checked
 * @difficulty: Difficulty to be checked against
 * Return: 1 if the hash matches the difficulty, 0 otherwise
 */
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
							uint32_t difficulty)
{
	uint8_t const *p = hash;
	uint32_t i;

	for (i = 0; i < difficulty / 8; i++)
		if (*p++ != 0x00)
			return (0);

	if (difficulty % 8)
		if ((*p & (0xFF << (8 - difficulty % 8))) != 0)
			return (0);

	return (1);
}
