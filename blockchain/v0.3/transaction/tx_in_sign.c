#include "transaction.h"

/**
 * tx_in_sign - Signs a transaction input
 * @in: The transaction input to sign
 * @tx_id: The transaction ID
 * @sender: The private key of the reciver of coins
 * contained in the transaction output referenced by @in
 * @all_unspent: The list of all unspent transaction outputs
 * Return: pointer to the signature structure on success,
 * NULL on error
 */
sig_t *tx_in_sign(tx_in_t *in,
	uint8_t const tx_id[SHA256_DIGEST_LENGTH],
	EC_KEY const *sender, llist_t *all_unspent)
{
	uint8_t pub[EC_PUB_LEN];
	unspent_tx_out_t *unspent;
	ssize_t i;

	for (i = 0; i < llist_size(all_unspent); i++)
	{
		unspent = llist_get_node_at(all_unspent, i);
		if (!memcmp(in->tx_out_hash, unspent->out.hash, SHA256_DIGEST_LENGTH))
			break;
		unspent = NULL;
	}
	if (!unspent || !ec_to_pub(sender, pub) ||
		!memcmp(pub, unspent->out.pub, EC_PUB_LEN))
		return (NULL);
	if (!ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &(in->sig)))
		return (NULL);

	return (&(in->sig));
}
