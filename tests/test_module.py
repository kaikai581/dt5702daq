#!/usr/bin/env python

from dt5702 import DT5702
from protocol import FEBDTP

def data_handler(nbytes):
    '''
    A dummy data handler to test function pointers.
    '''
    print(nbytes)

def Init(iface='enp0s31f6'):
    t = FEBDTP(iface)
    if t.ScanClients() == 0:
        print('No clients connected, exiting')
        return 0
    t.PrintMacTable()

    # initialize the voltage-controlled crystall oscillator
    t.VCXO = 500

    # loop through all detected FEBs
    for febid in range(t.nclients):
        febs[febid] = DT5702()
        febs[febid].mac5 = t.macs[febid][5]
        print(febs[febid].mac5)
        febs[febid].ts0_ref_AVE = 0
        febs[febid].ts0_ref_IND = 0
    
    # assign the data handler
    t.setPacketHandler(data_handler)
    t.fPacketHandler(500)

    # try to access the data field
    print(t.gpkt.Data[12])
    
    # Next, much code involves the member variable "dstmac",
    # which is the destination mac address the protocol writes to.
    return 1

if __name__ == '__main__':
    febs = dict()
    Init()
