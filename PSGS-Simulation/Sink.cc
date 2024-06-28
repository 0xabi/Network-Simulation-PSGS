#include <omnetpp.h>
#include "arrivalMsg_m.h"
#include "Queue.h"
#include "Server.h"

using namespace omnetpp;

class Sink: public cSimpleModule {
private:

    simsignal_t queueingTime1Signal;
    simsignal_t queueingTime2Signal;
    simsignal_t queueingTime3Signal;

    simsignal_t responseTime1Signal;
    simsignal_t responseTime2Signal;
    simsignal_t responseTime3Signal;

    simsignal_t extendedServiceTime1Signal;
    simsignal_t extendedServiceTime2Signal;
    simsignal_t extendedServiceTime3Signal;

    simsignal_t utilizationFactor1Signal;
    simsignal_t utilizationFactor2Signal;
    simsignal_t utilizationFactor3Signal;

    simsignal_t generalQueueingTimeSignal;
    simsignal_t generalResponseTimeSignal;

    cMessage *repeat1;
    cMessage *repeat2;
    cMessage *repeat3;

    double freqClass1;
    double freqClass2;
    double freqClass3;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Sink);

void Sink::initialize() {
    queueingTime1Signal = registerSignal("queueingTime1");
    queueingTime2Signal = registerSignal("queueingTime2");
    queueingTime3Signal = registerSignal("queueingTime3");

    responseTime1Signal = registerSignal("responseTime1");
    responseTime2Signal = registerSignal("responseTime2");
    responseTime3Signal = registerSignal("responseTime3");

    extendedServiceTime1Signal = registerSignal("extendedServiceTime1");
    extendedServiceTime2Signal = registerSignal("extendedServiceTime2");
    extendedServiceTime3Signal = registerSignal("extendedServiceTime3");

    utilizationFactor1Signal = registerSignal("utilizationFactor1");
    utilizationFactor2Signal = registerSignal("utilizationFactor2");
    utilizationFactor3Signal = registerSignal("utilizationFactor3");

    generalQueueingTimeSignal = registerSignal("generalQueueingTime");
    generalResponseTimeSignal = registerSignal("generalResponseTime");

    repeat1 = new cMessage("1");
    repeat1->setKind(1);
    repeat2 = new cMessage("2");
    repeat2->setKind(2);
    repeat3 = new cMessage("3");
    repeat3->setKind(3);


    freqClass1= par("avgServiceTime1").doubleValue();
    freqClass2 = par("avgServiceTime2").doubleValue();
    freqClass3 = par("avgServiceTime3").doubleValue();

    scheduleAt(simTime() + freqClass1, repeat1);
    scheduleAt(simTime() + freqClass2, repeat2);
    scheduleAt(simTime() + freqClass3, repeat3);
}

void Sink::handleMessage(cMessage *msg) {

    ArrivalMsg *arrMsg = dynamic_cast<ArrivalMsg*>(msg);

    if (msg->isSelfMessage()) {


        //cModule *qmod = getParentModule()->getSubmodule("queues1");
        cModule *qmod = getParentModule()->getModuleByPath("Net.queue1");
        cModule *qmod2 = getParentModule()->getModuleByPath("Net.queue2");
        cModule *qmod3 = getParentModule()->getModuleByPath("Net.queue3");
        cModule *smod = getParentModule()->getModuleByPath("Net.server");


        //why dynamic_cast doesnt work?
        Queue *queue1 = (Queue*) (qmod);
        Queue *queue2 = (Queue*) (qmod2);
        Queue *queue3 = (Queue*) (qmod3);
        Server *server = (Server*) (smod);

        double utilization = 0;

        if (msg->getKind() == 1) {
            int arrivals1 = queue1->returnArrivals();
            int departures1 = server->returnDepartures1();

            if (departures1 != 0) {
                utilization = arrivals1 / departures1;
                emit(utilizationFactor1Signal, utilization);
            }

            scheduleAt(simTime() + freqClass1, repeat1);

        } else if (msg->getKind() == 2) {
            int arrivals2 = queue2->returnArrivals();
            int departures2 = server->returnDepartures2();

            if (departures2 != 0) {
                utilization = arrivals2 / departures2;
                emit(utilizationFactor2Signal, utilization);
            }

            scheduleAt(simTime() + freqClass2, repeat2);

        } else if (msg->getKind() == 3) {
            int arrivals3 = queue3->returnArrivals();
            int departures3 = server->returnDepartures3();

            if (departures3 != 0) {
                utilization = arrivals3 / departures3;
                emit(utilizationFactor3Signal, utilization);
            }

            scheduleAt(simTime() + freqClass3, repeat3);

        }

    }
    if (arrMsg != nullptr) {
        int priority = arrMsg->getPriority();
        simtime_t queueingTime = arrMsg->getQueueingTime();
        simtime_t responseTime = simTime().dbl() - arrMsg->getTimestamp();
        simtime_t extendedServiceTime = simTime().dbl()
                - arrMsg->getFirstTime();

        EV << "Sink: user of priority " << priority << " arrived\n"
                  << "\t queueingTime: " << queueingTime << "\n"
                  << "\t responseTime: " << responseTime << "\n"
                  << "\t extendedServiceTime: " << extendedServiceTime << "\n";

        if (priority == 1) {

            emit(queueingTime1Signal, queueingTime);
            emit(responseTime1Signal, responseTime);
            emit(extendedServiceTime1Signal, extendedServiceTime);

        } else if (priority == 2) {

            emit(queueingTime2Signal, queueingTime);
            emit(responseTime2Signal, responseTime);
            emit(extendedServiceTime2Signal, extendedServiceTime);
        } else if (priority == 3) {

            emit(queueingTime3Signal, queueingTime);
            emit(responseTime3Signal, responseTime);
            emit(extendedServiceTime3Signal, extendedServiceTime);
        } else {
            EV << "Sink: ERROR, strange priority";
        }

        emit(generalQueueingTimeSignal, queueingTime);
        emit(generalResponseTimeSignal, responseTime);

        delete msg;

    }
    else {

        EV << "Sink: Error, strange message";
    }

}
