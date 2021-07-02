#!/usr/bin/env python

from dt5702 import DT5702
from protocol import FEBDTP

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
        # febs[febid].mac5 = t.macs[febid][5]
        febs[febid].ts0_ref_AVE = 0
        febs[febid].ts0_ref_IND = 0

if __name__ == '__main__':
    febs = dict()
    Init()
