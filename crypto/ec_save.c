#include "hblk_crypto.h"

/**
 * ec_save - a function that saves an EC key to a file.
 * @key: pointer to EC key
 * @folder: path to folder
 * folder should be created if it does not exist.
 * Return: 0 on success, -1 on error
 */
int ec_save(EC_KEY *key, char const *folder)
{
	FILE *fp;
	char path[256] = {0};

	if (!key || !folder)
		return (0);

	mkdir(folder, 0700);
	sprintf(path, "%s/%s", folder, PRI_FILENAME);
	fp = fopen(path, "w");
	if (!fp)
		return (0);
	if (!PEM_write_ECPrivateKey(fp, key, NULL, NULL, 0, NULL, NULL))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);
	sprintf(path, "%s/%s", folder, PUB_FILENAME);
	fp = fopen(path, "w");
	if (!fp)
		return (0);
	if (!PEM_write_EC_PUBKEY(fp, key))
	{
		fclose(fp);
		return (0);
	}
	fclose(fp);
	return (1);
}
