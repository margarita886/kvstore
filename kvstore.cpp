    #include <iostream>
    #include <sstream>
    #include<string>
    #include <fstream>
    #include <map>
    #include <sys/socket.h>
    #include <netinet/in.h>
    using namespace std;

    int main(){


    map<string, string> data;
    string line;

    
    ifstream inFile("data.txt");
    string fileLine;
    //read into file
    while(getline(inFile, fileLine)){
        stringstream fs(fileLine);
        string k, v;
        getline(fs, k, ',');
        getline(fs, v, ',');
        data[k] = v;
    }




    int server_fd = socket(AF_INET, SOCK_STREAM, 0); //create socket
    if(server_fd==-1){
        cout<<"Failed to create socket";
    }

    sockaddr_in address; //setting address and portu
    address.sin_family = AF_INET;  //ipv4
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080); //set port


    int bind_result = bind(server_fd, (sockaddr*)&address, sizeof(address));
    if (bind_result == -1) {
        cout << "Failed to bind";
    }

    int lis_res = listen(server_fd, 5); //5 connections allowed - listen to request
    if (lis_res == -1){
        cout<<"Fail to listen";
    }
    int client_fd = accept(server_fd, nullptr, nullptr); //server fd is the socket thats listening
    if(client_fd == -1){ //client fd is the scoket for the clinet
        cout<<"Connection acceptance failed";
    }
    else
        cout<<"Client connected succesfully"<<endl;

    bool ex = false;
    while(ex==false){

        char buffer[1024] = {0};
        recv(client_fd, buffer, 1024, 0);
        string line(buffer);

        stringstream ss(line);
        string com;
        ss >> com;
        string key;
        ss >>key;
        string value;
        ss >>value;

        if(com=="SET"){
            data[key]=value;
        }
        else if(com=="GET"){
            auto it = data.find(key);
            if(it == data.end()){
                string response = "KEY NOT FOUND. USE 'SET' to set a new key\n";
                send(client_fd, response.c_str(), response.size(), 0);
            } 
        else{
            string response = it->second + "\n";
            send(client_fd, response.c_str(), response.size(), 0);
        }
        }
        else if(com=="DELETE"){
            data.erase(key);
        }

        else if(com=="EXIT"){
            ex=true;
        }
    }

    //write into file

    ofstream outFile("data.txt");
    for(pair<string,string> entry : data){
        outFile<<entry.first<<","<<entry.second<<endl;
    }
    outFile.close();
    return 0;    
    }
