
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

    void Read(){ // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임. 
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


        //값을 뽑는 방법
        cout<<" User Name list"<<endl;
        for(int i =0; i<root["users"].size(); i++){ //배열은 이런식으로
            cout<<" name: "<<root["users"][i]["uName"]<<endl;
        }   

    }

    void Write(){ // 똑같이 여기서는 json file 쓰고 수정해서 원래 파일로 넣는 함수임. 원하는 대로 수정 ㄲ.
        //여기 함수에서는Users에 User 하나를 추가하는 함수임.
        ofs.open(filedata);
        Json::Value users; // 여기다 user 계속 추가

        Json::Value user; // 여기가 객체 하나를 계속 작성하는거
        
        user["uId"] = "000000";
        user["uName"] = "sunjae";
        
        //속성중에 배열이 있으면 따로 할당해서 해야됨
        Json::Value urshes;
        urshes.append("1");
        urshes.removeIndex(0,nullptr);
        

        user["uR2shs"] = urshes;    //배열은 이런식으로 추가
        user["uPenalty"] = "0000-00-00";

        

        users.append(user); //리스트에 넣어주고 아래에서


        root["users"] = users; // 여기서 마무리~
        //  파일 쓸때 형식임 건들 ㄴㄴ
        Json::StreamWriterBuilder builder;
	    builder["commentStyle"] = "None";
	    builder["indentation"] = "    ";  // Tab
	    unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        ///////////////////////////////////////
        
	    // 알파벳 순으로 write 된다.
	    //writer->write(root, &cout); cout 출력하고 싶을때
	    writer->write(root, &ofs); // 여기다가 root를 쓰는거임.
	    //cout << endl;  // add lf and flush

	    ofs.close();
        
    }
    void userAdd(int n, string uName){ // 똑같이 여기서는 json file 쓰고 수정해서 원래 파일로 넣는 함수임. 원하는 대로 수정 ㄲ.
        //여기 함수에서는Users에 User 하나를 추가하는 함수임.
        ofs.open(filedata);
        Json::Value users= root["users"]; // 여기다 user 계속 추가

        Json::Value user; // 여기가 객체 하나를 계속 작성하는거
        string tmp =to_string(n);
        while(tmp.length()!=6){
            tmp = "0"+tmp;
        }
        user["uId"] = tmp;
        cout<<uName<<" Welcome!" <<endl;
        cout<<"Your library membership number is ["<<tmp<<"]."<<endl;
        user["uName"] = uName;
        
        //속성중에 배열이 있으면 따로 할당해서 해야됨
        Json::Value urshes;
        urshes.append("1");
        urshes.removeIndex(0,nullptr);

        user["uR2shs"] = urshes;    //배열은 이런식으로 추가
        user["uPenalty"] = "0000-00-00";

        users.append(user); //리스트에 넣어주고 아래에서

        root["users"] = users; // 여기서 마무리~
        //  파일 쓸때 형식임 건들 ㄴㄴ
        Json::StreamWriterBuilder builder;
	    builder["commentStyle"] = "None";
	    builder["indentation"] = "    ";  // Tab
	    unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        ///////////////////////////////////////
        
	    // 알파벳 순으로 write 된다.
	    //writer->write(root, &cout); cout 출력하고 싶을때
	    writer->write(root, &ofs); // 여기다가 root를 쓰는거임.
	    //cout << endl;  // add lf and flush

	    ofs.close();
        
    }
    const int usersCount(){
        ifs = ifstream(filedata);
        Json::CharReaderBuilder builder;
	    builder["collectComments"] = false;
	    JSONCPP_STRING errs;
	    bool ok = parseFromStream(builder, ifs, &root, &errs); // root에 모든 데이터 들어가있음.
	    if (!ok){
            cout<<"Parse Error : Please Check your data File"<<endl;
            exit(EXIT_FAILURE);
            return -1;
        }


        

        return root["users"].size();
    }




};
class Users{
    public:
    string uId;
    string uName;
    vector<string> uR2shs;
    string uPenalty;
    Users(){
        vector<string> t;
        Users("","",t,"0000-00-00");
    };
    Users(string uid, string uname, vector<string> ur2shs, string upenalty){
        uId = uid;
        uName= uname;
        for (int i=0; i<ur2shs.size(); i++){
            uR2shs.push_back(ur2shs[i]);
        }
        uPenalty = upenalty;

    }
};
class userService{
public:
    int n;
    JsonParser jp;
    
    userService(){
        n = jp.usersCount();
    }
    void addUser(string userName){
        jp.userAdd(n,userName);
    }
};
int main (int argc, char* argv[]){
    if(argc != 3){
        cout<< "r2sh-book:: Please check your command."<<endl;
        return -1;
    }
    if(strlen(argv[2])>20){
        cout<<"Please Check your Name. Too LONG!" << endl;
        return -1;
    }
    userService us;
    us.addUser(argv[2]);

    return 0;
}   
