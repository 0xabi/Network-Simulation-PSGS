simple Server
{
    parameters:
       volatile double avgServiceTime1 @unit(s);
       volatile double avgServiceTime2 @unit(s);
       volatile double avgServiceTime3 @unit(s);
       bool preemption;
            
    gates:
       input in[];
       output out[];
}
