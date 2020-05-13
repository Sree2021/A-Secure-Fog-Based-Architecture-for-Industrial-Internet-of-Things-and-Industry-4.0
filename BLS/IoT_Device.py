#Python Code to generate signature for 'n' data packets

import sys
import timeit
import random
from blspy import (PrivateKey, PublicKey, InsecureSignature, Signature,
                   PrependSignature, AggregationInfo, ExtendedPrivateKey,
                   Threshold, Util)

#derive public key, private key and signatures
def aggsig():
	seed = bytes([0, 50, 6, 244, 24, 199, 1, 25, 52, 88, 192,
                19, 18, 12, 89, 6, 220, 18, 102, 58, 209,
                82, 12, 62, 89, 110, 182, 9, 44, 20, 254, 22])
	num=3 #number of data packets that needs to be transferred together
	sk=[0]*num
	pk=[0]*num
	sig=[0]*num
	msg=[0]*num
	m=[]

	for j in range(num): 
        	m.append(random.randint(1, 999))
	dt1 = timeit.default_timer()
	for x in range(num):
		seed = bytes([x+1]) + seed[1:]
		sk[x] = PrivateKey.from_seed(seed)
		pk[x] = sk[x].get_public_key()
		msg[x]=bytes(m[x])
		sig[x] = sk[x].sign(msg[x])
	dt2 = timeit.default_timer()
	print ("Signature Generation:",(dt2-dt1)*1000,"ms")
	return sig,msg   

# receive data from function
signature,msg = aggsig()





