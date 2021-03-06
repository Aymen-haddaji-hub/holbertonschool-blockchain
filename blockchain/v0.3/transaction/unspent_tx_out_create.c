#include "transaction.h"

/**
 * unspent_tx_out_create - Create an unspent transaction output
 * @block_hash: Hash of the Block containing the transaction @tx_id
 * @tx_id:      ID of the transaction containing @out
 * @out:        Copy of the referenced transaction output
 * Return:      A pointer to a newly allocated `unspent_tx_out_t`
 * or `NULL` on error
 */
unspent_tx_out_t *unspent_tx_out_create(
	uint8_t block_hash[SHA256_DIGEST_LENGTH],
	uint8_t tx_id[SHA256_DIGEST_LENGTH], tx_out_t const *out)
{
	unspent_tx_out_t *unspent;

	unspent = calloc(1, sizeof(*unspent));
	if (!unspent)
		return (NULL);
	memcpy(unspent->block_hash, block_hash, SHA256_DIGEST_LENGTH);
	memcpy(unspent->tx_id, tx_id, SHA256_DIGEST_LENGTH);
	memcpy(&(unspent->out), out, sizeof(*out));
	return (unspent);
}
