#include <omnetpp.h>
#include "serverStatusMsg_m.h"
#include "arrivalMsg_m.h"

#include <assert.h>

using namespace omnetpp;

class Server: public cSimpleModule {
protected:
    ArrivalMsg *msgInServer;
    cMessage *endOfServiceMsg;

    bool serverBusy;

    ServerStatusMsg busy_su;
    ServerStatusMsg idle_su;

    double avgServiceTime1;
    double avgServiceTime2;
    double avgServiceTime3;

    bool preemption;

    int numDepartures1;
    int numDepartures2;
    int numDepartures3;

public:
    Server();
    virtual ~Server();
    int returnDepartures1();
    int returnDepartures2();
    int returnDepartures3();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void startPacketService(ArrivalMsg *msg);
    void putPacketInQueue(cMessage *msg);
};

Define_Module(Server);

Server::Server() {
    msgInServer = nullptr;
    endOfServiceMsg = nullptr;
}

Server::~Server() {
    delete msgInServer;
    cancelAndDelete(endOfServiceMsg);
}


int Server::returnDepartures1()
{
    int copy = numDepartures1;
    numDepartures1=0;
    return copy;

}

int Server::returnDepartures2()
{
    int copy = numDepartures2;
    numDepartures2=0;
    return copy;
}

int Server::returnDepartures3()
{
    int copy = numDepartures3;
    numDepartures3=0;
    return copy;

}


void Server::initialize() {
    endOfServiceMsg = new cMessage("end-service");
    serverBusy = false;

    //get avgServiceTime parameter
    avgServiceTime1 = par("avgServiceTime1").doubleValue();
    avgServiceTime2 = par("avgServiceTime2").doubleValue();
    avgServiceTime3 = par("avgServiceTime3").doubleValue();

    preemption = par("preemption");


    busy_su.setBusy(true);
    idle_su.setBusy(false);

    numDepartures1 = 0;
    numDepartures2 = 0;
    numDepartures3 = 0;
}

void Server::handleMessage(cMessage *msg) {

    ArrivalMsg *arrMsg = dynamic_cast<ArrivalMsg*>(msg);

    if (msg->isSelfMessage()) { //Packet in server has been processed

        //log service completion
        EV << "Server: Completed service of " << msgInServer->getName() << endl;

        int priority = msgInServer->getPriority();

        if(priority==1)
        {
            numDepartures1++;
        }
        else if(priority==2)
        {
            numDepartures2++;
        }
        else if(priority==3)
        {
            numDepartures3++;
        }
        else
        {
            EV << "Server: During self message strange priority";
        }

        //Send processed packet to sink
        send(msgInServer, "out", 3);

        // send status update to queue
        serverBusy = false;

        //server is not busy anymore
        msgInServer = nullptr;
        serverBusy = false;

        //log idle server
        EV << "Server: server goes IDLE" << endl;

        send(idle_su.dup(), "out", 0);
        send(idle_su.dup(), "out", 1);
        send(idle_su.dup(), "out", 2);

    }
    // packet from queue and arrival message
    else if(arrMsg!=nullptr){


        //i have to kick out the current user
        //the queue logic checked that it have higher priority
        if (serverBusy) {
            int priorityUser = msgInServer->getPriority();
            int priorityArrivedUser = arrMsg->getPriority();

            //if the current user is higher or equal user
            // remember priority 1 > priority 2 !!!
            if (priorityUser <= priorityArrivedUser || !preemption) {

                if (!preemption) {
                    EV << "Server: No preemption, kick back\n";
                    EV << "Server: the user was: " << arrMsg->getName() << "\n";
                } else {
                    EV
                              << "Server: i'm busy and the arrival have no higher priority, kick back\n";
                    EV << "Server: the user was: " << arrMsg->getName() << "\n";
                }

                send(arrMsg, "out", priorityArrivedUser - 1);

            }
            //preemption policy
            else {
                cancelEvent(endOfServiceMsg);
                simtime_t passedServiceTime =
                        msgInServer->getPassedServiceTime();
                simtime_t lastSimTimeJoinServer =
                        msgInServer->getLastTimeJoinServer();

                msgInServer->setPassedServiceTime(
                        passedServiceTime
                                + (simTime() - lastSimTimeJoinServer));

                send(msgInServer, "out", priorityUser - 1);

                EV << "Server: stop the service time of "
                          << msgInServer->getName() << "\n";
                EV << "Server: because arrived user with priority "
                          << priorityArrivedUser << " is greater than\n";
                EV << "        the current user with priority " << priorityUser
                          << "\n";

                //update last time the user join the server
                arrMsg->setLastTimeJoinServer(simTime());

                //Put the message in server and start service
                msgInServer = arrMsg;
                startPacketService(arrMsg);

                //server is now busy
                serverBusy = true;

                busy_su.setPriority(priorityArrivedUser);
                send(busy_su.dup(), "out", 0);
                send(busy_su.dup(), "out", 1);
                send(busy_su.dup(), "out", 2);

            }

        }
        //if server is not busy
        else {
            //update last time the user join the server
            arrMsg->setLastTimeJoinServer(simTime());

            //Put the message in server and start service
            msgInServer = arrMsg;
            startPacketService(arrMsg);

            //server is now busy
            serverBusy = true;

            busy_su.setPriority(arrMsg->getPriority());
            send(busy_su.dup(), "out", 0);
            send(busy_su.dup(), "out", 1);
            send(busy_su.dup(), "out", 2);
        }

    }

}

void Server::startPacketService(ArrivalMsg *msg) {

    //generate service time and schedule completion accordingly
    //simtime_t serviceTime = exponential(avgServiceTime);
    int priority = msgInServer->getPriority();
    double passedServiceTime = msgInServer->getPassedServiceTime().dbl();

    //store when the user enters for the first time
    if (msgInServer->isFirstTime()) {
        msgInServer->setFirstTime(simTime());
        msgInServer->setIsFirstTime(false);
        EV << "Server: saving first entrance of the user timestamp\n";
    }

    if (priority == 1) {
        scheduleAt(simTime() + (avgServiceTime1 - passedServiceTime),
                endOfServiceMsg);
        serverBusy = true;
    } else if (priority == 2) {
        scheduleAt(simTime() + (avgServiceTime2 - passedServiceTime),
                endOfServiceMsg);
        serverBusy = true;
    } else if (priority == 3) {
        scheduleAt(simTime() + (avgServiceTime3 - passedServiceTime),
                endOfServiceMsg);
        serverBusy = true;
    }

    //log service start
    const char *nameUser = msgInServer->getName();
    simtime_t firstTime = msgInServer->getFirstTime();
    simtime_t lastTimeJoinServer = msgInServer->getLastTimeJoinServer();
    simtime_t lastTimeJoinQueue = msgInServer->getLastTimeJoinQueue();
    simtime_t queueingTime = msgInServer->getQueueingTime();

    EV << "Server: Starting service of " << nameUser << endl;
    EV << nameUser << ": \n" << "\t passedServiceTime: " << passedServiceTime
              << "\n" << "\t firstTimeJoinedServer: " << firstTime << "\n"
              << "\t lastTimeJoinedServer: " << lastTimeJoinServer << "\n"
              << "\t lastTimeJoinedQueue: " << lastTimeJoinQueue << "\n"
              << "\t queueingTime: " << queueingTime << "\n";

}

