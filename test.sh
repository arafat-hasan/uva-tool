#!/bin/bash

whoami
chmod +x install.sh
./install.sh $USERNAME
uva-tool -hunt -u felix_halim -r 10
echo | whoami
