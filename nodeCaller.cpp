

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


string NodeCaller::checkConnection(string check_messsage){
	
	HttpClient httpclient((this->targetUrl).c_str());
	nodeApiClient nodeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call checkConnection (" << this->targetUrl << ")" << endl;
		jsonValue = nodeApi.checkConnection(check_messsage);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["status_connection"].asString();
}


string NodeCaller::checkStorage(string check_messsage){

	HttpClient httpclient((this->targetUrl).c_str());
	nodeApiClient nodeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call checkStorage (" << this->targetUrl << ")" << endl;
		jsonValue = nodeApi.checkStorage(check_messsage);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["status_storage"].asString();
}


string NodeCaller::uploadPartOfFile(string upload_message){
	HttpClient httpclient((this->targetUrl).c_str());
	nodeApiClient nodeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call uploadPartOfFile (" << this->targetUrl << ")" << endl;
		jsonValue = nodeApi.uploadPartOfFile(upload_message);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["status_upload"].asString();
}


string NodeCaller::downloadFile(string download_message){
	HttpClient httpclient((this->targetUrl).c_str());
	nodeApiClient nodeApi(httpclient, JSONRPC_CLIENT_V2);
	
	Json::Value jsonValue;
	
	try{
		cout << "Call downloadFile (" << this->targetUrl << ")" << endl;
		jsonValue = nodeApi.downloadFile(download_message);
		cout << "return from (" << this->targetUrl << ") : \n" << jsonValue.toStyledString() << endl;
		
	
	} catch (JsonRpcException &e) {
		cerr << "return from (" << this->targetUrl << ") : \n" << e.what() << endl;
	}
	
	return jsonValue["status_download"].asString();
}


