#include "hblk_crypto.h"

/**
 * ec_to_pub - a function that converts an EC key to a public key.
 * @key: pointer to EC key
 * @pub: pointer to public key
 * Return: pointer to public key, NULL on error
 **/
uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{
	const EC_POINT *point;

	if (key == NULL)
		return (NULL);

	point = EC_KEY_get0_public_key(key);
	EC_POINT_point2oct(EC_KEY_get0_group(key), point,
			POINT_CONVERSION_UNCOMPRESSED, pub, EC_PUB_LEN, NULL);

	return (pub);
}
