#include <iostream>
#include <ctype.h>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <set>
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
    set<string> uIdSet;
    set<int> r2shOfUserIdSet;

    JsonParserUser()
    {
        filedata = "../data/Users.json"; //대상 파일임
    }

    set<string> getIdSet() { return uIdSet; }
    set<int> getR2shIdSet() { return r2shOfUserIdSet; }
    void idChecker(Json::Value data)
    {
        string id = data.asString();

        for (char c : id)
        {
            if (c < '0' || c > '9')
            {

                exit(EXIT_FAILURE);
            }
        }
    }
    bool checkTab(string str)
    {
        int flag = 0;
        for (int i = 0; i < (int)str.length(); ++i)
        {

            if (!(isspace(str[i]) == 0) || (str.find("\b") != string::npos))
            {
                flag++;
            }
        }
        if (flag > 0)
            return false;
        else
            return true;
    }

    int checkDate(int year, int month, int day)
    {
        if (month >= 13 || month <= 0)
            return false;
        if ((month % 2 == 1)) // odd month
        {
            if (month <= 7)
                if (day <= 0 || day > 31)
                    return false;
                else // month > 7
                    if (day <= 0 || day > 30)
                        return false;
        }
        else // even month
        {
            if (month <= 6)
            {
                if (month == 2)
                {
                    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) // leap year
                    {
                        if (day <= 0 || day > 30)
                            return false;
                    }
                    else if (day <= 0 || day > 28)
                        return false;
                }
                if (day <= 0 || day > 30)
                    return false;
            }
            else
            { // month > 6
                if (day <= 0 || day > 31)
                    return false;
            }
        }
        return true;
    }
    int Read()
    { // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임.
        // std::cout << "read 실행" << std::endl;
        ifsUserJson = ifstream(filedata);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        bool ok = parseFromStream(builder, ifsUserJson, &root, &errs); // root에 모든 데이터 들어가있음.
        if (!ok)
        {
            cout << "Parse Error : Please Check your data File" << endl;
            exit(EXIT_FAILURE);
        }
        else
        {
            for (int i = 0; i < root["users"].size(); i++)
            {

                // cout<<"big "<<endl;
                if ((root["users"][i].isMember("uId")) && (root["users"][i].isMember("uName")) && (root["users"][i].isMember("uPenalty")) && (root["users"][i].isMember("uR2shs")))
                {
                    idChecker(root["users"][i]["uId"]);
                    if (!(checkTab((root["users"][i]["uId"]).asString()) == true))
                        exit(EXIT_FAILURE); // uId 개행문자 있으면
                    if (!(checkTab((root["users"][i]["uName"]).asString()) == true))
                        exit(EXIT_FAILURE); // uName 개행문자 있으면
                    // cout<<"1 "<<endl;
                    if (!root["users"][i]["uId"].isString())
                        exit(EXIT_FAILURE);
                    // cout<<"2 "<<endl;
                    if (root["users"][i]["uId"].asString().length() != 6)
                        exit(EXIT_FAILURE);
                    // cout<<"3 "<<endl;
                    if (!root["users"][i]["uName"].isString())
                        exit(EXIT_FAILURE);
                    // cout<<"4 "<<endl;
                    if (root["users"][i]["uName"].asString().length() > 20)
                        exit(EXIT_FAILURE);
                    // cout<<"5 "<<endl;
                    if (root["users"][i]["uR2shs"].size() > 5)
                        exit(EXIT_FAILURE);
                    // cout<<"6 "<<endl;
                    for (int su = 0; su < root["users"][i]["uR2shs"].size(); su++)
                    {
                        if (!root["users"][i]["uR2shs"][su].isInt())
                            exit(EXIT_FAILURE);
                        r2shOfUserIdSet.insert(root["users"][i]["uR2shs"][su].asInt());
                    }

                    // cout<<"7 "<<endl;
                    if (!root["users"][i]["uPenalty"].isString())
                        exit(EXIT_FAILURE);
                    string date = root["users"][i]["uPenalty"].asString();
                    string token;
                    int y, m, d;
                    stringstream ss(date);
                    getline(ss, token, '-');
                    stringstream ssInt(token);
                    // cout<<date << token <<endl;
                    if (token.length() != 4)
                        exit(EXIT_FAILURE);
                    ssInt >> y;
                    // cout<<"big "<<endl;
                    if (ssInt.fail())
                        exit(EXIT_FAILURE);
                    getline(ss, token, '-');
                    if (token.length() != 2)
                        exit(EXIT_FAILURE);
                    stringstream ssIntm(token);
                    ssIntm >> m;
                    if (ssIntm.fail())
                        exit(EXIT_FAILURE);
                    getline(ss, token, '-');
                    if (token.length() != 2)
                        exit(EXIT_FAILURE);
                    stringstream ssIntd(token);
                    ssIntd >> d;
                    if (ssIntd.fail())
                        exit(EXIT_FAILURE);
                    // cout<<"checkDate "<<endl;
                    if (date.compare("0000-00-00") != 0 && !checkDate(y, m, d))
                        exit(EXIT_FAILURE);

                    uIdSet.insert(root["users"][i]["uId"].asString());
                    continue;
                }
                exit(EXIT_FAILURE);
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
    set<string> bidSet;
    JsonParserBook()
    {
        filedata = "../data/Books.json"; //대상 파일임
    }

    set<string> getIdSet() { return bidSet; }
    bool checkSpace(string str)
    {
        int flag = 0;
        for (int i = 0; i < (int)str.length(); ++i)
        {

            if (str[i] == ' ')
            {
            }
            else if (!(isspace(str[i]) == 0) || (str.find("\b") != string::npos))
            {

                flag++;
            }
        }
        if (flag > 0)
            return false;
        else
            return true;
    }

    bool checkTab(string str)
    {
        int flag = 0;

        for (int i = 0; i < str.length(); ++i)
        {
            if (!(isspace(str[i]) == 0) || (str.find("\b") != string::npos))
            {

                flag++;
            }
        }
        if (flag > 0)
        {
            exit(EXIT_FAILURE);
            return false;
        }

        else
            return true;
    }
    void nameChecker(Json::Value data)
    {
        string name = data.asString();
        if (name.length() < 1 || name.length() > 50)
            exit(EXIT_FAILURE);
    }

    void idChecker(Json::Value data)
    {
        string id = data.asString();
        if (id.length() != 8)
            exit(EXIT_FAILURE);
        for (char c : id)
        {
            if (c < '0' || c > '9')
                exit(EXIT_FAILURE);
        }
    }

    void authorsChecker(Json::Value data)
    {
        if (data.size() > 5) exit(EXIT_FAILURE);
        if (data.size() == 0)
            exit(EXIT_FAILURE);
        for (int i = 0; i < data.size(); i++)
        {
            string author = data[i].asString();
            if (author.length() < 1 || author.length() > 50)
                exit(EXIT_FAILURE);
        }
    }

    void categorysChecker(Json::Value data)
    {
        if (data.size() > 5) exit(EXIT_FAILURE);
        if (data.size() == 0)
            exit(EXIT_FAILURE);
        for (int i = 0; i < data.size(); i++)
        {
            string category = data[i].asString();
            if (category.length() < 1 || category.length() > 50)
                exit(EXIT_FAILURE);
        }
    }

    void detailChecker(Json::Value data)
    {
        string detail = data.asString();
        if (detail.length() < 0 || detail.length() > 255)
            exit(EXIT_FAILURE);
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
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < root["books"].size(); i++)
        {
            nameChecker(root["books"][i]["bName"]);
            idChecker(root["books"][i]["bId"]);
            authorsChecker(root["books"][i]["bAuthors"]);
            categorysChecker(root["books"][i]["bCategorys"]);
            detailChecker(root["books"][i]["bDetail"]);
            checkSpace((root["books"][i]["bName"]).asString());

            checkTab((root["books"][i]["bId"]).asString());

            for (int j = 0; j < (root["books"][i]["bAuthors"]).size(); j++)
            {
                checkSpace((root["books"][i]["bAuthors"][j]).asString());
            }
            for (int j = 0; j < (root["books"][i]["bAuthors"]).size(); j++)
            {
                checkTab((root["books"][i]["bCategorys"][j]).asString());
            }
            bidSet.insert(root["books"][i]["bId"].asString());
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
        filedata = "../data/R2shs.json"; //대상 파일임
    }

    bool checkTab(string str)
    {
        int flag = 0;

        for (int i = 0; i < (int)str.length(); ++i)
        {

            if (!(isspace(str[i]) == 0) || (str.find("\b") != string::npos))
            {

                flag++;
            }
            if (flag > 0)
                return false;
            else
                return true;
        }
    }
    void idChecker(Json::Value data)
    {
        string id = data.asString();

        for (char c : id)
        {
            if (c < '0' || c > '9')
            {

                exit(EXIT_FAILURE);
            }
        }
    }
    int checkDate(int year, int month, int day)
    {
        if (month >= 13 || month <= 0)
            return false;
        if ((month % 2 == 1)) // odd month
        {
            if (month <= 7)
            {
                if (day <= 0 || day > 31)
                    return false;
            }
            else // month > 7
            {
                if (day <= 0 || day > 30)
                    return false;
            }
        }
        else // even month
        {
            if (month <= 6)
            {
                if (month == 2)
                {
                    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) // leap year
                    {
                        if (day <= 0 || day > 30)
                            return false;
                    }
                    else if (day <= 0 || day > 28)
                        return false;
                }
                if (day <= 0 || day > 30)
                    return false;
            }
            else
            { // month > 6
                if (day <= 0 || day > 31)
                    return false;
            }
        }
        return true;
    }
    int Read(set<string> bIdSet, set<string> uIdSet, set<int> r2shIdSet)
    { // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임.

        ifsR2shsJson = ifstream(filedata);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        bool ok = parseFromStream(builder, ifsR2shsJson, &root, &errs); // root에 모든 데이터 들어가있음.
        if (!ok)
        {
            cout << "Parse Error : Please Check your data File" << endl;

            exit(EXIT_FAILURE);
        }
        else
        {
            for (int i = 0; i < root["r2shs"].size(); i++)
            {
                //사이즈 확인
                // cout<<"1 "<<endl;

                if ((root["r2shs"][i].isMember("rId")) && (root["r2shs"][i].isMember("rUid")) && (root["r2shs"][i].isMember("rBid")) && (root["r2shs"][i].isMember("rDate")) && (root["r2shs"][i].isMember("rDeadline")))
                {
                    idChecker(root["r2shs"][i]["rUid"]);
                    idChecker(root["r2shs"][i]["rBid"]);
                }
                else
                    exit(EXIT_FAILURE);
                // cout<<"2 "<<endl;
                if (!(root["r2shs"][i]["rId"]).isInt() || !(0 <= root["r2shs"][i]["rId"].asInt() && root["r2shs"][i]["rId"].asInt() <= INT_MAX) || !((root["r2shs"][i]["rUid"]).asString().length() == 6) || !((root["r2shs"][i]["rBid"]).asString().length() == 8))
                    exit(EXIT_FAILURE);
                if (checkTab((root["r2shs"][i]["rId"]).asString()) == false)
                    exit(EXIT_FAILURE);
                
                /*
                @ hotfix
                - user 에서 유효한(데이터 파일에 존재하는) r2shId인지 check
                */    
                r2shIdSet.erase(root["r2shs"][i]["rId"].asInt());
                if (checkTab((root["r2shs"][i]["rUid"]).asString()) == false)
                    exit(EXIT_FAILURE);
                /*
                @ hotfix
                - r2shs 에서 유효한(데이터 파일에 존재하는) uid인지 check
                */
                if(uIdSet.find(root["r2shs"][i]["rUid"].asString()) == uIdSet.end())
                    exit(EXIT_FAILURE);

                if (checkTab((root["r2shs"][i]["rBid"]).asString()) == false)
                    exit(EXIT_FAILURE);

                /*
                @ hotfix
                - r2shs 에서 유효한(데이터 파일에 존재하는) bid인지 check
                */
                if(bIdSet.find(root["r2shs"][i]["rBid"].asString()) == bIdSet.end())
                    exit(EXIT_FAILURE);
                if (!root["r2shs"][i]["rDate"].isString())
                    exit(EXIT_FAILURE);
                string date = root["r2shs"][i]["rDate"].asString();
                string token;
                int y, m, d;
                stringstream ss(date);
                getline(ss, token, '-');
                stringstream ssInt(token);
                if (token.length() != 4)
                    exit(EXIT_FAILURE);
                ssInt >> y;
                if (ssInt.fail())
                    exit(EXIT_FAILURE);
                getline(ss, token, '-');
                if (token.length() != 2)
                    exit(EXIT_FAILURE);
                stringstream ssIntm(token);
                ssIntm >> m;
                if (ssIntm.fail())
                    exit(EXIT_FAILURE);
                getline(ss, token, '-');
                if (token.length() != 2)
                    exit(EXIT_FAILURE);
                stringstream ssIntd(token);
                ssIntd >> d;
                if (ssIntd.fail())
                    exit(EXIT_FAILURE);

                if (date.compare("0000-00-00") != 0 && !checkDate(y, m, d))
                    exit(EXIT_FAILURE);

                // cout<<"deadlin "<<endl;
                if (!root["r2shs"][i]["rDeadline"].isString())
                    exit(EXIT_FAILURE);
                date = root["r2shs"][i]["rDeadline"].asString();
                stringstream ss2(date);
                getline(ss2, token, '-');
                stringstream ssInts(token);
                // cout<<"1 "<<endl;
                if (token.length() != 4)
                    exit(EXIT_FAILURE);
                ssInts >> y;
                if (ssInts.fail())
                    exit(EXIT_FAILURE);

                // cout<<token <<endl;
                getline(ss2, token, '-');
                if (token.length() != 2)
                    exit(EXIT_FAILURE);
                stringstream ssIntms(token);
                ssIntms >> m;
                if (ssIntms.fail())
                    exit(EXIT_FAILURE);

                // cout<<token <<endl;
                getline(ss2, token, '-');
                if (token.length() != 2)
                    exit(EXIT_FAILURE);
                stringstream ssIntds(token);
                ssIntds >> d;
                if (ssIntds.fail())
                    exit(EXIT_FAILURE);
                // cout<<date <<"compare"<<y<<m<<d<<checkDate(y,m,d)<<endl;
                if (date.compare("0000-00-00") != 0 && !checkDate(y, m, d))
                    exit(EXIT_FAILURE);
            }
            
            /*
            @ hotfix
            - r2shs 에서 유효한(데이터 파일에 존재하는) uid인지 check
            */
            if(!r2shIdSet.empty())
                exit(EXIT_FAILURE);
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

    set<string> bIdSet, uIdSet;
    set<int> r2shIdSet;
    if ((access(filePath1.c_str(), F_OK) == 0) && (access(filePath2.c_str(), F_OK) == 0) && (access(filePath3.c_str(), F_OK) == 0)) //
    {
        /* 
        @ hotfix 10/24 00:27 
        - 이제 check 순서 반드시 지켜야함
        - Book -> User -> R2sh
        */
        JPbook.Read();
        bIdSet = JPbook.getIdSet();
        JPuser.Read();
        uIdSet = JPuser.getIdSet();
        r2shIdSet = JPuser.getR2shIdSet();

        JPr2sh.Read(bIdSet,uIdSet,r2shIdSet);
    }
    else
    {
        // std::cout << "INTEGRITY CHECK FAILED" << std::endl;
        exit(EXIT_FAILURE);
        // exit(1);
    }
    // 파일 파싱

    return 0;
}
