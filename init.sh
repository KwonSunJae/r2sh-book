#! /bin/bash

function spinner() {
    local info="$1"
    local pid=$!
    local delay=0.75
    local spinstr='|/-\'
    while kill -0 $pid 2> /dev/null; do
        local temp=${spinstr#?}
        printf " [%c]  $info" "$spinstr"
        local spinstr=$temp${spinstr%"$temp"}
        sleep $delay
        local reset="\b\b\b\b\b\b"
        for ((i=1; i<=$(echo $info | wc -c); i++)); do
            reset+="\b"
        done
        printf $reset
    done
    printf "    \b\b\b\b"
}

echo "-----Initalizing r2sh-book-----"
echo "-----Install essential packages-----"

sudo apt-get update -y -qq && spinner "apt updating..."
sudo apt-get install gcc-9 g++-9 -y -qq && spinner "apt install gcc"
gcc --version
sudo apt-get install git -y -qq spinner " apt install git check"


echo "-----Alias Settings-----"
chmod 777 main.sh

cat << EOF >> ~/.bashrc
alias r2sh-book= 'bash ~/r2sh-book/main.sh "$@"'
EOF
source ~/.bashrc
echo "----- BUILD -----"
gcc ~/r2sh-book/src/show.cpp -o ~/r2sh-book/build/show.o -lsdtdc++
gcc ~/r2sh-book/src/search.cpp -o ~/r2sh-book/build/search.o -lsdtdc++
gcc ~/r2sh-book/src/loan.cpp -o ~/r2sh-book/build/loan.o -lsdtdc++
gcc ~/r2sh-book/src/return.cpp -o ~/r2sh-book/build/return.o -lsdtdc++
gcc ~/r2sh-book/src/info.cpp -o ~/r2sh-book/build/info.o -lsdtdc++
gcc ~/r2sh-book/src/auth.cpp -o ~/r2sh-book/build/auth.o -lsdtdc++
gcc ~/r2sh-book/src/check.cpp -o ~/r2sh-book/build/check.o -lsdtdc++

chmod 777 build/*
echo "----COMPLETE-----"
