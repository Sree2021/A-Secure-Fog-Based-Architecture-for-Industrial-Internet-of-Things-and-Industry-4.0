#Python Code to generate one aggregated signature for 'n' data packets

import sys
import timeit
import random 
from blspy import (PrivateKey, PublicKey, InsecureSignature, Signature,
                   PrependSignature, AggregationInfo, ExtendedPrivateKey,
                   Threshold, Util)

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
	for x in range(num):
		seed = bytes([x+1]) + seed[1:]
		sk[x] = PrivateKey.from_seed(seed)
		pk[x] = sk[x].get_public_key()
		msg[x]=bytes(m[x])
	dt1 = timeit.default_timer()
	for x in range(num):
		sig[x] = sk[x].sign(msg[x])
	for i in range(0,num-1,2):
		# Aggregate signatures together
		agg_sig_l = Signature.aggregate([sig[i], sig[i+1]])
		# Arbitrary trees of aggregates
		agg_sig_final = Signature.aggregate([agg_sig_l, sig[i+2]])	
		sig[i+2]=agg_sig_final
	dt2 = timeit.default_timer()
	print ("Signature Generation:",(dt2-dt1)*1000,"ms")
	return agg_sig_final,msg   

# receive data from function
message,msg = aggsig()




