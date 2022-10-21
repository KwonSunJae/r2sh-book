#include <iostream>
#include <fstream>
#include "json/json.h"
#include <string.h>
#include <ctime>

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

    Json::Value Read()
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
        return root["r2shs"];
    }

    void makeUser(string uId, string uName)
    { // 똑같이 여기서는 json file 쓰고 수정해서 원래 파일로 넣는 함수임. 원하는 대로 수정 ㄲ.
        //여기 함수에서는Users에 User 하나를 추가하는 함수임.
        ofs.open(filedata);
        Json::Value users; // 여기다 user 계속 추가

        Json::Value user; // 여기가 객체 하나를 계속 작성하는거
        user["uId"] = uId;
        user["uName"] = uName;

        //속성중에 배열이 있으면 따로 할당해서 해야됨
        Json::Value urshes;
        urshes.append("1");
        urshes.append("2");
        urshes.append("3");

        user["uR2shs"] = urshes; //배열은 이런식으로 추가
        user["uPenalty"] = "0000-00-00";

        users.append(user); //리스트에 넣어주고 아래에서

        root["users"] = users; // 여기서 마무리~
        //  파일 쓸때 형식임 건들 ㄴㄴ
        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "    "; // Tab
        unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        ///////////////////////////////////////

        // 알파벳 순으로 write 된다.
        // writer->write(root, &cout); cout 출력하고 싶을때
        writer->write(root, &ofs); // 여기다가 root를 쓰는거임.
        // cout << endl;  // add lf and flush

        ofs.close();
    }

    void Write(Json::Value r2shs)
    {
        ofs.open(filedata);

        root["r2shs"] = r2shs; // 여기서 마무리~
        //  파일 쓸때 형식임 건들 ㄴㄴ
        Json::StreamWriterBuilder builder;
        builder["commentStyle"] = "None";
        builder["indentation"] = "    "; // Tab
        unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        ///////////////////////////////////////

        // 알파벳 순으로 write 된다.
        // writer->write(root, &cout); cout 출력하고 싶을때
        writer->write(root, &ofs); // 여기다가 root를 쓰는거임.
        // cout << endl;  // add lf and flush

        ofs.close();
    }
};
bool search_book_present(string rBId, Json::Value r2shs);
void return_book(string rBId, Json::Value r2shs);

bool search_book_present(string rBId, Json::Value r2shs)
{
    for (int i = 0; i < r2shs.size(); i++)
    {
        if (r2shs[i]["rBId"] == rBId)
        {
            cout << "book rush found" << endl;
            cout << "book name: " << r2shs[i]["rUid"] << r2shs[i]["rDeadline"] << endl;
            return true;
        }
    }
    return false;
}

void return_book(string rBId, Json::Value r2shs)
{
    if (search_book_present(rBId, r2shs))
    {
        //리턴 수행
        for (int i = 0; i < r2shs.size(); i++)
        {
            if (r2shs[i]["rBId"] == rBId && r2shs[i]["rDate"] == "0000-00-00") // bid 가 존재하며, 반납되지 않은책 찾음.
            {
                time_t timer;
                struct tm t;
                timer = time(NULL);
                localtime_s(&t, &timer);
                string date = to_string(t.tm_year + 1900);
                date += "-";
                date.append(to_string(t.tm_mon + 1));
                date += "-";
                date.append(to_string(t.tm_mday));
                r2shs[i]["rDate"] = date;
                //연체여부판단.
                cout << "book returned" << endl;
                cout << "book name: " << r2shs[i]["rUid"] << "rDate:" << r2shs[i]["rDate"] << endl;

                cout << "book rush removed" << endl;
                cout << r2shs << endl;
                JsonParser("../data/R2shs.json").Write(r2shs);
            }
        }
    }
    else
    {
        cout << "book is not exist" << endl;
        //없는 책이라고 알려주기
    }
    cout << r2shs[0]["rBId"] << endl;
}
int main(int args, char **argv)
{
    Json::Value r2shs = JsonParser("../data/R2shs.json").Read();
    // cout << r2shs[0]["rName"].asString().c_str() << endl;
    cout << argv[1] << endl;
    return_book(argv[1], r2shs);

    return 0;
}