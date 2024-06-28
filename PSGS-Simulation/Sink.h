#include <omnetpp.h>
#include "arrivalMsg_m.h"

using namespace omnetpp;


class Sink : public cSimpleModule
{
  private:
    //simsignal_t lifetimeSignal;
    //simsignal_t arrivedMsgSignal;
    //simsignal_t avgSojournSignal;
    //int nb_arrivedMsg;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Sink);


void Sink::initialize()
{
    //lifetimeSignal = registerSignal("lifetime");
    //arrivedMsgSignal = registerSignal("arrivedMsg");
    //avgSojournSignal = registerSignal("avgSojourn");
    //nb_arrivedMsg = 0;
}

void Sink::handleMessage(cMessage *msg)
{
    //compute packet lifetime
    //simtime_t lifetime = simTime() - msg->getCreationTime();
    //emit(lifetimeSignal, lifetime);

    //Msg *recvMsg = check_and_cast<Msg*>(msg);
    //emit(avgSojournSignal,recvMsg->getCount());


    //log lifetime
    //EV << "Received " << msg->getName() << ", lifetime: " << lifetime << "s" << endl;


    //nb_arrivedMsg ++;
    //emit(arrivedMsgSignal, nb_arrivedMsg);

    delete msg;
}
