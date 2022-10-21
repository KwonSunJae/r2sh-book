
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json/json.h" //라이브러리 헤더파일
using namespace std;

class JsonParser{
public:
    Json::Value root; // Users 면 users의 배열 값들이 여기로 들어갈 예정 
    string filedata;
    ifstream ifs; // 파일 읽기
    ofstream ofs; // 파일 쓰기
    JsonParser(){
        filedata = "../data/Users.json"; //대상 파일임 
    }

    void Read(string target ){ // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임. 
        ifs = ifstream(filedata);
        Json::CharReaderBuilder builder;
	    builder["collectComments"] = false;
	    JSONCPP_STRING errs;
	    bool ok = parseFromStream(builder, ifs, &root, &errs); // root에 모든 데이터 들어가있음.
	    if (!ok){
            cout<<"Parse Error : Please Check your data File"<<endl;
            exit(EXIT_FAILURE);
            return ;
        }
        Json::Value t= target;

        //값을 뽑는 방법
        int i;
        bool flag=false;
        for( i =0; i<root["users"].size(); i++){ //배열은 이런식으로
            if(root["users"][i]["uId"].compare(t)){
                flag = true;
                break;
            }
        }   
        if(!flag){
            cout<<"r2sh-book:: No search results found."<<endl;
            return;
        }
        cout<<"User details."<<endl;
        cout<<"userName: ["<<root["users"][i]["uName"]<<"]"<<endl;
        cout<<"userId: ["<<root["users"][i]["uId"]<<"]"<<endl;
        cout<<"penalty: ["<<root["users"][i]["uPenalty"]<<"]"<<endl;
        cout<<"loanlist: [";

        R2shParser  rp;
        for(int j=0; j<root["users"][i]["uR2shs"].size();j++){
            int targetid =root["users"][i]["uR2shs"][j].asInt();
            cout<< rp.Read(targetid);
            if(j!=root["users"][i]["uR2shs"].size()-1)cout<<",";
        }
        return;
    }
    
};
class R2shParser{
public:
    Json::Value root; // Users 면 users의 배열 값들이 여기로 들어갈 예정 
    string filedata;
    ifstream ifs; // 파일 읽기
    ofstream ofs; // 파일 쓰기
    R2shParser(){
        filedata = "../data/R2shs.json"; //대상 파일임 
    }

    string Read(int target ){ // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임. 
        ifs = ifstream(filedata);
        Json::CharReaderBuilder builder;
	    builder["collectComments"] = false;
	    JSONCPP_STRING errs;
	    bool ok = parseFromStream(builder, ifs, &root, &errs); // root에 모든 데이터 들어가있음.
	    if (!ok){
            cout<<"Parse Error : Please Check your data File"<<endl;
            exit(EXIT_FAILURE);
            return ;
        }
        Json::Value t= target;

        //값을 뽑는 방법
        int i;
        bool flag=false;
        for( i =0; i<root["users"].size(); i++){ //배열은 이런식으로
            if(root["r2shs"][i]["rId"]== target){
                return root["r2shs"][i]["rBid"].asString();
            }
        }   
        
        cout<<"This is wrong Access. Data file is dumped. Please exec the init.sh"<<endl;
        string ret = "error";
        return ret;

    }
};


int main (int argc, char* argv[]){
    if(sizeof(argv[2])/sizeof(char)!=6){
        cout<<"Please Check your ID. ID's length is 6." << endl;
        return;
    }
    JsonParser jp;
    string s(argv[2]);
    
    jp.Read(  s );
    
    return;
} 