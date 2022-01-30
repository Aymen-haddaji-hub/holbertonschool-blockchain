#include "blockchain.h"

/**
 * block_destroy - destroys a block
 * @block: pointer to the block to be destroyed
 * Return: void
 * On error, return NULL
 **/
void block_destroy(block_t *block)
{
	if (!block)
		return;
	free(block);
}
