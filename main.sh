#! /bin/bash

case "$1" in
                show)
                        bash ~/r2sh-book/build/show "$@";
                        ;;
                search)
                        bash ~/r2sh-book/build/search  "$@";
                        ;;
                loan)
                        bash ~/r2sh-book/build/loan  "$@";
                        ;;
                return)
                        bash ~/r2sh-book/build/return  "$@";
                        ;;
                info)
                        bash ~/r2sh-book/build/info  "$@";
                        ;;

                auth)
                        bash ~/r2sh-book/build/auth  "$@";

                        ;;
                help)
                        bash ~/r2sh-book/build/help  "$@";
                        ;;
                *)
                        echo "$@" "is wrong commands!";
                        bash ~/r2sh-book/build/help  "$@";
                        ;;
esac