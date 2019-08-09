#include "NetworkingManager.hpp"
#include "SocketManager.hpp"
#include "SocketException.hpp"

#include <iostream>
#include <string>

#include <errno.h>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>

using namespace std;
using namespace SockWrapperForCplusplus;

const ssize_t sendData(Socket* _targetServer, const void* _sendData, const size_t _dataSize, const int _flag=0) {

	size_t dataSize = _dataSize;
	if( _dataSize == 0)
		throw SocketDataSizeZeroException("size of sendData arg is Zero");

	return send( _targetServer->getDiscripter(), (void*)_sendData, dataSize, _flag);

}

const ssize_t recvData(Socket* _recvServer, void* _readData, const int _flag, const size_t _dataSize) {

	size_t dataSize = _dataSize;
	if( dataSize == 0 ) 
		throw SocketDataSizeZeroException("size of recvData arg is zero.");
	
	return recv( _recvServer->getDiscripter(), _readData, dataSize, _flag);

}
