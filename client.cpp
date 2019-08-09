
#include <iostream>
#include <string>

#include "SockWrapper/ClientSocketManager.hpp"
#include "SockWrapper/NetworkingManager.hpp"
#include "SockWrapper/ServerSocketManager.hpp"
#include "SockWrapper/SocketManager.hpp"
#include "SockWrapper/Socket.hpp"
#include "SockWrapper/SocketException.hpp"

using namespace std;
using namespace SockWrapperForCplusplus;

int main(void) {

    Socket socket("127.0.0.1", 12000, false); //<서버로 연결하는 소켓 생성
    string data = "hello Server";

    //소켓 생성
    if(!setSocket(&socket)) {
        cout << "setSocket() error!";
        return 0;
    }

    //서버와 연결
    if(!connectToServer(&socket)) {
        cout << "connectToServer() error" << endl;
        closeSocket(&socket);
        return 0;
    }

    char* sendToData = (char*)(data.c_str());
    //서버에게 데이터 전송
    cout << "To server : " << data << endl;
    if(sendData(&socket, sendToData, data.length()) <= 0) {
        cout << "sendData() error" << endl;
        closeSocket(&socket);
        return 0;
    }

    //데이터 수신
    char recvBuffer[128] = {0};
    if(recvData(&socket, recvBuffer, 128) <= 0) {
        cout << "recvData() error" << endl;
        closeSocket(&socket);
        return 0;
    }

    cout << "From Server : " << recvBuffer << endl;

    closeSocket(&socket);
    return 0;
}