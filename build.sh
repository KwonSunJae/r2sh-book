#! /bin/bash

cd src
g++ -o ../build/info info.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/search search.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/loan loan.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/return return.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/info info.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/info info.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/check check.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION

chmod 777 build/*
echo "----COMPLETE-----"
