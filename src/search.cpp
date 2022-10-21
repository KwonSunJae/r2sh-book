#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "json/json.h"
#include "util/BookRepository.h"
#include "util/ExceptionManager.h"

using namespace std;

const string CMD = "search";
const int ARGV_CMD = 1;
const int ARGV_BNAME = 2;

int main(int argc, char **argv) {
    if (argc != 3) {
        cout << "Invalid Number of Argument\n";
        ExceptionManager::printHelp();
        exit(EXIT_FAILURE);
    };
    if (CMD.compare(argv[ARGV_CMD])!=0) {
        cout << "Invalid Command\n";
        ExceptionManager::printHelp();
        exit(EXIT_FAILURE);
    };

    string bookName = argv[ARGV_BNAME];

    vector<Book> list = BookRepository::getBookList("../data/Books.json");
    vector<int> result = BookRepository::findAllByBookName(&list, bookName);
    if (result.empty()) {
        cout << "r2sh-book : No search result found\n"
        exit(EXIT_FAILURE);
    };
    for (int i = 0; i < result.size(); i++){
        cout << i+1 <<". ";
        list.at(result.at(i)).printLine();
    }
    
}