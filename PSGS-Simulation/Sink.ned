simple Sink
{
    parameters:
        @display("i=block/sink");
        @signal[queueingTime1];
        @signal[responseTime1];
        @signal[extendedServiceTime1];
        @signal[queueingTime2];
        @signal[responseTime2];
        @signal[extendedServiceTime2];
        @signal[queueingTime3];
        @signal[responseTime3];
        @signal[extendedServiceTime3];
        @signal[utilizationFactor1];
        @signal[utilizationFactor2];
        @signal[utilizationFactor3];
        @signal[generalQueueingTime];
        @signal[generalResponseTime];

        @statistic[queueingTime1](title="Queueing time of class-1"; unit=s; record=vector,mean; interpolationmode=none);
        @statistic[queueingTime2](title="Queueing time of class-2"; unit=s; record=vector,mean; interpolationmode=none);
        @statistic[queueingTime3](title="Queueing time of class-3"; unit=s; record=vector,mean; interpolationmode=none);
		@statistic[generalQueueingTime](title="General queueing time"; unit=s; record=vector,mean; interpolationmode=none);


        @statistic[responseTime1](title="Response time of class-1"; unit=s; record=vector,mean; interpolationmode=none);
        @statistic[responseTime2](title="Response time of class-2"; unit=s; record=vector,mean; interpolationmode=none);
        @statistic[responseTime3](title="Response time of class-3"; unit=s; record=vector,mean; interpolationmode=none);
		@statistic[generalResponseTime](title="General queueing time"; unit=s; record=vector,mean; interpolationmode=none);

        @statistic[extendedServiceTime1](title="Extended service time of class-1"; unit=s; record=vector,mean; interpolationmode=none);
        @statistic[extendedServiceTime2](title="Extended service time of class-2"; unit=s; record=vector,mean; interpolationmode=none);
        @statistic[extendedServiceTime3](title="Extended service time of class-3"; unit=s; record=vector,mean; interpolationmode=none);
        
        @statistic[utilizationFactor1](title="Utilization factor of class-1"; record=vector,mean;);
        @statistic[utilizationFactor2](title="Utilization factor of class-2"; record=vector,mean;);
        @statistic[utilizationFactor3](title="Utilization factor of class-3"; record=vector,mean;);
        
       volatile double avgServiceTime1 @unit(s);
       volatile double avgServiceTime2 @unit(s);
       volatile double avgServiceTime3 @unit(s);
        
    gates:
        input in;
}
