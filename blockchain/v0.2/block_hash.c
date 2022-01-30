#include "blockchain.h"

/**
 * block_hash - hashes a block
 * @block: pointer to the block to be hashed
 * @hash_buf: pointer to the buffer where the hash will be stored
 * Return: pointer to the hash_buf
 **/
uint8_t *block_hash(block_t const *block,
			uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t len;

	if (!block || !hash_buf)
		return (NULL);
	len = sizeof(block->info) + block->data.len;
	sha256((int8_t const *)block, len, hash_buf);
	return (hash_buf);
}
