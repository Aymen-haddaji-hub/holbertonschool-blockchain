#include "blockchain.h"

/**
 * block_create - creates a new block
 * @prev: pointer to the previous block
 * @data: data to be stored in the block
 * @data_len: length of the data
 * Return: On success pointer to the new block
 * On error, return NULL
 **/
block_t *block_create(block_t const *prev,
					  int8_t const *data, uint32_t data_len)
{
	block_t *new_block;

	if (!data || !data_len)
		return (NULL);
	if (data_len > BLOCKCHAIN_DATA_MAX)
		data_len = BLOCKCHAIN_DATA_MAX;

	new_block = calloc(1, sizeof(*new_block));
	if (!new_block)
		return (NULL);

	new_block->info.index = prev->info.index + 1;
	new_block->info.timestamp = time(NULL);
	new_block->info.nonce = 0;
	memcpy(new_block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	memcpy(new_block->data.buffer, data, data_len);
	new_block->data.len = data_len;
	return (new_block);
}
