
#include <iostream>
#include <string>

#include "SockWrapper/ClientSocketManager.hpp"
#include "SockWrapper/NetworkingManager.hpp"
#include "SockWrapper/ServerSocketManager.hpp"
#include "SockWrapper/SocketManager.hpp"
#include "SockWrapper/Socket.hpp"
#include "SockWrapper/SocketException.hpp"


//#include "SockWrapper/SockWrapperLib.hpp"

using namespace std;
using namespace SockWrapperForCplusplus;

int main(void) {

    Socket mySocket("127.0.0.1", 12000, true); //<서버자신의 소켓 생성

    string getData;
    string data = "ok client";

    //소켓 생성
    if(!setSocket(&mySocket)) {
        cout << "setSocket() error!";
        return 0;
    }

    //REUSE_ADDR 설정
    int setOpt = 1; //true
    if(!setSocketOption(&mySocket, SOL_SOCKET, SO_REUSEADDR, (void*)(&setOpt), sizeof(setOpt))) {
        cout << "setSocketOption() error" << endl;
        return 0;
    }

    //bind
    if(!bindSocket(&mySocket)) {
        cout << "bindSocket() error" << endl;
        closeSocket(&mySocket);
        return 0;
    }

    //listen
    if(!listenClient(&mySocket, 1)) {
        cout << "listenClient() error" << endl;
        closeSocket(&mySocket);
        return 0;
    }

    //클라이언트 소켓 생성
    Socket clientSocket; //아무것도 없는 상태로 초기화

    //accept
    if(!acceptClient(&mySocket, &clientSocket)) {

        cout << "acceptClient() error" << endl;
        closeSocket(&mySocket);
        return 0;
    }
    char recvBuffer[128] = {0};

    //데이터 수신
    if( recvData(&clientSocket, recvBuffer, 128) <= 0) {
        cout << "recvData() error" << endl;
        
        closeSocket(&clientSocket);
        closeSocket(&mySocket);
        return 0;
    }

    cout << "From Client : " << recvBuffer << endl;

    //데이터 송신
    char* sendToData = (char*)(data.c_str());
    if( sendData(&clientSocket, sendToData, data.length()) <= 0) {
        cout << "sendData() error" << endl;
        
        closeSocket(&clientSocket);
        closeSocket(&mySocket);
        return 0;
    }

    cout << "To Client : " << data << endl;

    closeSocket(&clientSocket);
    closeSocket(&mySocket);

    return 0;
}