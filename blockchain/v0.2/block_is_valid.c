#include "blockchain.h"

/**
 * block_is_valid - checks if a block is valid
 * and checks that a Block’s hash matches its difficulty
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
	uint8_t const *p;
	uint32_t i;

	if (!block)
		return (-1);

	if (prev_block && block->info.prev_hash != prev_block->hash)
		return (-1);

	if (block->info.nonce == 0)
		return (-1);

	if (block->info.difficulty % 8)
		if ((block->hash[block->info.difficulty / 8] &
			(0xFF << (8 - block->info.difficulty % 8))) != 0)
			return (-1);

	p = block->hash;
	for (i = 0; i < block->info.difficulty / 8; i++)
		if (*p++ != 0x00)
			return (-1);

	return (0);
}
