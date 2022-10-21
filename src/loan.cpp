#include<iostream>
#include<fstream>
#include "json/json.h"
#include<string>
#include<ctime>

using namespace std;
int search(const Json::Value *v, string type,string key);
int search(const Json::Value* v,string type,string key){
   int j = 0;
   Json::Value value = *v;
   for (const auto a : value) {
      if (a.get(type, "Empty").asString().compare(key) ==0) return j;
      j++;
      
   }
   return -1;
}
void loan(char* uid, char*bid) {
   ifstream bjson("../data/Books.json");
   ifstream rjson("../data/R2shs.json");
   ifstream ujson("../data/Users.json");
   Json::CharReaderBuilder builder;
   builder["collectComments"] = false;
   Json::Value bvalue;
   Json::Value rvalue;
   Json::Value uvalue;

   JSONCPP_STRING berrs;
   bool ok1 = parseFromStream(builder, bjson, &bvalue, &berrs);
   JSONCPP_STRING rerrs;
   bool ok2 = parseFromStream(builder, rjson, &rvalue, &rerrs);
   JSONCPP_STRING uerrs;
   bool ok3 = parseFromStream(builder, ujson, &uvalue, &uerrs);
   JSONCPP_STRING rerrs2;
   bool ok4 = parseFromStream(builder, ujson, &uvalue, &uerrs);
   int check_uid,check_bid,check_rid;
   string ti;
//   if (ok1)if (ok2)if (ok3);
   if ((check_uid=search(&uvalue["users"],"uId",uid))!=-1) {
      if ((ti=uvalue["users"][check_uid].get("uPenalty","").asString()).compare("0000-00-00") != 0) {
         if ((check_bid = search(&bvalue["books"], "bId", bid)) != -1) {//bid체크
            if ((check_rid=search(&rvalue["r2shs"],"rBid", bid)) == -1) {//book대여정보확인
               time_t timer;
               struct tm*t;
               timer = time(NULL);
               t=localtime(&timer);
               string date = to_string(t->tm_year + 1900);
               date += "-";
               date.append(to_string(t->tm_mon + 1));
               date += "-";
               string date2 = date;
               date.append(to_string(t->tm_mday));
               date2.append(to_string(t->tm_mday + 7));
               cout << "---------Loan Info---------" << endl;
               cout << "booKName: [" << bvalue["books"][check_bid].get("bName","").asString() << "]" << endl;
               cout << "loanUser: [" << uvalue["users"][check_uid].get("uName", "").asString() << "]" << endl;
               cout << "-------------------------" << endl;
               cout << "The book laon has been successfully" << endl;
               cout << "The return deadline is " << date2<< "." << endl;
               ofstream rjson2("../data/R2shs.json");
               Json::Value rvalue2;
               int j=0;
               for (const auto a : rvalue["r2shs"]) {
                  j++;
               }
               rvalue2["rId"] = to_string(j);
               rvalue2["rUid"] = uvalue["users"][check_uid]["uId"].asString();
               rvalue2["rBid"] = bvalue["books"][check_bid]["bId"].asString();
               rvalue2["rDate"] = date;//시간
               rvalue2["rDeadline"] = date2;//시간+7
               rvalue["r2shs"].append(rvalue2);
               Json::StreamWriterBuilder builder;
               builder["commentStyle"] = "None";
               builder["indentation"] = "    ";  // Tab
               unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
               writer->write(rvalue, &rjson2);
               cout << endl;  // add lf and flush
               rjson2.close();
            }
            else {
               cout << "This book was aleady loaned!. you can`t loan this book.." << endl;
            }
         }
         else {
            cout << "Please check your bookID. No search result found." << endl;
         }
      }
      else {
         cout << "You can`t borrow a booknow. Penalty dealine: "<<ti<<"." << endl;
      }
   }else{
      cout << "Please check your userID. No search result found." << endl;
   }
}
int main(int args, char**argv) {
   if (args == 4) {
      loan(argv[2],argv[3]);
   }
   return 0;
}
