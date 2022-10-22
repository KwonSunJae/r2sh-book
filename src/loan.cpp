#include<iostream>
#include<fstream>
#include "json/json.h"
#include<string>
#include<cstring>
#include<ctime>
#include<cctype>

using namespace std;
string make_time(int y,int m,int d);
string make_time2(int y,int m,int d);
int search(const Json::Value *v, string type,string key);
int check(string a,string b);
string make_time2(int y,int m,int d){
   switch(m){
      case 1:
      if(d>31){
         d-=31;
         m++;
         break;
      }
      case 2:
      if(y%4==0){
         if(d>29){
            d-=29;
            m++;
            break;
         }
      }else{
          if(d>28){
            d-=28;
            m++;
            break;
         }
      }
      case 3:
      if(d>31){
         d-=31;
         m++;
         break;
      }
      case 4:
      if(d>30){
         d-=30;
         m++;
         break;
      }
      case 5:if(d>31){
         d-=31;
         m++;
         break;
      }
      case 6:
      if(d>30){
         d-=30;
         m++;
         break;
      }
      case 7:
      if(d>31){
         d-=31;
         m++;
         break;
      }
      case 8:
      if(d>31){
         d-=31;
         m++;
         break;
      }
      case 9:
      if(d>30){
         d-=30;
         m++;
         break;
      }
      case 10:
      if(d>31){
         d-=31;
         m++;
         break;
      }
      case 11:
      if(d>30){
         d-=30;
         m++;
         break;
      }
      case 12:
      if(d>31){
         d-=31;
         m++;
         break;
      }
   }
   if(m>12){
      m-=12;
      y++;
   }

   string date=to_string(y);
    date.append("-");
   if(m<10){
      date.append("0");
   }
    date.append(to_string(m));
     date.append("-");
   if(d<10){
     date.append("0");
   }
    date.append(to_string(d));
   return date;
}
string make_time(int y,int m,int d){
   string date=to_string(y);
   date.append("-");
   if(m<10){
      date.append("0");
   }
    date.append(to_string(m));
   date.append("-");
   if(d<10){
     date.append("0");
   }
    date.append(to_string(d));
   return date;
}
int check(string a, string b){
   if(a.length()==6){
      if(b.length()==8){
         for(int i=0;i<6;i++){
            if(isdigit(a.at(i))==0)return 0;
         }
         for(int i=0;i<8;i++){
            if(isdigit(b.at(i))==0)return 0;
         }
          return 1;
            
       }
    }
   return 0;
}
   
int search(const Json::Value* v,string type,string key){
   int j = 0;
   Json::Value value = *v;
   for (const auto a : value) {
      if (a.get(type, "Empty").asString().compare(key) ==0) return j;
      j++;
      
   }
   return -1;
}
void loan(char* u, char*b) {
   ifstream bjson("../data/Books.json");
   ifstream rjson("../data/R2shs.json");
   ifstream ujson("../data/Users.json");
   Json::CharReaderBuilder builder;
   builder["collectComments"] = false;
   Json::CharReaderBuilder builder1;
   builder1["collectComments"] = false;
   Json::CharReaderBuilder builder2;
   builder2["collectComments"] = false;
   Json::Value bvalue;
   Json::Value rvalue;
   Json::Value uvalue;

   JSONCPP_STRING berrs;
   bool ok1 = parseFromStream(builder, bjson, &bvalue, &berrs);
   JSONCPP_STRING rerrs;
   bool ok2 = parseFromStream(builder1, rjson, &rvalue, &rerrs);
   JSONCPP_STRING uerrs;
   bool ok3 = parseFromStream(builder2, ujson, &uvalue, &uerrs);
   JSONCPP_STRING rerrs2;
   int check_uid,check_bid,check_rid;
   string ti;
   string bid(b);
   string uid(u);
//   if (ok1)if (ok2)if (ok3);
  
   if ((check_uid=search(&uvalue["users"],"uId",uid))!=-1) {
      time_t timer;
      struct tm*t;
      timer = time(NULL);
      t=localtime(&timer);
      int check_time1;
      check_time1=(t->tm_year + 1900)*10000+(t->tm_mon + 1)*100+t->tm_mday;
      ti=uvalue["users"][check_uid].get("uPenalty","").asString();
      string check_time2=ti;
      check_time2.replace(4,1,"");
      check_time2.replace(6,1,"");
      if (check_time1>=stoi(check_time2)) {
         if ((check_bid = search(&bvalue["books"], "bId", bid)) != -1) {//bid체크
            if ((check_rid=search(&rvalue["r2shs"],"rBid", bid)) == -1) {//book대여정보확인
            int k=0;
               for (const auto a : uvalue["users"][check_uid]["uR2shs"]) {
                  k++;
               }
               
               if(k<5){
                  string date = make_time(t->tm_year + 1900,t->tm_mon + 1,t->tm_mday);               
                  string date2 = make_time2(t->tm_year + 1900,t->tm_mon + 1,t->tm_mday+7);

                  cout << "---------Loan Info---------" << endl;
                  cout << "booKName: [" << bvalue["books"][check_bid].get("bName","").asString() << "]" << endl;
                  cout << "loanUser: [" << uvalue["users"][check_uid].get("uName", "").asString() << "]" << endl;
                  cout << "-------------------------" << endl;
                  cout << "The book laon has been successfully" << endl;
                  cout << "The return deadline is " << date2<< "." << endl;
                  ofstream rjson2("../data/R2shs.json");
                  Json::Value rvalue2;
                  ofstream ujson2("../data/Users.json");

                  int j=0;
                  for (const auto a : rvalue["r2shs"]) {
                     j++;
                  }
                  
              
                  uvalue["users"][check_uid]["uPenalty"]="0000-00-00";
                  uvalue["users"][check_uid]["uR2shs"].append(j);
               
                  rvalue2["rId"]=j;
                  rvalue2["rUid"] = uvalue["users"][check_uid]["uId"].asString();
                  rvalue2["rBid"] = bvalue["books"][check_bid]["bId"].asString();
                  rvalue2["rDate"] = "0000-00-00";//시간
                  rvalue2["rDeadline"] = date2;//시간+7
                  rvalue["r2shs"].append(rvalue2);
                   Json::StreamWriterBuilder builder4;
                  builder4["commentStyle"] = "None";
                  builder4["indentation"] = "    ";  // Tab
                  unique_ptr<Json::StreamWriter> writer(builder4.newStreamWriter());
                  writer->write(rvalue, &rjson2);
                  writer->write(uvalue, &ujson2);
                  cout << endl;  // add lf and flush
                  rjson2.close();
               }else cout<<"you already loaned 5books"<<endl;
                
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
         cout << "You can`t borrow a booknow. Penalty deadline:" <<ti<<"."<< endl;
      }
   }else{
      cout << "Please check your userID. No search result found." << endl;
   }
}
int main(int args, char**argv) {
   
   if (args == 4) {
      if(strcmp(argv[1],"loan")==0){
         if(check(argv[2],argv[3])==1){
            loan(argv[2],argv[3]);
         }
         else{
            cout<<"check your bid or uid."<<endl;
         }
      }
      else{
      cout<<"check command. "<<endl;
      }
   }
   else{
      cout<<"check your argument"<<endl;
   }
   return 0;
}
