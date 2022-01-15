#include "hblk_crypto.h"

/**
 * ec_load - a function that loads an EC key from a file.
 * @folder: path to folder
 * Return: pointer to EC key on success, NULL on error.
 */
EC_KEY *ec_load(char const *folder)
{
	FILE *fp;
	char path[256] = {0};
	EC_KEY *key;

	if (!folder)
		return (NULL);
	sprintf(path, "%s/%s", folder, PRI_FILENAME);
	fp = fopen(path, "r");
	if (!fp)
		return (NULL);
	key = PEM_read_ECPrivateKey(fp, NULL, NULL, NULL);
	fclose(fp);
	if (!key)
		return (NULL);
	sprintf(path, "%s/%s", folder, PUB_FILENAME);
	fp = fopen(path, "r");
	if (!fp)
		return (NULL);
	if (!PEM_read_EC_PUBKEY(fp, &key, NULL, NULL))
	{
		EC_KEY_free(key);
		return (NULL);
	}
	fclose(fp);
	return (key);
}
