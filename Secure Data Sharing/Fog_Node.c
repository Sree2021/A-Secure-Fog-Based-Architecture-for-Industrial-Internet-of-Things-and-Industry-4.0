//The Fog Node receives c' and the re-encryption key and computes the re-encrypted ciphertext c''

#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	
	element_t cc,cf;

	//Re-Encryption
	element_init_GT(cc, pairing);
	element_init_GT(cf, pairing);

	element_pairing(cc, c4, c1);
	element_mul(cf,c2,cc);
	time6 = pbc_get_time();
	printf("\nRe-Encryption by Fog Time = %fms\n", (time6 - time5)*1000);

	element_clear(cc);
	element_clear(cf);

	return 0;
}

