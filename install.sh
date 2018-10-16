#!/bin/bash

#sed -i "38s/.*/\	const\ string\ szHome\ =\ ${1};/" src/uva-tool.cpp
g++ -g -Wall -Wextra -Wshadow -Wfloat-equal -pedantic -std=c++11 -O2 -Wformat=2 -Wconversion -lm -o uva-tool src/uva-tool.cpp
mkdir ~/.cache/uva-tool/
sudo mv uva-tool /usr/bin/
sudo mkdir /usr/share/uva-tool/
sudo cp pid-to-num.cvs /usr/share/uva-tool/


