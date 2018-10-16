#!/bin/bash

sudo apt install curl
chmod +x install.sh
./install.sh $USERNAME
uva-tool -hunt -u felix_halim -r 10

