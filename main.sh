#! /bin/bash
NOW_DIR=$(pwd)
cd ~/r2sh-book/src
case "$1" in
                show)
                        ~/r2sh-book/build/show "$@";
                        ;;
                search)
                           ~/r2sh-book/build/search  "$@";
                        ;;
                loan)
                           ~/r2sh-book/build/loan  "$@";
                        ;;
                return)
                           ~/r2sh-book/build/return  "$@";
                        ;;
                info)
                           ~/r2sh-book/build/info  "$@";
                        ;;

                auth)
                           ~/r2sh-book/build/auth  "$@";

                        ;;
                help)
                           ~/r2sh-book/build/help  "$@";
                        ;;
                *)
                        echo "$@" "is wrong commands!";
                           ~/r2sh-book/build/help  "$@";
                        ;;
esac

cd $NOW_DIR