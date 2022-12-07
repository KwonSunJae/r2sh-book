#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string helpMessage =
    "==========================================\n"
    "R2SH-BOOK COMMANDS!!\n"
    "==========================================\n"
    "show <book-id> : show detail for the book\n"
    "search <keyword> : search book by keyword and show list\n"
    "search -c <category> : serach book by category and show list\n"
    "loan <user-id> : borrow book by bid\n"
    "return  <book-id> : return book by bid\n"
    "info <user-id> : show list of books borrowed by the user\n"
    "info <book-id>	: show you can borrow this book\n"
    "auth <username> : generate unique user-id according to username\n"
    "help : show available command list\n";

class ExceptionManager
{
public:
    static void printHelp()
    {
        cout << helpMessage;
    }
};