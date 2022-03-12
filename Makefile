CC = g++ -std=c++17
# CC = g++ 

CFLAGS = -g -I/usr/include/jsoncpp
LDFLAGS_SV = -ljsoncpp -lmicrohttpd -ljsonrpccpp-common -ljsonrpccpp-server
LDFLAGS_CL = -ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client


all: node edge nodeApiClient.h nodeApiServer.h

# Json RPC

edgeApiClient.h:	edgeApi.json
	jsonrpcstub edgeApi.json --cpp-server=edgeApiServer --cpp-client=edgeApiClient

edgeApiServer.h:	edgeApi.json
	jsonrpcstub edgeApi.json --cpp-server=edgeApiServer --cpp-client=edgeApiClient

nodeApiClient.h:	nodeApi.json
	jsonrpcstub nodeApi.json --cpp-server=nodeApiServer --cpp-client=nodeApiClient

nodeApiServer.h:	nodeApi.json
	jsonrpcstub nodeApi.json --cpp-server=nodeApiServer --cpp-client=nodeApiClient


# Caller
edgeCaller.o:	edgeCaller.h edgeCaller.cpp
	$(CC) -c $(CFLAGS) edgeCaller.cpp
	
nodeCaller.o:	nodeCaller.h nodeCaller.cpp
	$(CC) -c $(CFLAGS) nodeCaller.cpp

# Node
node.o:	node.cpp edgeCaller.h edgeApiClient.h nodeApiServer.h nodeCaller.h nodeApiClient.h
	$(CC) -c $(CFLAGS) node.cpp

node:	node.o edgeCaller.o nodeCaller.o
	$(CC) -o node node.o edgeCaller.o nodeCaller.o $(LDFLAGS_SV) $(LDFLAGS_CL)


# Edge
edge.o:	edge.cpp edgeApiServer.h nodeCaller.h nodeApiClient.h
	$(CC) -c $(CFLAGS) edge.cpp

edge:	edge.o nodeCaller.o
	$(CC) -o edge edge.o nodeCaller.o $(LDFLAGS_SV) $(LDFLAGS_CL)



clean:
	rm -f *.o *~ edgeApiClient.h edgeApiServer.h nodeApiClient.h nodeApiServer.h edge node


