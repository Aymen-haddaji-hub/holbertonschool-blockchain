#include "blockchain.h"

/**
 * blockchain_serialize - serializes a blockchain
 * @blockchain: pointer to the blockchain to be serialized
 * @path: path to the file to be created
 * if the file already exists, it will be overwritten
 * Return: 0 on success, -1 on failure
 **/
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *file;
	block_t *block;
	hblk_file_t hblk_file;
	int i;

	if (!blockchain || !path)
		return (-1);

	memcpy(hblk_file.hblk_magic, HBLK_MAGIC, 4);
	memcpy(hblk_file.hblk_version, HBLK_VERSION, 3);
	hblk_file.hblk_endian = _get_endianness();
	hblk_file.hblk_blocks = llist_size(blockchain->chain);

	file = fopen(path, "wb");
	if (!file)
		return (-1);

	fwrite(&hblk_file, sizeof(hblk_file), 1, file);
	for (i = 0; i < hblk_file.hblk_blocks; i++)
	{
		block = llist_get_node_at(blockchain->chain, i);
		if (!block)
		{
			fclose(file);
			return (-1);
		}
		fwrite((void *)&block->info, sizeof(block->info), 1, file);
		fwrite((void *)&block->data.len, sizeof(block->data.len), 1, file);
		fwrite((void *)block->data.buffer, block->data.len + 1, 1, file);
		fwrite((void *)block->hash, SHA256_DIGEST_LENGTH, 1, file);
	}
	fclose(file);
	return (0);
}
