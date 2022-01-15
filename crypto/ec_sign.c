#include "hblk_crypto.h"

/**
 * ec_sign - Sign a set of bytes with an EC private key
 * @key: pointer to the private key
 * @msg: pointer to the message to sign
 * @msglen: length of the message to sign
 * @sig: pointer to the signature structure
 * Return: Pointer to the signature buffer, or NULL on error.
 */
uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg,
				size_t msglen, sig_t *sig)
{
	unsigned int len;

	if (key == NULL || msg == NULL || sig == NULL)
		return (NULL);
	len = sig->len;
	if (ECDSA_sign(0, msg, msglen, sig->sig, &len, (EC_KEY *)key) != 1)
		return (NULL);
	sig->len = len;

	return (sig->sig);
}
