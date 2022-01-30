#include "blockchain.h"

/**
 * blockchain_difficulty - computes the difficulty to
 * assign to a potential next Block in the Blockchain.
 * @blockchain: pointer to the Blockchain
 * Return: the difficulty to assign to the next Block
 * in the Blockchain
 * Difficulty adjustment:
 * Retrieve the last Block for which an adjustment was made
 * (the Block with index <blockchain_size> - DIFFICULTY_ADJUSTMENT_INTERVAL)
 * Compute the expected elapsed time between the two Blocks
 * Compute the actual elapsed time
 * The difficulty must be incremented if the elapsed time
 * is lower than half the expected elapsed time
 * The difficulty must be decremented if the elapsed time
 * is greater than twice the expected elapsed time
 * he difficulty should not change otherwise
 */
uint32_t blockchain_difficulty(blockchain_t const *blockchain)
{
	block_t *last_adjusted_block, *last_block;
	time_t expected_elapsed_time, actual_elapsed_time;

	if (!blockchain)
		return (0);
	last_block = llist_get_tail(blockchain->chain);
	if (!last_block)
		return (0);
	if (last_block->info.index == 0 ||
		last_block->info.index % DIFFICULTY_ADJUSTMENT_INTERVAL != 0)
		return (last_block->info.difficulty);
	last_adjusted_block = llist_get_node_at(blockchain->chain,
		(last_block->info.index + 1) - DIFFICULTY_ADJUSTMENT_INTERVAL);
	expected_elapsed_time = DIFFICULTY_ADJUSTMENT_INTERVAL *
			BLOCK_GENERATION_INTERVAL;
	actual_elapsed_time = last_block->info.timestamp -
		last_adjusted_block->info.timestamp;
	if (actual_elapsed_time * 2 < expected_elapsed_time)
		return (last_block->info.difficulty + 1);
	/* The difficulty must be decremented if the elapsed time is */
	/* greater than twice the expected elapsed time */
	if (actual_elapsed_time > expected_elapsed_time * 2)
		return (last_block->info.difficulty - 1);
	return (last_block->info.difficulty);
}
