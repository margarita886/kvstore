#include <iostream>
#include <sstream>
#include<string>
#include <map>
using namespace std;

int main(){

map<string, string> data;
string line;



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
        if(it == data.end()){ //key doesnt exist
            cout<<"KEY NOT FOUND. USE 'SET' to set a new key";
        } 
    else{
        cout<<it->second; // using the location of it find the value(2nd)
    }

    }
    else if(com=="DELETE"){
        data.erase(key);
    }

    else if(com=="EXIT"){
        ex=true;
    }


}

return 0;    
}