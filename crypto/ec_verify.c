#include "hblk_crypto.h"

/**
 * ec_verify - Verify an ECDSA signature
 * @key: pointer to the public key
 * @msg: pointer to the message to verify
 * @msglen: length of the message to verify
 * @sig: pointer to the signature structure
 * Return: 1 if the signature is valid, 0 otherwise.
 */
int ec_verify(EC_KEY const *key, uint8_t const *msg,
				size_t msglen, sig_t const *sig)
{
	return (ECDSA_verify(0, msg, msglen, sig->sig, sig->len, (EC_KEY *)key));
}
