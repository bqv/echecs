#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

using std::string;
using std::cout;
using std::endl;
using std::cerr;

class network
{
	private:
		struct addrinfo *res;
		string currentBuffer;
		int sockfd;
	public:
		//initializer takeing the hostname and port (as a string)
		network(string hostname, string port);
		//a version of recv with a timeout (in microseconds, will block until then)
		int recvTimeout(int s, char *buf, int len, int timeout);
		//recieve a message from the network (put in the buffer, returns message length)
		int recieveMsg(string &buffer);
		//send a message to the network not including newline (returns the number of bytes send)
		int sendMsg(string message);
};

#endif
