
#ifndef EDGE_CALLER_H
#define EDGE_CALLER_H

#include <iostream>
#include <vector>

using namespace std;

class EdgeCaller{

	private:
		string targetUrl;
	
	public:
		EdgeCaller(string url);
		virtual string registerNode(string nodeUrl);
		virtual string checkConnection(string temp);
		virtual string uploadFileMetadata(string nodeUrl, string metadata);
		virtual string downloadFileMetadata(string nodeUrl);
		virtual string confirmUploading(string temp);
    virtual vector<string> getUrls(string callingNode);

};


#endif


