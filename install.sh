g++ -g -Wall -Wextra -Wshadow -Wfloat-equal -pedantic -std=c++11 -O2 -Wformat=2 -Wconversion -lm -o uva-tool uva-tool.cpp
sudo mv uva-tool /usr/bin/
sudo mkdir /usr/share/uva-tool/
sudo cp pid-to-num.cvs /usr/share/uva-tool/
mkdir ~/.cache/uva-tool/

