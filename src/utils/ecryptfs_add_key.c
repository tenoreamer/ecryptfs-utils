#include <stdio.h>
#include <ecryptfs.h>

void usage(void)
{
	printf("Usage:\n"
	       "\n"
	       "ecryptfs-add-key [module alias] [module params]\n"
	       "\n");
}

int main(int argc, char *argv[])
{
	struct ecryptfs_pki_elem *selected_pki = NULL;
	char auth_tok_sig_hex[ECRYPTFS_SIG_SIZE_HEX + 1];
	int rc = 0;

	if (argc != 2) {
		usage();
		goto out;
	}
	if ((rc = ecryptfs_add_key_module_key_to_keyring(auth_tok_sig_hex,
							 selected_pki))) {
		printf("Error attempting to insert key "
		       "into the user session keyring; rc = [%d]. "
		       "Check the system log for more information from "
		       "libecryptfs.\n", rc);
		rc = 1;
		goto out;
	}
	auth_tok_sig_hex[ECRYPTFS_SIG_SIZE_HEX] = '\0';
	printf("Inserted auth tok with sig [%s] into the user session "
	       "keyring\n", auth_tok_sig_hex);
out:
	return rc;
}
