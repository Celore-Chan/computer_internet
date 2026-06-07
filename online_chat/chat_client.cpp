#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include<thread>

#define PORT 8888
#define BUFFER_SIZE 1024
using namespace std;

void recvm(int sock){
	while(true){
		char buffer[BUFFER_SIZE];

                memset(buffer,0,sizeof(buffer));
                int bytesReceived=recv(sock,buffer,sizeof(buffer),0);
                if(bytesReceived<=0){
                        cout<<"服务器断开连接"<<endl;
                        break;
                }
                cout<<buffer<<"\n\n";
	}
}

int main(){
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==-1){
		cerr<<"无法创建socket"<<endl;
		return -1;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(PORT);

	hostent* host=gethostbyname("localhost");
	if(host==nullptr){
		cerr<<"无法解析主机名"<<endl;
		return -1;
	}
	memcpy(&serverAddr.sin_addr,host->h_addr,host->h_length);

	if(connect(sock,(sockaddr*)&serverAddr,sizeof(serverAddr))<0){
		cerr<<"连接失败"<<endl;
		return -1;
	}

	cout<<"已连接到服务器！可以开始聊天了"<<endl;

	thread receiveder(recvm,sock);
	receiveder.detach();

	while(true){
		string name="client:";
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
                send(sock,message.c_str(),message.size()+1,0);
		cout<<"\n";
	}

	close(sock);
	return 0;
}
