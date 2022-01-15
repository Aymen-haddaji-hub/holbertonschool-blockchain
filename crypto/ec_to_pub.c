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
	const EC_GROUP *group;
	size_t pub_key_len;

	if (!key || !pub)
		return (NULL);

	point = EC_KEY_get0_public_key(key);
	group = EC_KEY_get0_group(key);
	if (!point || !group)
		return (NULL);

	pub_key_len = EC_POINT_point2oct(group, point,
					 POINT_CONVERSION_UNCOMPRESSED,
					 pub, EC_PUB_LEN, NULL);
	if (pub_key_len != EC_PUB_LEN)
		return (NULL);

	return (pub);
}
