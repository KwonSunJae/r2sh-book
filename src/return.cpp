#include <iostream>
#include <fstream>
#include "json/json.h"
#include <string>
#include <ctime>
#include <stdio.h>
#include <time.h>

#include "util/ExceptionManager.h"
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
int find_book(string rBId, Json::Value r2shs)
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

    if (now_t > dead_t)
    {
        int penalty = (now_t - dead_t) / (60 * 60 * 24);
        now_t = now_t + now_t - dead_t;
        struct tm *penaltyDate = localtime(&now_t);

        string month = get_format_00(penaltyDate->tm_mon + 1);
        string day = get_format_00(penaltyDate->tm_mday);

        return to_string(penaltyDate->tm_year + 1900) + "-" + month + "-" + day;
    }
    else
    {
        return "0000-00-00";
    }
}
void return_book(string rBid, Json::Value r2shs, vector<Book> bookList)
{

    // check rBid's length is 8
    if (rBid.length() != 8)
    {

        cout << "r2sh-book : invalid bId\n";
        exit(EXIT_FAILURE);
    }
    int index = find_book(rBid, r2shs);
    if (index == -1)
    {
        cout << "r2sh-book : no R2sh found\n";
        exit(EXIT_FAILURE);
    }

    int bookIndex = BookRepository::findOneByBookId(&bookList, rBid);
    if (bookIndex == -1)
    {
        cout << "r2sh-book : Book is not exist" << endl;
        exit(EXIT_FAILURE);
    }

    Book book = bookList.at(bookIndex);

    Json::Value users = JsonParser("../data/Users.json").Read("users");
    int userIndex = -1;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i]["uId"] == r2shs[index]["rUid"])
        {
            userIndex = i;
        }
    }
    if (userIndex == -1)
    {
        cout << "r2sh-book : User is not exist" << endl;
        exit(EXIT_FAILURE);
    }

    string res = get_penalty_date(r2shs[index]["rDeadline"].asString());
    if (res != "0000-00-00")
    {
        cout << "penalty occured.\n"
             << "loanUser: " << users[userIndex]["uName"] << "penalty date : ~" << res << endl;
        users[userIndex]["uPenalty"] = res;
        JsonParser("../data/Users.json").Write(users, "users");
    }

    // user 에 정보 저장 (penalty)

    cout << "return book" << endl;
    cout << "---------------Loan Info---------------\n";
    cout << "bookName : [" << book.getName() << "]\n";
    cout << "loanUser : [" << users[userIndex]["uName"] << "]\n";
    cout << "---------------------------------------\n";

    r2shs[index]["rDate"] = get_today();
    //연체여부판단.
    cout << "The book return has been successfully" << endl;
    JsonParser("../data/R2shs.json").Write(r2shs, "r2shs");
}

int main(int argc, char **argv)
{
    if (argv[1] != "return")
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