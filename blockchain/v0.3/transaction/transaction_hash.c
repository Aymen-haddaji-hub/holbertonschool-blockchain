#include "transaction.h"

/**
 * create_tx_data_buffer - Creates a buffer for the transaction data
 * @tx: The transaction to create the buffer for
 * @input_count: The number of inputs
 * @output_count: The number of outputs
 * @tx_io_buf_size: The size of the buffer
 * Return: A pointer to the buffer or NULL on error
 */
uint8_t *create_tx_data_buffer(
	const transaction_t *tx,
	int *input_count,
	int *output_count,
	size_t *tx_io_buf_size)
{
	uint8_t *tx_data_buf;

	if (!tx || !input_count || !output_count)
		return (NULL);
	*input_count = llist_size(tx->inputs);
	if (*input_count == -1)
		return (NULL);
	*output_count = llist_size(tx->outputs);
	if (*output_count == -1)
		return (NULL);
	*tx_io_buf_size = ((SHA256_DIGEST_LENGTH * 3) * *input_count) +
					  ((SHA256_DIGEST_LENGTH * 3) * *output_count);
	tx_data_buf = calloc(*tx_io_buf_size, sizeof(uint8_t));
	if (!tx_data_buf)
		return (NULL);
	return (tx_data_buf);
}

/**
 * fill_tx_data_buffer - Fills the buffer with the transaction data
 * @tx: The transaction to create the buffer for
 * @input_count: The number of inputs
 * @output_count: The number of outputs
 * @tx_io_buf: The buffer to fill with the transaction data
 * Return: 0 on success, 1 on error
 */
int fill_tx_data_buffer(
	const transaction_t *tx,
	int input_count,
	int output_count,
	uint8_t *tx_io_buf)
{
	int i;
	uint8_t *tx_data_buf;
	tx_in_t *tx_in;
	tx_out_t *tx_out;

	if (!tx || !tx_io_buf)
		return (1);
	for (i = 0, tx_data_buf = tx_io_buf; i < input_count; i++)
	{
		tx_in = (tx_in_t *)llist_get_node_at(tx->inputs, i);
		if (!tx_in)
			return (1);
		memcpy(tx_data_buf, tx_in, (SHA256_DIGEST_LENGTH * 3));
		tx_data_buf += (SHA256_DIGEST_LENGTH * 3);
	}
	for (i = 0; i < output_count; i++)
	{
		tx_out = (tx_out_t *)llist_get_node_at(tx->outputs, i);
		if (!tx_out)
			return (1);
		memcpy(tx_data_buf, tx_out->hash, SHA256_DIGEST_LENGTH);
		tx_data_buf += SHA256_DIGEST_LENGTH;
	}
	return (0);
}
/**
 * transaction_hash - compute the ID (hash) of a transaction
 * @transaction: the transaction to compute the ID of
 * @hash_buf: the buffer to store the ID in
 * Return: pointer to hash_buf
 */
uint8_t *transaction_hash(
	transaction_t const *transaction,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	uint8_t *tx_data_buf;
	size_t tx_io_buf_size;
	int input_count;
	int output_count;
	
	if (!transaction || !hash_buf)
		return (NULL);
	tx_data_buf = create_tx_data_buffer(transaction,
										&input_count,
										&output_count,
										&tx_io_buf_size);
	if (!tx_data_buf)
		return (NULL);
	if (fill_tx_data_buffer(transaction,
							input_count,
							output_count,
							tx_data_buf) != 0)
	{
		free(tx_data_buf);
		return (NULL);
	}
	if (!sha256((const int8_t *)tx_data_buf,
				tx_io_buf_size,
				hash_buf))
	{
		free(tx_data_buf);
		return (NULL);
	}
	free(tx_data_buf);
	return (hash_buf);
}
