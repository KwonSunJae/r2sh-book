#! /bin/bash
uid=$2
bid=$3
if [ $bid == "00000100" ]
then
    echo "----------Loan Info-----------"
    echo "bookName: [sunjae is handsome]"
    echo "loanUser: [sunjae]"
    echo "------------------------------"
    echo "The book loan has been successfully"
    echo "The return deadline is 2022-10-11."
elif [ $uid == "100000" ] 
then
    echo "Please check your userID. No search result found."
elif [ $bid == "10000000" ] 
then
    echo "Please check your bookID. No search result found."
elif [ $bid == "00000000" ] 
then
    echo "This book was aleady loaned!. You can't loan this book."
elif [ $uid == "000000" ] 
then
    ehco "You can't borrow a book now. Penalty deadline: 2022-10-12 "
fi