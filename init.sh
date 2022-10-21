#! /bin/bash

spin()
{
  spinner="/|\\-/|\\-"
  while :
  do
    for i in `seq 0 7`
    do
      echo -n "${spinner:$i:1}"
      echo -en "\010"
      sleep 1
    done
  done
}
spin &
SPIN_PID=$!
trap "kill -9 $SPIN_PID" `seq 0 15`
echo "-----Initalizing r2sh-book-----"
echo "-----Install essential packages-----"

sudo apt-get update -y -q
sudo apt-get install gcc gcc-9 g++ -y -q
gcc --version
sudo apt-get install git -y -q
sudo apt-get install python3 -y -q

echo "-----Alias Settings-----"
chmod 777 main.sh

cat << EOF >> ~/.bashrc
alias r2sh-book='bash ~/r2sh-book/main.sh "\$@"'
EOF
source ~/.bashrc
echo "----- BUILD -----"
git clone https://github.com/open-source-parsers/jsoncpp.git

cd jsoncpp

python3 ~/r2sh-book/jsoncpp/amalgamate.py
cd ~/r2sh-book
cp -r jsoncpp/dist/* src
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
kill -9 $SPIN_PID