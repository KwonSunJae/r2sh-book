#include <iostream>
#include <fstream>

#include "../model/Book.h"
#include "json/json.h"

using namespace std;

class BookRepository {
   private:
    static Json::Value warmUp(string filePath) {
        Json::Value root;
        ifstream ifs = ifstream(filePath);
        Json::CharReaderBuilder builder;
        builder["collectComments"] = false;
        JSONCPP_STRING errs;
        if (!parseFromStream(builder, ifs, &root, &errs)) {
            cout << "Parse Error : Please Check your data File" << endl;
            exit(EXIT_FAILURE);
        }
        return root;
    }

   public:
    static vector<Book> getBookList(string filePath) {
        Json::Value root = warmUp(filePath);
        vector<Book> res;
        for (int i = 0; i < root["books"].size(); i++) {
            res.push_back(Book(root["books"][i]));
        }
        return res;
    }
};