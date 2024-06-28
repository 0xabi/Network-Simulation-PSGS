network Net
{
    @display("bgb=818,273");
    submodules:
        source: Source {
            parameters:
                @display("p=88.365,59.594997");
        }
        queue1: Queue {
            parameters:
                @display("p=328.8,59.594997");
        }
        queue2: Queue {

            @display("p=328.8,134.6025");
        }
        queue3: Queue {

            @display("p=328.8,218.8575");
        }
        server: Server {

            @display("p=460.32,145.905");
        }
        sink: Sink {
            @display("p=549.71246,145.905");
        }
    connections:
        source.out++ --> queue1.in++;
        source.out++ --> queue2.in++;
        source.out++ --> queue3.in++;
        //source2.out --> queue2.in;
        //source3.out --> queue3.in;
        queue1.out --> server.in++;
        queue2.out --> server.in++;
        queue3.out --> server.in++;
        server.out++ --> queue1.in++;
        server.out++ --> queue2.in++;
        server.out++ --> queue3.in++;
        server.out++ --> sink.in;

}
