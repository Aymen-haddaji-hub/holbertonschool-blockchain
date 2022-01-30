#include "transaction.h"

/**
 * tx_in_create - Creates a new transaction input
 * @unspent: The unspent output to use
 * Return: A pointer to the new transaction input
 * On error, return NULL.
 * The created transaction input’s signature structure
 * must be zeroed
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *tx_in;

	if (!unspent)
		return (NULL);
	tx_in = calloc(1, sizeof(*tx_in));
	if (!tx_in)
		return (NULL);
	memcpy(tx_in->block_hash, unspent->block_hash, SHA256_DIGEST_LENGTH);
	memcpy(tx_in->tx_id, unspent->tx_id, SHA256_DIGEST_LENGTH);
	memcpy(tx_in->tx_out_hash, &(unspent->out).hash, SHA256_DIGEST_LENGTH);
	memset(&(tx_in->sig), 0, sizeof(tx_in->sig));
	return (tx_in);
}
