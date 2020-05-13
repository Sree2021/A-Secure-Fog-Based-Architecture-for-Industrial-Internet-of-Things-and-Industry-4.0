#The Fog Node receives the data packets and the signatures from the IoT device
#The public key of the IoT device is known publicly by the entire system

import timeit
from blspy import (PrivateKey, PublicKey, InsecureSignature, Signature,
                   PrependSignature, AggregationInfo, ExtendedPrivateKey,
                   Threshold, Util)
data = []
num = 3 #the number of data packets

	# Add information required for verification, to sig object
	dt3 = timeit.default_timer()
	for x in range(num):
		sig[x].set_aggregation_info(AggregationInfo.from_msg(pk[x], msg[x]))
		ok = sig[x].verify()
	print ("Signature Verification Time:",(dt4-dt3)*1000,"ms")
