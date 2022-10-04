#! /bin/bash
keyword=$2
if [ $keyword = "sunjae"]
then
    echo "Library search results.
1. bookName: [sunjae is nice], bookAuthor: [sunjae], bookID: [00000000]
2. bookName: [sunjae is handsome], bookAuthor: [sunjae], bookID: [00000100]
3. bookName: [sunjae is bad], bookAuthor: [subin], bookID: [000000200]"
else
    echo "r2sh-book:: No search results found"
fi