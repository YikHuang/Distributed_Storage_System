Original download link:
https://github.com/YikHuang/Distributed_Storage_System
=====

+ Milestone (0) ideas, plan, and structure

=====

+ Milestone (1) the architecture

=====

- Milestone (2) complete the functions
  // Assume the edge server is up and all nodes are ready to connect to the server
  // edge server: http://127.0.0.1:8080/
  // node1: http://127.0.0.1:9001/
  // node2: http://127.0.0.1:9002/
  // node3: http://127.0.0.1:9003/
  // node4: http://127.0.0.1:9004/
  // Uploading case: node1 is uploading
  // Downloading case: node2,  3, and 4 are able to download

  + Uploading case: 
	Step 1: Register the node
	Step 2: Check the edge server connection
	Step 3: Upload the file metadata to edge server
	Step 4: Check nodes connection and storage by edge server
	Step 5: Upload part(s) of file to all other nodes

  + Downloading:
	Step 1: Register the node
	Step 2: Check the edge server connection
	Step 3: Download the file metadata to the current node
	Step 4: Check nodes connection and storage by edge server
	Step 5: Download other parts of file from all other nodes
=====
