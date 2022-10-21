#! /bin/bash

case "$1" in
                show)
                        bash /home/ubuntu/r2sh-book/src/show.sh "$@";
                        ;;
                search)
                        bash /home/ubuntu/r2sh-book/src/search.sh "$@";
                        ;;
                loan)
                        bash /home/ubuntu/r2sh-book/src/loan.sh "$@";
                        ;;
                return)
                        bash /home/ubuntu/r2sh-book/src/return.sh "$@";
                        ;;
                info)
                        bash /home/ubuntu/r2sh-book/src/info.sh "$@";
                        ;;

                auth)
                        bash /home/ubuntu/r2sh-book/src/auth.sh "$@";

                        ;;
                help)
                        bash /home/ubuntu/r2sh-book/src/help.sh "$@";
                        ;;
                *)
                        echo "$@" "is wrong commands!";
                        bash /home/ubuntu/r2sh-book/src/help.sh "$@";
                        ;;
esac