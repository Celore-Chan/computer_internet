#include<iostream>
#include<string.h>
#include<thread>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<thread>

#define BUFFER_SIZE 1024
#define PORT 8888
using namespace std;

void recvm(int clientSocket){
	while(true){
		char buffer[BUFFER_SIZE];

                memset(buffer,0,sizeof(buffer));
                int bytesReceived=recv(clientSocket,buffer,sizeof(buffer),0);
                if(bytesReceived<=0){
                        cout<<"客户端断开连接"<<endl;
                        break;
                }
                cout<<buffer<<"\n\n";
	}
}

int main(){
	int serverSocket=socket(AF_INET,SOCK_STREAM,0);
	if(serverSocket==-1){
		cerr<<"无法创建服务器socket"<<endl;
		return -1;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(PORT);
	serverAddr.sin_addr.s_addr=INADDR_ANY;

	if(bind(serverSocket,(sockaddr*)&serverAddr,sizeof(serverAddr))){
			cerr<<"绑定失败"<<endl;
			return -1;
	}

	if(listen(serverSocket,1)){
		cerr<<"监听失败"<<endl;
		return -1;
	}

	cout<<"等待客户端连接..."<<endl;

	sockaddr_in clientAddr;
	socklen_t clientAddrSize=sizeof(clientAddr);
	int clientSocket=accept(serverSocket,(sockaddr*)&clientAddr,&clientAddrSize);
	if(clientSocket==-1){
		cerr<<"连接客户端失败"<<endl;
		return 1;
	}
	cout<<"客户端已连接(输入\"exit\"关闭连接)"<<endl;

	thread receiveder(recvm,clientSocket);
	receiveder.detach();

	while(true){
		string name="server:";
		string message;
                
                getline(cin,message);
		if(message=="exit")break;
		else if(message.size()>BUFFER_SIZE){
                        cout<<"输入超出限定字符数，请重新输入"<<endl;
                        continue;
                }
		else if(message.size()==0){
			cout<<"输入不能为空"<<endl;
			continue;
		}

		message=name+message;
                send(clientSocket,message.c_str(),message.size()+1,0);
		cout<<"\n";
	}

	close(clientSocket);
	close(serverSocket);
	return 0;
}
