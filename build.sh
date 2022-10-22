#! /bin/bash

cd src
g++ -o ../build/info info.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION -std=c++17
g++ -o ../build/search search.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION -std=c++17
g++ -o ../build/loan loan.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION -std=c++17
g++ -o ../build/return return.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION -std=c++17
g++ -o ../build/info info.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION -std=c++17
g++ -o ../build/info info.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION -std=c++17
g++ -o ../build/check check.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION -std=c++17

chmod 777 build/*
echo "----COMPLETE-----"
