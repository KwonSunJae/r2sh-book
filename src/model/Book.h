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
    void print() {
        cout << "[" << id << "] " << name << endl;
        cout << "Authros : ";
        for (string author : authors) {
            cout << author << " ";
        }
        cout << "\nCategorys : ";
        for (string category : categorys) {
            cout << category << " ";
        }
        cout << "\nDetail : " << detail << endl;
    }
};