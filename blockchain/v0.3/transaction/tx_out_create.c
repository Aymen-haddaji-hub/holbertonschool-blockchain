#include "blockchain.h"

/**
 * tx_out_create - Create a transaction output
 * @amount: Amount of the transaction output
 * @pub:    Receiver's public address
 * Return:  A pointer to a newly allocated `tx_out_t`
 *         or `NULL` on error
 */
tx_out_t *tx_out_create(uint32_t amount, uint8_t *pub[EC_PUB_LEN])
{
	tx_out_t *tx_out;

	if (!amount || !pub)
		return (NULL);
	tx_out = calloc(1, sizeof(*tx_out));
	if (!tx_out)
		return (NULL);
	tx_out->amount = amount;
	memcpy(tx_out->pub, pub, sizeof(tx_out->pub));
	if (!sha256((int8_t const *)tx_out, sizeof(tx_out->amount) +
				sizeof(tx_out->pub), tx_out->hash))
		return (free(tx_out), NULL);

	return (tx_out);
}
