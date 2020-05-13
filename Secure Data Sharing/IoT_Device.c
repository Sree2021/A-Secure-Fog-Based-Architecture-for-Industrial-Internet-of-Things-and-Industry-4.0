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

	element_t k_S,sk_S,temp1,d,publish1;
	double time1, time2, time3, time4;
	element_t r,c0,c1,p1,p2,temp3,c2,m;
	element_t y,temp4,ca,ca1,cb1,cb,c4;

//Sender Key Generation
	time1 = pbc_get_time();
	element_init_Zr(k_S, pairing);	
	element_init_G1(sk_S, pairing);	
	element_init_G1(temp1, pairing);	
	element_init_Zr(d, pairing);
	element_init_G1(publish1, pairing);

	element_random(k_S);
	element_pow_zn(sk_S, P_S, k_S);
	element_pow_zn(temp1, publish, k_S);
	element_random(d);
	element_pow_zn(publish1, g, d);
	time2 = pbc_get_time();
	printf("\nSender Key Generation Time = %fms\n", (time2 - time1)*1000);

//perform encryption
	element_init_Zr(r, pairing);
	element_init_G1(c0, pairing);
	element_init_G1(c1, pairing);
	element_init_G1(p1, pairing);
	element_init_G2(p2, pairing);
	element_init_GT(temp3, pairing);
	element_init_GT(m, pairing);
	element_init_GT(c2, pairing);

	element_random(r);
	element_pow_zn(c0, publish1, r);
	element_pow_zn(c1, g, r);

	element_pow_zn(p1, g_S, r);
	element_pow_zn(p2, publish, k_S);
	element_pairing(temp3, p1, p2);
	element_random(m);
	element_mul(c2, m, temp3);
	time3 = pbc_get_time();
	printf("\nEncryption Time = %fms\n", (time3 - time2)*1000);

	//generate re-encryption key
	element_init_GT(y, pairing);
	element_init_Zr(temp4, pairing);
	element_init_G1(ca, pairing);
	element_init_G1(ca1, pairing);
	element_init_G1(cb1, pairing);
	element_init_G1(cb, pairing);
	element_init_G1(c4, pairing);

	element_random(y);
	element_mul_zn(temp4,mk,k_S);
	element_pow_zn(ca1,g_S,temp4);
	element_invert(ca, ca1);
	int n =element_length_in_bytes(y);
	unsigned char *data = pbc_malloc(n);
	element_to_bytes(data, y);
	char *out3 = SHA256(data, n,0);
	element_from_hash(cb1, out3, strlen(out3));
	element_pow_zn(cb,cb1,d);
	element_mul(c4,ca,cb);
	time4 = pbc_get_time();
	printf("\nRe-Encryption Key Generation Time = %fms\n", (time4 - time3)*1000);

	element_clear(k_S);
	element_clear(sk_S);
	element_clear(temp1);
	element_clear(d);
	element_clear(publish1);
	element_clear(r);
	element_clear(c0);
	element_clear(c1);
	element_clear(p1);
	element_clear(p2);
	element_clear(temp3);
	element_clear(c2);
	element_clear(m);
	element_clear(y);
	element_clear(temp4);
	element_clear(ca);
	element_clear(ca1);
	element_clear(cb1);
	element_clear(cb);
	element_clear(c4);
	

return 0;
}
