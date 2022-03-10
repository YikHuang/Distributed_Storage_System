

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
		virtual string checkConnection(string temp);
		virtual string checkStorage(string temp);
		virtual string uploadPartOfFile(string temp);
		virtual string downloadFile(string temp);

};


#endif



