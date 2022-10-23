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

    static int findOneByBookId(vector<Book>* list, string bookId) {
        for (int i = 0; i < list->size(); i++){
            if(bookId.compare(list->at(i).getId())==0) return i;
        }
        cout << "For complete";
        return -1;
    }

    static vector<int> findAllByBookName(vector<Book>* list, string bookName) {
        vector<int> res;
        for (int i = 0; i < list->size() && res.size() < 10; i++){
            if(list->at(i).getName().find(bookName)!=string::npos){
                res.push_back(i);
            }
        }
        return res;
    }
};