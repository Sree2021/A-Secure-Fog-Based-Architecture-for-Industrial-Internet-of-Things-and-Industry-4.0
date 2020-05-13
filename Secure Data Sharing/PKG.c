//The PKG generates the system parameters, partial private key and shares it with the IoT Device and the User
#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/md5.h>
#endif

int main(int argc, char **argv) {

	pairing_t pairing;
	element_t g,mk,publish,g_S,g_R,P_S,P_R;
	double time1, time2;
	const char Id_S[]="101", Id_R[]="201";

	pbc_demo_pairing_init(pairing, argc, argv);
	if (!pairing_is_symmetric(pairing)) 
		pbc_die("Pairing must be symmetric");

	printf("Proxy Re-Encryption Test\n");

	time1 = pbc_get_time();
	//generate system parameters
	element_init_G1(g, pairing);
	element_init_G1(publish, pairing);
	element_init_Zr(mk, pairing);
	element_random(g);
	element_random(mk);
	element_pow_zn(publish, g, mk);

	//partial private key generation
	element_init_G1(g_S, pairing);
	element_init_G1(g_R, pairing);
	element_init_G1(P_S, pairing);
	element_init_G1(P_R, pairing);

	char *out1 = SHA256(Id_S, strlen(Id_S),0);
	char *out2 = SHA256(Id_R, strlen(Id_R),0);

	element_from_hash(g_S, out1, strlen(out1));
	element_from_hash(g_R, out2, strlen(out2));

	element_pow_zn(P_S, g_S, mk);
	element_pow_zn(P_R, g_R, mk);
	time2 = pbc_get_time();
	printf("\nPKG Setup Time = %fms\n", (time2 - time1)*1000);

	element_clear(g);
	element_clear(mk);
	element_clear(publish);
	element_clear(g_S);
	element_clear(P_S);
	element_clear(g_R);
	element_clear(P_R);
	pairing_clear(pairing);

	return 0;
}
