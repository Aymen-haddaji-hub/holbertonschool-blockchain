#include "blockchain.h"

/**
 * block_is_valid - checks if a block is valid
 * @block: pointer to the block to be checked
 * @prev_block: pointer to the previous block
 * to be validated block should
 * not be NULL
 * prev block should be NULL only if it is the first block
 * computed hash should be the same as the hash of the block
 * Return: 0 if the block is valid, -1 otherwise
 */
int block_is_valid(block_t const *block, block_t const *prev_block)
{
	block_t const tmp = GEN_BLOCK;
	uint8_t hash[SHA256_DIGEST_LENGTH] = {0};

	if (!block || (!prev_block && block->info.index != 0))
		return (1);
	if (block->info.index == 0)
		return (memcmp(block, &tmp, sizeof(tmp)));
	if (block->info.index != prev_block->info.index + 1)
		return (1);
	if (!block_hash(prev_block, hash) ||
		memcmp(hash, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (!block_hash(block, hash) ||
		memcmp(hash, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (block->data.len > BLOCKCHAIN_DATA_MAX)
		return (1);
	return (0);
}
