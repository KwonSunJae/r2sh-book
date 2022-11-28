#include <iostream>
#include <string>
#include <vector>

#include "json/json.h"

using namespace std;

class Book {
   private:
    string name;
    string id;
    vector<string> authors;
    vector<string> categorys;
    string detail;

   public:
    Book(Json::Value data) {
        name = data["bName"].asString();
        id = data["bId"].asString();
        for (int i = 0; i < data["bAuthors"].size(); i++) {
            authors.push_back(data["bAuthors"][i].asString());
        }

        for (int i = 0; i < data["bCategorys"].size(); i++) {
            categorys.push_back(data["bCategorys"][i].asString());
        }
        detail = data["bDetail"].asString();
    }
    void printOne() {
        cout << "Book details\n";
        cout << "bookName : [" << name << "],\n";
        cout << "bookAuthor : [";
        for (size_t i = 0; i < authors.size(); i++){
            if(i==authors.size()-1) cout <<authors.at(i);
            else cout << authors.at(i) << ",";
        }
    
        cout << "],\n";
        cout << "bookID : [" << id << "],\n";
        cout << "bookCategory : [";
        for (size_t i = 0; i < categorys.size(); i++){
            if(i==categorys.size()-1) cout <<categorys.at(i);
            else cout << categorys.at(i) << ",";
        }
        cout << "],\n";
        cout << "bookDetails : " << detail << endl;
    }

    void printLine() {
        cout << "bookName : [" << name << "], ";
        cout << "bookAuthor : [";
        for (string author : authors) {
            cout << author << ",";
        }
        cout << "], ";
        cout << "bookID : [" << id << "]\n";
    }

    string getId() { return id; }
    string getName() { return name; }
    vector<string>getcategorys(){return categorys;} 
};
