#include <iostream>
#include <sstream>
#include<string>
#include<fstream>
#include <map>
using namespace std;

int main(){

map<string, string> data;
string line;

ifstream inFile("data.txt");
string fileLine;

while(getline(inFile, fileLine)){
    stringstream fs(fileLine);
    string k, v;
    getline(fs, k, ',');
    getline(fs, v, ',');
    data[k] = v;
}

bool ex = false;

while(ex==false){

    getline(cin , line);
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
            cout<<"KEY NOT FOUND. USE 'SET' to set a new key"<<endl;
        } 
    else{
        cout<<it->second<<endl;
    }

    }
    else if(com=="DELETE"){
        data.erase(key);
    }

    else if(com=="EXIT"){
        ex=true;
    }


}

ofstream outFile("data.txt");
for(pair<string,string> entry : data){
    outFile<<entry.first<<","<<entry.second<<endl;
}
outFile.close();

return 0;    
}