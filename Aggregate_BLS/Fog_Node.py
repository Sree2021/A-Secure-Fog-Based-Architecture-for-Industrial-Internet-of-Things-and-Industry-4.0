#The Fog Node receives the data packets and the aggregated signature from the IoT device
#The public key of the IoT device is known publicly by the entire system

import timeit
import pickle
from blspy import (PrivateKey, PublicKey, InsecureSignature, Signature,
                   PrependSignature, AggregationInfo, ExtendedPrivateKey,
                   Threshold, Util)

num = 3
a=[0]*num

	# Create aggregation information (or deserialize it)
	dt3 = timeit.default_timer()
	for x in range(num):
		a[x] = AggregationInfo.from_msg(pk[x], msg[x])
	for i in range(0,num-1,2):
		a1a2 = AggregationInfo.merge_infos([a[i], a[i+1]])
		a_final = AggregationInfo.merge_infos([a1a2, a[i+2]])
		a[i+2]=a_final
	agg_sig_final.set_aggregation_info(a_final)
	ok = agg_sig_final.verify()
	dt4 = timeit.default_timer()
	print ("Signature Verification Time:",(dt4-dt3)*1000,"ms")
	





