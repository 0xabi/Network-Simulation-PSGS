#include <omnetpp.h>
#include "arrivalMsg_m.h"

using namespace omnetpp;


class Source : public cSimpleModule
{
  private:
    ArrivalMsg *sendMessageEvent1;
    ArrivalMsg *sendMessageEvent2;
    ArrivalMsg *sendMessageEvent3;
    int nbGenMessages1;
    int nbGenMessages2;
    int nbGenMessages3;

    double avgInterArrivalTime1;
    double avgInterArrivalTime2;
    double avgInterArrivalTime3;

  public:
    Source();
    virtual ~Source();

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Source);

Source::Source()
{
    sendMessageEvent1 = nullptr;
    sendMessageEvent2 = nullptr;
    sendMessageEvent3 = nullptr;

}

Source::~Source()
{
    cancelAndDelete(sendMessageEvent1);
    cancelAndDelete(sendMessageEvent2);
    cancelAndDelete(sendMessageEvent3);

}

void Source::initialize()
{
    sendMessageEvent1 = new ArrivalMsg();
    sendMessageEvent1 ->setPriority(1);
    sendMessageEvent2 = new ArrivalMsg();
    sendMessageEvent2 ->setPriority(2);
    sendMessageEvent3 = new ArrivalMsg();
    sendMessageEvent3 -> setPriority(3);

    nbGenMessages1 = 0;
    nbGenMessages2 = 0;
    nbGenMessages3 = 0;

    //get inter-arrival times
    avgInterArrivalTime1 = par("interArrival1").doubleValue();
    avgInterArrivalTime2 = par("interArrival2").doubleValue();
    avgInterArrivalTime3 = par("interArrival3").doubleValue();

    //start sending packets
    scheduleAt(simTime()+avgInterArrivalTime1, sendMessageEvent1);
    scheduleAt(simTime()+avgInterArrivalTime2, sendMessageEvent2);
    scheduleAt(simTime()+avgInterArrivalTime3, sendMessageEvent3);

}

void Source::handleMessage(cMessage *msg)
{
    ArrivalMsg *arrivalMsg = dynamic_cast<ArrivalMsg*>(msg);
    int msgPriority = arrivalMsg->getPriority();

    //generate packet name
    char msgname[20];


    //generate and send the packet out to the queue
    //cMessage *message = new cMessage(msgname);


    if(msgPriority == 1)
    {
        sprintf(msgname, "msg-%d-%d", ++nbGenMessages1,1);

        ArrivalMsg *msg1 = new ArrivalMsg(msgname);
        msg1->setPriority(1);
        msg1->setTimestamp(simTime());
        send(msg1, "out",0);
        scheduleAt(simTime()+exponential(avgInterArrivalTime1), sendMessageEvent1);

        bubble(msgname);
    }
    else if(msgPriority == 2)
    {
        sprintf(msgname, "msg-%d-%d", ++nbGenMessages2,2);

        ArrivalMsg *msg2 = new ArrivalMsg(msgname);
        msg2->setPriority(2);
        msg2->setTimestamp(simTime());
        send(msg2, "out",1);
        scheduleAt(simTime()+exponential(avgInterArrivalTime2), sendMessageEvent2);

        bubble(msgname);
    }
    else if(msgPriority == 3)
    {
        sprintf(msgname, "msg-%d-%d", ++nbGenMessages3,3);

        ArrivalMsg *msg3 = new ArrivalMsg(msgname);
        msg3->setPriority(3);
        msg3->setTimestamp(simTime());
        send(msg3, "out",2);
        scheduleAt(simTime()+exponential(avgInterArrivalTime3), sendMessageEvent3);

        bubble(msgname);
    }
    else
    {
        EV << "ERROR";
    }


}
