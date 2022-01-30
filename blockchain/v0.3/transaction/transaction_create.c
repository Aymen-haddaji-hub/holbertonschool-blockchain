#include "transaction.h"

/**
 * get_sender_unspent - Get the unspent transaction of the sender.
 * @node: The node.
 * @idx: The index of the current node.
 * @args: The arguments (public key, tx_in, amount).
 * Return: 0 on success, 1 on error.
 */
int get_sender_unspent(llist_node_t node, unsigned int idx, void *args)
{
	unspent_tx_out_t *unspent = node;
	void **ptr = args;
	tx_in_t *tx_in;
	llist_t *inputs = ptr[1];
	uint32_t *amount = ptr[2];

	(void)idx;
	if (!memcmp(unspent->out.pub, ptr[0], EC_PUB_LEN))
	{
		tx_in = tx_in_create(unspent);
		llist_add_node(inputs, tx_in, ADD_NODE_REAR);
		*amount += unspent->out.amount;
	}
	return (0);
}
/**
 * sign_tx_in - sign tx_in
 * @node: The node.
 * @idx: The index of the current node.
 * @args: The arguments (public key, tx_in, amount).
 * Return: 0 on success, 1 on error.
 */
int sign_tx_in(llist_node_t node, unsigned int idx, void *args)
{
	tx_in_t *tx_in = node;
	void **ptr = args;

	(void)idx;
	if (!tx_in_sign(tx_in, ptr[0], ptr[1], ptr[2]))
		return (1);
	return (0);
}
/**
 * transfer_coin - Transfer coin from sender to receiver.
 * @sender: The sender.
 * @receiver: The receiver.
 * @amount: The amount.
 * @balance: The balance of the sender.
 * Return: list of transaction inputs.
 */
llist_t *transfer_coin(EC_KEY const *sender,
	EC_KEY const *receiver, uint32_t amount,
	uint32_t balance)
{
	llist_t *output;
	uint32_t rest = balance - amount;
	uint8_t pub[EC_PUB_LEN];
	tx_out_t *tx_out;

	output = llist_create(MT_SUPPORT_FALSE);
	ec_to_pub(receiver, pub);
	tx_out = tx_out_create(amount, pub);
	if (!tx_out)
		return (NULL);
	llist_add_node(output, tx_out, ADD_NODE_REAR);
	if (rest != 0)
	{
		ec_to_pub(sender, pub);
		tx_out = tx_out_create(rest, pub);
		if (!tx_out)
			return (NULL);
		llist_add_node(output, tx_out, ADD_NODE_REAR);
	}
	return (output);
}

/**
 * transaction_create - Creates a new transaction
 * @sender: The private key of the sender of coins
 * @receiver: The public key of the reciever of coins
 * @amount: The amount of coins to send
 * @all_unspent: The list of all unspent transaction outputs
 * Return: pointer to the transaction structure on success,
 * NULL on error
 */
transaction_t *transaction_create(EC_KEY const *sender,
	EC_KEY const *receiver,
	uint32_t amount,
	llist_t *all_unspent)
{
	uint8_t pub[EC_PUB_LEN];
	transaction_t *tx;
	llist_t *inputs, *outputs;
	uint32_t unspent_amount = 0;
	void *args[3];

	if (!sender || !receiver || !all_unspent)
		return (NULL);
	tx = calloc(1, sizeof(*tx));
	if (!tx)
		return (NULL);
	inputs = llist_create(MT_SUPPORT_FALSE);
	ec_to_pub(sender, pub);
	args[0] = pub;
	args[1] = inputs;
	args[2] = &unspent_amount;
	llist_for_each(all_unspent, get_sender_unspent, args);
	if (unspent_amount < amount)
	{
		free(tx);
		return (NULL);
	}
	outputs = transfer_coin(sender, receiver, amount, unspent_amount);
	if (!outputs)
	{
		free(tx);
		return (NULL);
	}
	tx->inputs = inputs;
	tx->outputs = outputs;
	args[0] = tx->id;
	args[1] = (void *)sender;
	args[2] = all_unspent;
	llist_for_each(tx->inputs, sign_tx_in, args);
	return (tx);
}
