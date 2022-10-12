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
python3 amalgamate.py
cp -r jsoncpp/dist/* src
gcc ~/r2sh-book/src/show.cpp -o ~/r2sh-book/build/show.o -lsdtdc++
gcc ~/r2sh-book/src/search.cpp -o ~/r2sh-book/build/search.o -lsdtdc++
gcc ~/r2sh-book/src/loan.cpp -o ~/r2sh-book/build/loan.o -lsdtdc++
gcc ~/r2sh-book/src/return.cpp -o ~/r2sh-book/build/return.o -lsdtdc++
gcc ~/r2sh-book/src/info.cpp -o ~/r2sh-book/build/info.o -lsdtdc++
gcc ~/r2sh-book/src/auth.cpp -o ~/r2sh-book/build/auth.o -lsdtdc++
gcc ~/r2sh-book/src/check.cpp -o ~/r2sh-book/build/check.o -lsdtdc++

chmod 777 build/*
echo "----COMPLETE-----"
kill -9 $SPIN_PID