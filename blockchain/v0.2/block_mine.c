#include "blockchain.h"

/**
 * block_mine - mines a block
 * @block: pointer to the block to be mined
 * Return: nothing (void)
 */
void block_mine(block_t *block)
{
	block->info.nonce = 0;
	while (!hash_matches_difficulty(block->hash, block->info.difficulty))
	{
		block->info.nonce++;
		block_hash(block, block->hash);
	}
}
