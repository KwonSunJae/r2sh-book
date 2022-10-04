#! /bin/bash
if ["$3" = "00000100"]
then
    echo "The book loan has been successfully"
    echo "The return deadline is 2022-10-11."
else
    echo "Please check your commands."
    $HOME/r2sh-book/src/help.sh
fi