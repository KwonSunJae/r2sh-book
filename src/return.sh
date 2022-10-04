#! /bin/bash
bid=$2
if [ $bid == "00000100" ]
then
    echo "----------Loan Info-----------"
    echo "bookName: [sunjae is handsome]"
    echo "loanUser: [sunjae]"
    echo "------------------------------"
    echo "The book return has been successfully"
elif [ $bid == "10000000" ] 
then
    echo "Please check your bookID. No search result found."
elif [ $bid == "00000000" ] 
then
    echo "This book was aleady loaned!. You can't loan this book."
fi