#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "json/json.h"
#include "util/BookRepository.h"
#include "util/ExceptionManager.h"

using namespace std;

const string CMD = "search";
const string CMD2 = "-c";
const int ARGV_CMD = 1;
const int ARGV_BNAME = 2;
const int ARGV_TYPE = 2;
const int ARGV_CNAME = 3;

int main(int argc, char **argv) {
    if (argc != 3&&argc!=4) {
        cout << "Invalid Number of Argument\n";
        ExceptionManager::printHelp();
        exit(EXIT_FAILURE);
    };
    if (CMD.compare(argv[ARGV_CMD])!=0) {
        cout << "Invalid Command\n";
        ExceptionManager::printHelp();
        exit(EXIT_FAILURE);
    };
    if (argc==4&&CMD2.compare(argv[ARGV_TYPE])!=0) {
        cout << "Invalid Command\n";
        ExceptionManager::printHelp();
        exit(EXIT_FAILURE);
    };
    if(argc==3){
        string bookName = argv[ARGV_BNAME];

        vector<Book> list = BookRepository::getBookList("../data/Books.json");
        vector<int> result = BookRepository::findAllByBookName(&list, bookName);
        if (result.empty()) {
            cout << "r2sh-book : No search result found\n";
            exit(EXIT_FAILURE);
        };
        for (int i = 0; i < result.size(); i++){
            cout << i+1 <<". ";
            list.at(result.at(i)).printLine();
        }
    }else{
        string Category = argv[ARGV_CNAME];

        vector<Book> list = BookRepository::getBookList("../data/Books.json");
        vector<int> result = BookRepository::findAllByCategory(&list, Category);
        if (result.empty()) {
            cout << "r2sh-book : No search result found\n";
            exit(EXIT_FAILURE);
        };
        for (int i = 0; i < result.size(); i++){
            cout << i+1 <<". ";
            list.at(result.at(i)).printLine();
        }
    }
    
}
