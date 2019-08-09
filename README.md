# TCP Socket Function Wrapper For C++
__Object__ : The Alternative TCP Socket Function for Boost Lib that requires much of disk memory
* 해당 C++ 프로젝트에 비해 어마어마하게 큰 용량의 Boot Library의 Socket Library를 대체하기 위해 임시방편으로 사용하는 Library


## Example Server-Client


### Server.cpp
<pre><code>

#include <iostream>
#include <string>

#include "SockWrapper/ServerSocketManager.hpp"
#include "SockWrapper/NetworkingManager.hpp"

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
</pre></code>



### Client.cpp
<pre><code>

#include <iostream>
#include <string>

#include "SockWrapper/ClientSocketManager.hpp"
#include "SockWrapper/NetworkingManager.hpp"

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
</pre></code>

