#include <iostream>
#include <fstream>
#include "json/json.h"
#include <string>
#include <stdio.h>
#include <ctime>
#include <time.h>

#include "util/ExceptionManager.h"
#include "util/BookRepository.h"

using namespace std;
string get_format_00(int);
string get_today();
string get_penalty_date(string);
void return_book(string, Json::Value, vector<Book>);

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

    void Write(Json::Value data, string key)
    {
        ofs.open(filedata);
        // cout << r2shs << endl;
        root[key] = data; // 여기서 마무리~
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

string get_today()
{
    time_t timer;
    struct tm *t;
    timer = time(NULL);
    t = localtime(&timer);
    time_t time = mktime(t);

    return to_string(t->tm_year + 1900) + "-" + to_string(t->tm_mon + 1) + "-" + to_string(t->tm_mday);
}
int find_r2sh(string rBId, Json::Value r2shs)
{
    for (int i = 0; i < r2shs.size(); i++)
    {
        if (r2shs[i]["rBid"] == rBId && r2shs[i]["rDate"] == "0000-00-00") // bid 가 존재하며, 반납되지 않은책 찾음.
        {
            return i;
        }
    }
    return -1;
}
string get_format_00(int prev)
{
    size_t n = 2;

    int precision = n - min(n, to_string(prev).size());
    return string(precision, '0').append(to_string(prev));
}
string get_penalty_date(string deadline)
{
    time_t timer;
    struct tm time_dead;

    time_dead.tm_year = stoi(deadline.substr(0, 4)) - 1900;
    time_dead.tm_mon = stoi(deadline.substr(5, 2)) - 1;
    time_dead.tm_mday = stoi(deadline.substr(8, 2));
    time_dead.tm_hour = 0;
    time_dead.tm_min = 0;
    time_dead.tm_sec = 0;

    time_t dead_t = mktime(&time_dead);
    time_t now_t = time(NULL);
    cout << "dead : " << dead_t << endl;
    cout << "now  : " << now_t << endl;

    if (now_t - dead_t > 0)
    {
        long long res = now_t + now_t - dead_t;
        cout << res << endl;
        time_t temp;
        temp = (time_t)res;

        cout << temp << endl;
        struct tm penaltyDate;
        struct tm time_now;
        localtime_r(&temp, &penaltyDate);
        localtime_r(&now_t, &time_now);

        cout << "now time" << to_string(time_now.tm_year + 1900) + "-" + get_format_00(time_now.tm_mon + 1) + "-" + get_format_00(time_now.tm_mday) << endl;
        cout << "deadline" << deadline << endl;
        cout << "penalty " << to_string(penaltyDate.tm_year + 1900) + "-" + get_format_00(penaltyDate.tm_mon + 1) + "-" + get_format_00(penaltyDate.tm_mday) << endl;

        string return_res = (to_string(penaltyDate.tm_year + 1900) + "-" + get_format_00(penaltyDate.tm_mon + 1) + "-" + get_format_00(penaltyDate.tm_mday));
        cout << "returning : " << return_res << endl;
        return return_res;
    }
    else
    {
        return "0000-00-00";
    }
}
void return_book(string rBid, Json::Value r2shs, vector<Book> bookList)
{

    string res;

    // check rBid's length is 8
    if (rBid.length() != 8)
    {
        cout << "Invalid Argument\n";
        ExceptionManager::printHelp();

        exit(EXIT_FAILURE);
    }
    int r2shIndex = find_r2sh(rBid, r2shs);
    if (r2shIndex == -1)
    {
        cout << "Please check ur bookID. No search result found\n";
        exit(EXIT_FAILURE);
    }

    int bookIndex = BookRepository::findOneByBookId(&bookList, rBid);
    if (bookIndex == -1)
    {
        cout << "Please check ur bookID. No search result found" << endl;
        exit(EXIT_FAILURE);
    }

    Book book = bookList.at(bookIndex);

    Json::Value users = JsonParser("../data/Users.json").Read("users");
    int userIndex = -1;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]["uId"] == r2shs[r2shIndex]["rUid"])
        {
            userIndex = i;
        }
    }
    if (userIndex == -1)
    {
        cout << "User is not exist" << endl;
        exit(EXIT_FAILURE);
    }
    res = get_penalty_date(r2shs[r2shIndex]["rDeadline"].asString());
    cout << "dddddddd" << endl;
    if (res != "0000-00-00")
    {
        if (users[userIndex]["uPenalty"].asString() == "0000-00-00")
        {
            users[userIndex]["uPenalty"] = res;
        }
        else
        {
            users[userIndex]["uPenalty"] = res;
            // users[userIndex]["uPenalty"] = max(users[userIndex]["uPenalty"].asString(), res);
        }
        cout << "penalty occured.\n"
             << "loanUser: " << users[userIndex]["uName"] << "penalty date : ~" << users[userIndex]["uPenalty"] << endl;
    }

    vector<Json::Value> temp;
    for (int i = 0; i < users[userIndex]["uR2shs"].size(); i++)
    {
        if (users[userIndex]["uR2shs"][i] != r2shs[r2shIndex]["rId"].asInt())
        {
            temp.push_back(users[userIndex]["uR2shs"][i]);
        }
    }
    users[userIndex]["uR2shs"].clear();
    for (int i = 0; i < temp.size(); i++)
    {
        users[userIndex]["uR2shs"].append(temp[i]);
    }

    // user 에 정보 저장 (penalty)

    cout << "---------------Loan Info---------------\n";
    cout << "bookName : [" << book.getName() << "]\n";
    cout << "loanUser : [" << users[userIndex]["uName"] << "]\n";
    cout << "---------------------------------------\n";

    r2shs[r2shIndex]["rDate"] = get_today();
    //연체여부판단.
    cout << "The book return has been successfully" << endl;
    JsonParser("../data/Users.json").Write(users, "users");
    JsonParser("../data/R2shs.json").Write(r2shs, "r2shs");
}

int main(int argc, char **argv)
{
    string CMD = "return";
    if (argc != 3)
    {
        cout << "Invalid Number of Argument\n";
        ExceptionManager::printHelp();
        exit(EXIT_FAILURE);
    };
    if (CMD.compare(argv[1]) != 0)
    {
        cout << "r2sh-book : invalid command" << endl;
        exit(EXIT_FAILURE);
    }
    string bookR2shId = argv[2];

    Json::Value r2shs = JsonParser("../data/R2shs.json").Read("r2shs");
    vector<Book> bookList = BookRepository::getBookList("../data/Books.json");

    return_book(bookR2shId, r2shs, bookList);

    return 0;
}
