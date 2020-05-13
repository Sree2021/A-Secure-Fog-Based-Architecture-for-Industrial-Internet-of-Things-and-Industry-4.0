//The user receives c'' from the Fog node and extracts the original message

#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

	double time1, time2, time3;
	element_t k_R,sk_R,temp2;
	element_t temp5,res;

	//Receiver Key Generation
	time1 = pbc_get_time();
	element_init_Zr(k_R, pairing);
	element_init_G1(sk_R, pairing);
	element_init_G1(temp2, pairing);

	element_random(k_R);	
	element_pow_zn(sk_R, P_R, k_R);	
	element_pow_zn(temp2, publish, k_R);
	
	time2 = pbc_get_time();
	printf("\nReceiver Key Generation Time = %fms\n", (time2 - time1)*1000);
	
	//Decryption
	element_init_GT(temp5, pairing);
	element_init_GT(res, pairing);

	element_pairing(temp5, cb1, c0);
	element_div(res, cf, temp5);
	if (element_cmp(m, res) == 0)
		printf("Decryption successful");
	else
		printf("Failure");

	time3 = pbc_get_time();
	printf("\nDecryption Time = %fms\n", (time3 - time2)*1000);
	
	element_clear(k_R);
	element_clear(sk_R);
	element_clear(temp2);
	element_clear(temp5);
	element_clear(res);

	return 0;
}

