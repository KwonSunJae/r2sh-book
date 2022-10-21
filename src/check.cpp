#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "json/json.h" //라이브러리 헤더파일
using namespace std;

class JsonParserUser
{
public:
    Json::Value root; // Users 면 users의 배열 값들이 여기로 들어갈 예정
    string filedata;
    ifstream ifsUserJson;  // 파일 읽기
    ifstream ifsBooksJson; // 파일 읽기
    ifstream ifsR2shsJson; // 파일 읽기
    ofstream ofs;          // 파일 쓰기
    JsonParserUser()
    {
        filedata = "../data/Users.json"; //대상 파일임
    }

    int Read()
    { // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임.
        std::cout << "read 실행" << std::endl;
        ifsUserJson = ifstream(filedata);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        bool ok = parseFromStream(builder, ifsUserJson, &root, &errs); // root에 모든 데이터 들어가있음.
        if (!ok)
        {
            cout << "Parse Error : Please Check your data File" << endl;
            return -1;
        }
        else
        {
            for (int i = 0; i < root["users"].size(); i++)
            {
                std::cout << "uid: " << root["users"][i]["uId"] << std::endl;
                std::cout << "uName: " << root["users"][i]["uName"] << std::endl;
                std::cout << "uPenalty: " << root["users"][i]["uPenalty"] << std::endl;
                std::cout << "uR2shs: " << root["users"][i]["uR2shs"] << std::endl;
                if ((root["users"][i].isMember("uId")) && (root["users"][i]["uName"]) && (root["users"][i]["uPenalty"]) && (root["users"][i]["uR2shs"]))
                {
                    std::cout << "있어용~" << std::endl;
                    return 0;
                }
                else
                    return -1;
            }
        }
    }
};
class JsonParserBook
{
public:
    Json::Value root; // Users 면 users의 배열 값들이 여기로 들어갈 예정
    string filedata;
    ifstream ifsBooksJson; // 파일 읽기
    ofstream ofs;          // 파일 쓰기
    JsonParserBook()
    {
        filedata = "../data/Books.json"; //대상 파일임
    }

    int Read()
    { // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임.

        ifsBooksJson = ifstream(filedata);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        bool ok = parseFromStream(builder, ifsBooksJson, &root, &errs); // root에 모든 데이터 들어가있음.
        if (!ok)
        {
            cout << "Parse Error : Please Check your data File" << endl;

            return -1;
        }
        else
        {
            for (int i = 0; i < root["books"].size(); i++)
            {
                std::cout << "bName: " << root["books"][i]["bName"] << std::endl;
                std::cout << "bId: " << root["books"][i]["bId"] << std::endl;
                std::cout << "bAuthors: " << root["books"][i]["bAuthors"] << std::endl;
                std::cout << "bCategorys: " << root["books"][i]["bCategorys"] << std::endl;
                std::cout << "bDetail: " << root["books"][i]["bDetail"] << std::endl;
                if ((root["books"][i].isMember("bName")) && (root["books"][i]["bId"]) && (root["books"][i]["bAuthors"]) && (root["books"][i]["bCategory"]) && (root["books"][i]["bDetail"]))
                {
                    std::cout << "있어용~" << std::endl;
                    return 0;
                }
                else
                    return -1;
            }
        }
    }
};

class JsonParserR2sh
{
public:
    Json::Value root; // Users 면 users의 배열 값들이 여기로 들어갈 예정
    string filedata;
    ifstream ifsR2shsJson; // 파일 읽기
    ofstream ofs;          // 파일 쓰기
    JsonParserR2sh()
    {
        filedata = "../data/R2sh.json"; //대상 파일임
    }

    int Read()
    { // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임.

        ifsR2shsJson = ifstream(filedata);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        bool ok = parseFromStream(builder, ifsR2shsJson, &root, &errs); // root에 모든 데이터 들어가있음.
        if (!ok)
        {
            cout << "Parse Error : Please Check your data File" << endl;

            return -1;
        }
        else
        {
            for (int i = 0; i < root["r2shs"].size(); i++)
            {
                std::cout << "rId: " << root["r2shs"][i]["rId"] << std::endl;
                std::cout << "rUid: " << root["r2shs"][i]["rUid"] << std::endl;
                std::cout << "rBld: " << root["r2shs"][i]["rBld"] << std::endl;
                std::cout << "rDate: " << root["r2shs"][i]["rDate"] << std::endl;
                std::cout << "rDeadLine: " << root["r2shs"][i]["rDeadline"] << std::endl;
                if ((root["r2shs"][i].isMember("rId")) && (root["r2shs"][i]["rUid"]) && (root["r2shs"][i]["rBld"]) && (root["r2shs"][i]["rDate"]) && (root["r2shs"][i]["rDeadLine"]))
                {
                    std::cout << "있어용~" << std::endl;
                    return 0;
                }
                else
                    return -1;
            }
        }
    }
};
int main()
{
    JsonParserUser JPuser = JsonParserUser();
    JsonParserBook JPbook = JsonParserBook();
    JsonParserR2sh JPr2sh = JsonParserR2sh();

    // 파일 존재 여부 확인
    std::string filePath1 = "../data/Users.json";
    std::string filePath2 = "../data/Books.json";
    std::string filePath3 = "../data/R2shs.json";

    if ((access(filePath1.c_str(), F_OK) == 0) && (access(filePath2.c_str(), F_OK) == 0)) //&& (access(filePath3.c_str(), F_OK) == 0))
    {
        std::cout << "FILE EXIST" << std::endl;
        JPuser.Read();
        JPbook.Read();
        JPr2sh.Read();
    }
    else
    {
        std::cout << "INTEGRITY CHECK FAILED" << std::endl;

        // exit(1);
    }
    // 파일 파싱

    return 0;
}