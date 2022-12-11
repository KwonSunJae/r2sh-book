
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "json/json.h"  //라이브러리 헤더파일

// json 읽기
/*
@ username으로 사용자 찾기
@ 1. User.json -> username 으로 rid 리스트 뽑기
@ 2. 리스트 뽑은거 돌면서 r2shs 에서 해당 유저 대여리스트 뽑기
@ 3. 출력
*/

using namespace std;

class UserInfo {
   public:
    string uId;
    vector<string> borrows;

    void print() {
        printf("userID:[%s], recentBorrow: [",uId.c_str());
        for (size_t i = 0; i < borrows.size(); i++) {
            printf("%s", borrows.at(i).c_str());
            if (i != borrows.size() - 1) printf(",");
        }
        printf("]\n");
    }
};

class R2shParser {
   public:
    Json::Value root;  // Users 면 users의 배열 값들이 여기로 들어갈 예정
    string filedata;
    ifstream ifs;  // 파일 읽기
    ofstream ofs;  // 파일 쓰기
    R2shParser() {
        filedata = "../data/R2shs.json";  // 대상 파일임
    }

    /*
    @ Params
    @ list : uId list
    */
    vector<UserInfo> Read(const vector<string>& list) {  // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임.
        // cout<<"this is example test print R2shParser Read argument is" << target<<endl;
        ifs = ifstream(filedata);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        bool ok = parseFromStream(builder, ifs, &root, &errs);  // root에 모든 데이터 들어가있음.
        if (!ok) {
            exit(EXIT_FAILURE);
        }

        // 값을 뽑는 방법
        int i;
        bool flag = false;
        vector<UserInfo> infoList;
        for (int T = 0; T < list.size(); T++) {
            UserInfo ui;
            ui.uId = list[T];
            for (i = 0; i < root["r2shs"].size(); i++) {  // 배열은 이런식으로
                if (!root["r2shs"][i]["rUid"].compare(list[T])) {
                    ui.borrows.push_back(root["r2shs"][i]["rBid"].asString());
                }
            }
            infoList.push_back(ui);
        }
        return infoList;
    }
};

class UserParser {
   public:
    Json::Value root;  // Users 면 users의 배열 값들이 여기로 들어갈 예정
    string filedata;
    ifstream ifs;  // 파일 읽기
    ofstream ofs;  // 파일 쓰기
    UserParser() {
        filedata = "../data/Users.json";  // 대상 파일임
    }

    void Read(string target) {
        ifs = ifstream(filedata);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        bool ok = parseFromStream(builder, ifs, &root, &errs);  // root에 모든 데이터 들어가있음.
        if (!ok) {
            cout << "Parse Error : Please Check your data File" << endl;
            exit(EXIT_FAILURE);
            return;
        }
        Json::Value t = target;

        // 값을 뽑는 방법
        int i;
        vector<string> uIdList;
        bool flag = false;
        for (i = 0; i < root["users"].size(); i++) {  // 배열은 이런식으로
            if (!root["users"][i]["uName"].compare(t)) {
                uIdList.push_back(root["users"][i]["uId"].asString());
                flag = true;
            }
        }


        if (!flag) {
            cout << "r2sh-book:: No search results found." << endl;
            return;
        }

        R2shParser rp;
        vector<UserInfo> infoList;
        infoList = rp.Read(uIdList);
        printf("Search of Name : %s\n", target.c_str());
        for (int i = 0; i < infoList.size(); i++) {
            printf("%d. ", i);
            infoList[i].print();
        }
    }
};


int main(int argc, char* argv[]) {
    if (argc != 3) exit(1);
    string username = argv[2];
    UserParser up;
    up.Read(username);
}