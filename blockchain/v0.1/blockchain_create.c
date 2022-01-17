#include "blockchain.h"

/**
* init_genesis_block - Creates a genesis block
* @difficulty: Difficulty of the genesis block
*  Return: Pointer to the genesis block
*/
block_t *init_genesis_block(uint8_t difficulty)
{
	block_t *block;

	block = calloc(1, sizeof(*block));
	if (!block)
		return (NULL);
	difficulty = difficulty;
	block->info.index = 0;
	block->info.difficulty = 0;
	block->info.timestamp = 1537578000;
	block->info.nonce = 0;
	memset(block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
	memcpy(block->data.buffer, "Holberton School", strlen("Holberton School"));
	block->data.len = strlen("Holberton School");
	memcpy(block->hash,
		"\xc5\x2c\x26\xc8\xb5\x46\x16\x39\x63\x5d\x8e\xdf\x2a\x97\xd4\x8d\x0c\x8e\x00\x09\xc8\x17\xf2\xb1\xd3\xd7\xff\x2f\x04\x51\x58\x03",
			SHA256_DIGEST_LENGTH);
	return (block);
}
/**
 * blockchain_create - Creates a blockchain
 * Return: Pointer to the blockchain
 **/
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain;
	block_t *genesis_block;

	blockchain = calloc(1, sizeof(*blockchain));
	if (!blockchain)
		return (NULL);
	genesis_block = init_genesis_block(0);
	if (!genesis_block)
		return (NULL);

	blockchain->chain = llist_create(MT_SUPPORT_TRUE);
	if (!blockchain->chain)
		return (NULL);
	llist_add_node(blockchain->chain, genesis_block, ADD_NODE_FRONT);
	return (blockchain);
}
