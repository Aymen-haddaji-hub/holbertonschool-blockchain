#include "blockchain.h"

/**
 * blockchain_serialize -  serializes a Blockchain into a file
 * @blockchain: points to the Blockchain to be serialized
 * @path: contains the path to a file to serialize the Blockchain into
 * Return: returns 0 upon success, or -1 upon failure
 **/
int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	FILE *fp;
	block_t *block;
	header_t header;
	int i;

	if (!blockchain || !path)
		return (-1);

	memcpy(header.hblk_magic, "HBLK", 4);
	memcpy(header.hblk_version, "0.2", 3);
	header.hblk_endian = _get_endianness();
	header.hblk_blocks = llist_size(blockchain->chain);
	if (header.hblk_blocks == -1)
		return (-1);
	fp = fopen(path, "w");
	if (!fp)
		return (-1);
	fwrite(&header, sizeof(header), 1, fp);
	for (i = 0; i < header.hblk_blocks; i++)
	{
		block = llist_get_node_at(blockchain->chain, i);
		if (!block)
		{
			fclose(fp);
			return (-1);
		}
		fwrite((void *)&block->info, sizeof(block->info), 1, fp);
		fwrite((void *)&block->data.len, sizeof(block->data.len), 1, fp);
		fwrite(block->data.buffer, block->data.len, 1, fp);
		fwrite(block->hash, sizeof(block->hash), 1, fp);
	}
	fclose(fp);
	return (0);
}
