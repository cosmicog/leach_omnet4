/*
 * base.h
 *
 *  Created on: Jan 1, 2015
 *      Author: orhangazi44
 *
 *      LGPL
 *
 */

#ifndef BASE_H_
#define BASE_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "leach_message_m.h"

class Base : public cSimpleModule
{
  private:
    int clusterMaxMember;
    int numNodes;
    int numClusters;
    double p;
    cModule *mainModule;
    int xPosition, yPosition;
    int receivedRoundCount;
    int numberOfLivingNodes;
    bool * nodeDeaths;
    bool noEnergy = false;
    int * posXs;
    int * posYs;
    double * nodeBatteries;
    double expendedEnergyForRound;
    double totalExpendedEnergy;
    cLongHistogram numberOfLivingNodesStats;
    cLongHistogram receivedRoundCountStats;
    cLongHistogram expendedEnergiesForRoundsStats;
    cOutVector expendedEnergiesForRoundsVector;
    cOutVector numberOfLivingNodesVector;
    cOutVector receivedRoundCountVector;
    cOutVector totalEnergyVector;

  protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(cMessage *msg);
};

#endif /* BASE_H_ */









