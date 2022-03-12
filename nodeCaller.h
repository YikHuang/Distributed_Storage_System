

#ifndef NODE_CALLER_H
#define NODE_CALLER_H

#include <iostream>
#include <vector>

using namespace std;


class NodeCaller{
	private:
		string targetUrl;
	
	public:
		NodeCaller(string url);
		virtual string checkConnection(string check_messsage);
		virtual string checkStorage(string check_messsage);
		virtual string uploadPartOfFile(string part_of_file);
		virtual string downloadFile(string upload_message);
};


#endif



