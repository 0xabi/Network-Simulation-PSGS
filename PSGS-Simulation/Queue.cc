#include <omnetpp.h>
#include <serverStatusMsg_m.h>
#include <arrivalMsg_m.h>

using namespace omnetpp;

class Queue: public cSimpleModule {
protected:
    cMessage *msgInServer;
    cMessage *endOfServiceMsg;

    cQueue queue;



    bool serverBusy;
    int priorityUserInServer;

    int numQueue;

    bool preemption;

    int arrivals;

    cMessage *repeat;

public:
    Queue();
    virtual ~Queue();
    int returnArrivals();

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void putPacketInQueue(cMessage *msg);
    void sendPacketToServer(cMessage *msg);
};

Define_Module(Queue);

Queue::Queue() {
    msgInServer = endOfServiceMsg = nullptr;
}

Queue::~Queue() {
    delete msgInServer;
    cancelAndDelete(endOfServiceMsg);
}

int Queue::returnArrivals()
{
    int copy = arrivals;
    arrivals = 0;
    return copy;

}

void Queue::initialize() {

    numQueue = par("numQueue");

    endOfServiceMsg = new cMessage("end-service");
    queue.setName("queue");

    serverBusy = false;
    priorityUserInServer = 0;

    preemption = par("preemption");

    arrivals = 0;

    repeat = new cMessage();


}

void Queue::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {

        EV << "Self message?";

} else {

    //check from which gate it's arrived
    cGate *arrivalGate = msg->getArrivalGate();

    if (arrivalGate != nullptr) {

        int arrivalGateIndex = arrivalGate->getIndex();

        //it arrives from source
        if (arrivalGateIndex == 0) {

            arrivals++;

            EV << "Queue " << numQueue << ": Arrival from source!\n";

            ArrivalMsg *arrMsg = dynamic_cast<ArrivalMsg*>(msg);
            int priorityMsg = arrMsg->getPriority();

            //put the user into the queue only if the server have a higher or equal user priority (if preemption enabled)
            // remember priority 1 > priority 2 !!!
            if (serverBusy && preemption) {
                //the user in the server have more priority
                if (priorityUserInServer <= priorityMsg) {

                    //save the last time that the user go to the queue
                    arrMsg->setLastTimeJoinQueue(simTime());
                    putPacketInQueue(arrMsg);

                    EV << "Queue " << numQueue
                              << ": Server is Busy and there is another user (not lower priority)\n";
                    EV << "         because the current user with priority "
                              << priorityUserInServer
                              << "is higher or equal than\n";
                    EV << "         the arrived user with priority "
                              << priorityMsg << "\n";
                    EV << "Queue " << numQueue
                              << ": Putting the user in the queue\n";
                    EV << "[Preemption ON]\n";

                }
                //the user in the server have less priority
                else {
                    //if the queue is empty i go directly
                    if (queue.isEmpty()) {

                        sendPacketToServer(arrMsg);

                        EV << "Queue " << numQueue
                                  << ": the arrived user with priority "
                                  << priorityMsg << " have more priority than "
                                  << priorityUserInServer << "\n";
                        EV << "Queue " << numQueue
                                  << ": Sent the user into the server\n";
                    }
                    //the queue is not empty so pop the queue
                    else {
                        //the arrived user go to the queue

                        //save the last time that the user go to the queue
                        arrMsg->setLastTimeJoinQueue(simTime());
                        putPacketInQueue(arrMsg);

                        //pop the user with the same priority and send to the server
                        ArrivalMsg *msgToSend =
                                dynamic_cast<ArrivalMsg*>(queue.pop());

                        //update the queueing time
                        simtime_t lastTimeJoinQueue =
                                msgToSend->getLastTimeJoinQueue();
                        simtime_t queueTime = msgToSend->getQueueingTime();
                        queueTime = queueTime + (simTime() - lastTimeJoinQueue);
                        msgToSend->setQueueingTime(queueTime);

                        sendPacketToServer(msgToSend);

                        EV << "Queue " << numQueue
                                  << ": the arrived user with priority"
                                  << priorityMsg << " have more priority than "
                                  << priorityUserInServer << "\n";
                        EV << "Queue " << numQueue
                                  << ": the arrived user with priority "
                                  << priorityMsg << " have more priority\n"
                                  << "\t but there is another user in the queue with the same priority\n";
                        EV << "Queue " << numQueue << ": Popping...\n";
                        EV << "Queue " << numQueue
                                  << ": Sent the user into the server\n";
                    }

                    EV << "[Preemption ON]\n";

                    //server is now busy
                    serverBusy = true;                //useless
                }
            } else if (serverBusy && !preemption) {

                arrMsg->setLastTimeJoinQueue(simTime());
                putPacketInQueue(arrMsg);
                EV << "Queue " << numQueue
                          << ": Putting the user with priority " << priorityMsg
                          << " in the queue\n";
                EV << "[Preemption OFF]\n";
            } else { //server idle, start service right away
                     //Put the message in server and start service

                sendPacketToServer(arrMsg);

                EV << "Queue " << numQueue << ": server is idle\n";
                EV << "Queue " << numQueue
                          << ": Sent the user into the server\n";

                //server is now busy
                serverBusy = true;

            }
        }
        //it arrives from server
        else if (arrivalGateIndex == 1) {

            //check if is a server status message
            //or an arrival message

            EV << "Queue " << numQueue << ": Arrival from the server\n";

            ServerStatusMsg *ssm = dynamic_cast<ServerStatusMsg*>(msg);
            ArrivalMsg *amsg = dynamic_cast<ArrivalMsg*>(msg);

            //is a server status message
            if (ssm != nullptr) {

                EV << "Queue " << numQueue << ": Server status message\n";

                serverBusy = ssm->getBusy();

                priorityUserInServer = ssm->getPriority();
                EV << "Queue " << numQueue
                          << ": Server is busy, save priority user that is into the server i.e "
                          << priorityUserInServer << "\n";

                //if the server is not busy
                if (!serverBusy) {
                    if (!queue.isEmpty()) {

                        ArrivalMsg *arrMsg = (ArrivalMsg*) queue.pop();

                        //update the queueing time
                        simtime_t lastTimeJoinQueue =
                                arrMsg->getLastTimeJoinQueue();
                        simtime_t queueTime = arrMsg->getQueueingTime();
                        queueTime = queueTime + (simTime() - lastTimeJoinQueue);
                        arrMsg->setQueueingTime(queueTime);

                        sendPacketToServer(arrMsg);

                        EV << "Queue " << numQueue
                                  << ": The server is not busy anymore and i have user in the queue\n";
                        EV << "Queue " << numQueue
                                  << ": I send user into the server\n";
                    }
                }

                delete ssm;
            }

            //it's an arrival message, so the "packet" return to the queue
            //and i'll put it to the head to be reprocessed later
            //this happens when you get kicked out for a high priority user
            else if (amsg != nullptr) {
                EV << "Queue " << numQueue
                          << ": It's an arrival message, so the user was kicked out\n";
                EV << "Queue " << numQueue
                          << ": Inserting the kicked out user into the queue\n";

                //insert the message to the head of the queue
                if (queue.isEmpty()) {
                    amsg->setLastTimeJoinQueue(simTime());
                    queue.insert(amsg);
                } else {

                    amsg->setLastTimeJoinQueue(simTime());

                    ArrivalMsg *headArrivalMsg =
                            dynamic_cast<ArrivalMsg*>(queue.front());

                    //it will be popped before all users to continue later to be served
                    queue.insertBefore(headArrivalMsg, amsg);
                }

            }

        } else {
            EV << "Queue " << numQueue << ": Error in Queue\n";
        }
    } else {
        EV << "Queue " << numQueue << ": Error: Arrival Gate is Null\n";
    }
}
}

void Queue::sendPacketToServer(cMessage *msg) {
send(msg, "out");
}

void Queue::putPacketInQueue(cMessage *msg) {

queue.insert(msg);
EV << msg->getName() << "        enters queue" << endl;
}



