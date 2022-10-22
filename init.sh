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
if (( $EUID == 0 )); then
  echo "root is very dangerous. Please change your Account"
  echo $EUID
  exit
fi

echo $EUID
cd ~/r2sh-book
echo "-----Install essential packages-----"
echo "apt updating..."
sudo apt-get update -y -qq
echo "apt gcc g++ Installing..."

sudo apt-get install gcc gcc-9 g++ -y -qq

gcc --version

echo "-----Alias Settings-----"
chmod 777 main.sh
chmod 777 src/help.sh
cat << EOF >> ~/.bashrc
alias r2sh-book='bash ~/r2sh-book/main.sh "\$@"'
EOF
source ~/.bashrc
echo "----- BUILD -----"
cd src
g++ -o ../build/info info.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/search search.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/loan loan.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/return return.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/auth auth.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/check check.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION
g++ -o ../build/show show.cpp jsoncpp.cpp -I. -DJSON_IS_AMALGAMATION

cd ~/r2sh-book
echo "----COMPLETE-----"
kill -9 $SPIN_PID