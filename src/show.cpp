#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "json/json.h"
#include "util/BookRepository.h"
#include "util/ExceptionManager.h"

using namespace std;

const string CMD = "show";
const int ARGV_CMD = 1;
const int ARGV_BID = 2;

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

    string bookId = argv[ARGV_BID];

    vector<Book> list = BookRepository::getBookList("../data/Books.json");
    int result = BookRepository::findOneByBookId(&list, bookId);
    if (result == -1) cout << "r2sh-book : No search result found\n";
    list.at(result).printOne();
}