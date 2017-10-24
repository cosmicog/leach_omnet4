/*
 * base.cc
 *
 *  Created on: Dec 20, 2014
 *      Author: orhangazi44
 *
 *      LGPL
 *
 */

#include "base.h"

Define_Module(Base);

void Base::initialize()
{
    mainModule = getModuleByPath("LeachBasic");
    p = mainModule->par("p").doubleValue();
    numNodes = mainModule->par("numNodes");
    clusterMaxMember = (int)(1 / p);
    numClusters = (numNodes / clusterMaxMember);
    numberOfLivingNodes = numNodes;
    receivedRoundCount = 0;
    totalExpendedEnergy = 0;
    nodeDeaths = new bool[ numNodes ];
    nodeBatteries = new double[ numNodes ];
    double ndbt = mainModule->par("nodeBatteries");

    for(int i = 0; i < numNodes; i++)
    {
        nodeDeaths[i] = false; // Buna sonra bak
        nodeBatteries[i] = ndbt;
    }

    WATCH(numberOfLivingNodes);
    WATCH(receivedRoundCount);

    char* str = new char[16];
    xPosition = mainModule->par("bazX");
    yPosition = mainModule->par("bazY");
    sprintf(str, "BS (%d, %d)", xPosition, yPosition);
    getDisplayString().setTagArg("t", 0, str);
    getDisplayString().setTagArg("p", 0, xPosition);
    getDisplayString().setTagArg("p", 1, yPosition);

    totalEnergyVector.setName("Total Energy Vector");
    numberOfLivingNodesVector.setName("Number Of Living Nodes Vector");
    receivedRoundCountVector.setName("Received Round Count Vector");
    expendedEnergiesForRoundsVector.setName("Expended Energies For Rounds Vector");

    totalEnergyVector.record(totalExpendedEnergy);
    numberOfLivingNodesVector.record(numberOfLivingNodes);
    receivedRoundCountVector.record(receivedRoundCount);
    expendedEnergiesForRoundsVector.record(0.0);

    cMessage * msg2 = new cMessage("recordEnergy");
    simtime_t stt2 = 0.1;
    scheduleAt(stt2, msg2);
}

void Base::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(), "recordEnergy") == 0 )
    {
        if(noEnergy)
        {
            EV << "NO MORE INFORMATION, SIMULATION IS STOPPING!!!!!!!!XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
            return;
        }
        EV << "RECORDING =======================================XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  " << expendedEnergyForRound << "    XXXXXXXXXX\n";
        expendedEnergiesForRoundsVector.record(expendedEnergyForRound);
        // expendedEnergyForRound = .0;
        noEnergy = true;
        scheduleAt(simTime()+4, msg);
        return;
    }

    head2baseMsg *msg1 = check_and_cast<head2baseMsg *>(msg);

    if(strcmp(msg->getName(), "die") == 0 && nodeDeaths[msg1->getSource()] == false)
    {
        nodeDeaths[msg1->getSource()] = true;
        numberOfLivingNodes--;
        numberOfLivingNodesVector.record(numberOfLivingNodes);
        return;
    }

    if(strcmp(msg->getName(), "myBattery") == 0 )
    {
        noEnergy = false;
        int src = msg1->getSource();
        double olddd = nodeBatteries[src];
        nodeBatteries[src] = msg1->getTotalExpendedEnergy();
        expendedEnergyForRound += (olddd - nodeBatteries[src]);
    }

    if(strcmp(msg1->getName(), "h2bM") == 0)
    { // Message arrived.
        EV << "BASE: Message " << msg->getName() << " arrived from node[" << msg->getSenderModuleId()-2 << "].\n";
        EV << "BASE: RECEIVED DIE COUNT : " << msg1->getDieCount() << " *********************************************************************.\n";
        bubble("ARRIVED");
    }
    delete msg;
}

void Base::finish()
{
    receivedRoundCountVector.record(receivedRoundCount/numClusters); // Program tasarımında hata yapmışım, yaklaşık 5 cluster, yaklaşık bunun beşte biri olacak.
    recordScalar("#receivedRoundCount", receivedRoundCount);
    numberOfLivingNodesStats.recordAs("Number of Living Nodes");
    receivedRoundCountStats.recordAs("Recevied Message Count");
}





