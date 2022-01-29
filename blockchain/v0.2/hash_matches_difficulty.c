#include "blockchain.h"

/**
 * hash_matches_difficulty - check if a hash matches the difficulty
 * @hash: hash to check
 * @difficulty: difficulty to check against
 * Return: 1 if hash matches difficulty, 0 otherwise
 **/
int hash_matches_difficulty(uint8_t const hash[SHA256_DIGEST_LENGTH],
					uint32_t difficulty)
{
	int i;
	uint32_t diff = 0;
	uint8_t *p = (uint8_t *)hash;

	if (!hash)
		return (0);
	for (; p < hash + SHA256_DIGEST_LENGTH; p++)
	{
		for (i = 7; i >= 0; i--)
		{
			if ((*p >> i) & 1)
			{
				if (diff >= difficulty)
					return (1);
				return (0);
			}
			diff++;
		}
	}
	if (diff < difficulty)
		return (0);
	return (1);
}
