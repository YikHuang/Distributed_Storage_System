

#include "nodeCaller.h"
#include <vector>


// Json rpc
#include <stdlib.h>
#include "nodeapiclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>


using namespace jsonrpc;
using namespace std;


NodeCaller::NodeCaller(string url){
	this->targetUrl = url;
	cout << "NodeCaller created" << endl;
}


string NodeCaller::checkConnection(string temp){
	
	HttpClient httpclient((this->targetUrl).c_str());
	nodeApiClient nodeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call checkConnection (" << this->targetUrl << ")" << endl;
		jsonValue = nodeApi.checkConnection(temp);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["test"].asString();
}


string NodeCaller::checkStorage(string temp){

	HttpClient httpclient((this->targetUrl).c_str());
	nodeApiClient nodeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call checkStorage (" << this->targetUrl << ")" << endl;
		jsonValue = nodeApi.checkStorage(temp);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["test"].asString();
}


string NodeCaller::uploadPartOfFile(string temp){
	HttpClient httpclient((this->targetUrl).c_str());
	nodeApiClient nodeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call uploadPartOfFile (" << this->targetUrl << ")" << endl;
		jsonValue = nodeApi.uploadPartOfFile(temp);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["test"].asString();
}


string NodeCaller::downloadFile(string temp){
	HttpClient httpclient((this->targetUrl).c_str());
	nodeApiClient nodeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call downloadFile (" << this->targetUrl << ")" << endl;
		jsonValue = nodeApi.downloadFile(temp);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["test"].asString();
}


