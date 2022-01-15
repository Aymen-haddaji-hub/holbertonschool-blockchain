#include "hblk_crypto.h"

/**
 * EC_KEY *ec_create - a function that creates a new EC key pair.
 * Return: pointer to EC key, NULL on error
 **/
EC_KEY *ec_create(void)
{
	EC_KEY *key;

	key = EC_KEY_new_by_curve_name(NID_secp256k1);
	if (!key)
		return (NULL);

	if (!EC_KEY_generate_key(key))
	{
		EC_KEY_free(key);
		return (NULL);
	}

	return (key);
}
