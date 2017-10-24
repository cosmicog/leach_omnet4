/*
 * calculations.h
 *
 *  Created on: Dec 20, 2014
 *      Author: orhangazi44
 *
 *      LGPL
 *
 */

#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "leach_message_m.h"
#include <math.h>
#include <algorithm> // random_shuffle için

static int MIN_DISTANCE = -1;
static int SEND_REDUCE = 0;
static int RECEIVE_REDUCE = 1;
static int DATA_AGGREGATION_REDUCE = 2;
static int NO_DISTANCE = 3;
static int INFO = 0;
static int DATA = 1;
static int NUM_NODES;
static double E_ELEC;
static double E_AMP;
static double E_MP;
static double E_FS;
static int THRS_DIST;
int NUM_CLUSTERS;
int CLUSTER_DEFAULT_MEMBER;
int K;
double P;

class Node : public cSimpleModule
{
  private:
    cMessage *node2headDataMessage;
    node2headMsg *node2headChooseMessage;
    cMessage *ch2baseMessage;
    cMessage *waitEvent; // Kendine döndürecek
    cMessage *broadcastEvent; // Reklam mesajını bekletecek
    cMessage *headWaitEvent; // düğüm mesajını bekletecek
    cMessage *nextRoundEvent; // Sonraki round'a hazırlayacak
    cModule *server, *clusterHead, *mainModule;
    cOutVector receivedRoundCountVector;
    int xPosition, yPosition, curRound, globalRound, dieCount, clusterMemberCount = 0, gDeg;
    double chDistance, battery, fullBattery, networkRadius, aggBattery, percentageControl;
    double totalExpendedEnergy; // ch için;

    bool first_init = true;
    bool iAmHead = false;
    bool iAmDead = false;
    bool broadcastSent = false;
    bool littleBroadcastSent = false;
    bool chooseSent = false;
    bool broadcastArrived = false;
    bool noCh = false;
    std::string ch2headMsgStr = "";

    char *chFullPath = new char[128];
    char *color = new char[7];

    int * clusterMembers;
    int * clusterMembersXs;
    int * clusterMembersYs;
    double * clusterMembersBats;

  protected:
    virtual void die();
    virtual void finish();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void updateDisplayStringPositionAndTag(int x, int y);
    virtual void beginHeadSelection();
    virtual void beginNextRound();
    virtual double reduceBattery(double distance, int sendOrReduce, int type, int packetCount);
    virtual int getNodeId();

};

double calculateDistance(int x0, int y0, int x1, int y1)
{
    return sqrt((double)( pow(abs(x0-x1), 2) + pow(abs(y0-y1), 2) ) );
}

char* generateRandomColor()
{
    char * color = new char[7];
    const char * hexa = "0123456789ABCDEF";
    color[0] = '#';
    color[1] = hexa[ intuniform(0, 15, 0) ];
    color[2] = hexa[ intuniform(0, 15, 1) ];
    color[3] = hexa[ intuniform(0, 15, 2) ];
    color[4] = hexa[ intuniform(0, 15, 3) ];
    color[5] = hexa[ intuniform(0, 15, 4) ];
    color[6] = hexa[ intuniform(0, 15, 5) ];
    return color;
}
#endif /* CALCULATIONS_H_ */
