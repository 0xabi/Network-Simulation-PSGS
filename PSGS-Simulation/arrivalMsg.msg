
packet ArrivalMsg {
    int priority = 0;
    simtime_t firstTime = 0;
    simtime_t lastTimeJoinServer = 0;
    simtime_t lastTimeJoinQueue = 0;
    simtime_t queueingTime = 0;
    simtime_t passedServiceTime = 0;
    bool isFirstTime = true;  
}
