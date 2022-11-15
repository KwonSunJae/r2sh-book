
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json/json.h" //라이브러리 헤더파일
#include "util/BookRepository.h"
using namespace std;

class JsonParser
{
public:
    Json::Value root; // Users 면 users의 배열 값들이 여기로 들어갈 예정
    string filedata;
    ifstream ifs; // 파일 읽기
    ofstream ofs; // 파일 쓰기
    JsonParser(string filepath)
    {
        filedata = filepath; //대상 파일임
    }

    Json::Value Read(string key)
    { // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임.
        ifs = ifstream(filedata);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        bool ok = parseFromStream(builder, ifs, &root, &errs); // root에 모든 데이터 들어가있음.
        if (!ok)
        {
            cout << "Parse Error : Please Check your data File" << endl;
            exit(EXIT_FAILURE);
            return Json::Value(0);
        }

        //값을 뽑는 방법
        return root[key];
    }
};

class R2shParser
{
public:
    Json::Value root; // Users 면 users의 배열 값들이 여기로 들어갈 예정
    string filedata;
    ifstream ifs; // 파일 읽기
    ofstream ofs; // 파일 쓰기
    R2shParser()
    {
        filedata = "../data/R2shs.json"; //대상 파일임
    }

    string Read(int target)
    { // 함수 리턴을 객체로 하고 싶으면 원하는대로 수정하면됨. 파일 읽는 예제 코드임.
        // cout<<"this is example test print R2shParser Read argument is" << target<<endl;
        ifs = ifstream(filedata);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        bool ok = parseFromStream(builder, ifs, &root, &errs); // root에 모든 데이터 들어가있음.
        if (!ok)
        {
            cout << "Parse Error : Please Check your data File" << endl;
            exit(EXIT_FAILURE);
            string ret = "error";
            return ret;
        }
        Json::Value t = target;

        //값을 뽑는 방법
        int i;
        bool flag = false;
        for (i = 0; i < root["r2shs"].size(); i++)
        { //배열은 이런식으로
            int a = root["r2shs"][i]["rId"].asInt();
            if (a == target)
            {
                string ret = root["r2shs"][i]["rBid"].asString();
                cout << ret;
                ret = "";
                return ret;
            }
        }

        cout << "This is wrong Access. Data file is dumped. Please exec the init.sh" << endl;
        string ret = "error";
        return ret;
    }
    void infoBook(string bId)
    {
        Json::Value r2shs = JsonParser("../data/R2shs.json").Read("r2shs");
        vector<Book> list = BookRepository::getBookList("../data/Books.json");
        int result = BookRepository::findOneByBookId(&list, bId);
        if (result == -1)
        {
            cout << "r2sh-book : No search result found\n";
            exit(EXIT_FAILURE);
        }
        list.at(result).printOne();
        int bStat = isBookUnreturn(r2shs, bId);

        if (bStat == 1)
            cout << "Loan availabl]" << endl;
        else
            cout << "rushed : [X]" << endl;

        return;
    }
    int isBookUnreturn(Json::Value r2shs, string bId)
    {

        for (int i = 0; i < r2shs.size(); i++)
        {
            if (r2shs[i]["rBid"] == bId)
            {
                if (r2shs[i]["rDate"] == "0000-00-00")
                {
                    return 1;
                }
            }
        }
        return 0;
    }
};
class UserJsonParser
{
public:
    Json::Value root; // Users 면 users의 배열 값들이 여기로 들어갈 예정
    string filedata;
    ifstream ifs; // 파일 읽기
    ofstream ofs; // 파일 쓰기
    UserJsonParser()
    {
        filedata = "../data/Users.json"; //대상 파일임
    }

    void Read(string target)
    {
        ifs = ifstream(filedata);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        bool ok = parseFromStream(builder, ifs, &root, &errs); // root에 모든 데이터 들어가있음.
        if (!ok)
        {
            cout << "Parse Error : Please Check your data File" << endl;
            exit(EXIT_FAILURE);
            return;
        }
        Json::Value t = target;

        //값을 뽑는 방법
        int i;
        bool flag = false;
        for (i = 0; i < root["users"].size(); i++)
        { //배열은 이런식으로
            if (!root["users"][i]["uId"].compare(t))
            {
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            cout << "r2sh-book:: No search results found." << endl;
            return;
        }
        cout << "User details." << endl;
        cout << "userName: [" << root["users"][i]["uName"] << "]" << endl;
        cout << "userId: [" << root["users"][i]["uId"] << "]" << endl;
        cout << "penalty: [" << root["users"][i]["uPenalty"] << "]" << endl;
        cout << "loanlist: [";

        R2shParser rp;
        for (int j = 0; j < root["users"][i]["uR2shs"].size(); j++)
        {
            int targetid = root["users"][i]["uR2shs"][j].asInt();
            cout << rp.Read(targetid);
            if (j != root["users"][i]["uR2shs"].size() - 1)
                cout << ",";
        }
        cout << "]" << endl;
        return;
    }
};

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        cout << "Pleas Check your Commands." << endl;
        return -1;
    }
    string s(argv[2]);
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] > '9' && s[i] < '0')
        {
            cout << "Please Check Your Data file." << endl;
            return -1;
        }
    }
    if (s.length() == 6)
    {
        UserJsonParser jp;
        jp.Read(s);
    }
    else if (s.length() == 8)
    {
        R2shParser r;
        r.infoBook(s);
    }
    else
    {
        cout << s<<" is Wrong Commands" << endl;
        return -1;
    }

    return 0;
}
