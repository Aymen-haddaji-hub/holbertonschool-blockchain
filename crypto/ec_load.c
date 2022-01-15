#include "hblk_crypto.h"

/**
 * ec_load - loads an EC key pair from the disk.
 * @folder: path to the folder in which to save the keys
 * Return: pointer to the loaded EC key, NULL on error
 */
EC_KEY *ec_load(char const *folder)
{
	FILE *fp;
	char path[256] = {0};
	EC_KEY *key = NULL;

	if (!folder)
		return (0);
	sprintf(path, "%s/" PUB_FILENAME, folder);
	fp = fopen(path, "r");
	if (!fp)
	{
		EC_KEY_free(key);
		return (0);
	}
	if (!PEM_read_EC_PUBKEY(fp, &key, NULL, NULL))
	{
		EC_KEY_free(key);
		fclose(fp);
		return (0);
	}
	fclose(fp);
	sprintf(path, "%s/" PRI_FILENAME, folder);
	fp = fopen(path, "r");
	if (!fp)
		return (0);
	if (!PEM_read_ECPrivateKey(fp, &key, NULL, NULL))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);
	return (key);
}
