#! /bin/bash

echo "
------------------------------------------------------------------------------
R2SH-BOOK COMMANDS!!
------------------------------------------------------------------------------
show  <book-id> : show detail for the book
search  <keyword> : serach book by keyword and show list
search -c <category> : serach book by category and show list
loan <user-id> <book-id> : borrow book by bid
return <book-id> : return book by bid
info <user-id>	: show list of books borrowed by the user
info <book-id>	: show you can borrow this book
auth <username> : generate unique user-id according to username
find <username> : find your userID by username
help : show available command list
------------------------------------------------------------------------------
"
