#!/bin/bash 
#
# FILE: vim_uva-tool_run_script.sh
#
# @author: Md. Arafat Hasan Jenin <arafathasanjenin[at]gmail[dot]com>
#
# LINK:
#
# DATE CREATED: 09-05-17 20:19:12 (+06)
# LAST MODIFIED: 05-10-17 15:07:06 (+06)
#
# DESCRIPTION:
#
# DEVELOPMENT HISTORY:
# Date         Version     Description
# --------------------------------------------------------------
# 09-05-17		1.0         File Created
#
#


##
##     ___          ___           ___                       ___
##    /  /\        /  /\         /__/\        ___          /__/\
##   /  /:/       /  /:/_        \  \:\      /  /\         \  \:\
##  /__/::\      /  /:/ /\        \  \:\    /  /:/          \  \:\
##  \__\/\:\    /  /:/ /:/_   _____\__\:\  /__/::\      _____\__\:\
##     \  \:\  /__/:/ /:/ /\ /__/::::::::\ \__\/\:\__  /__/::::::::\
##      \__\:\ \  \:\/:/ /:/ \  \:\~~\~~\/    \  \:\/\ \  \:\~~\~~\/
##      /  /:/  \  \::/ /:/   \  \:\  ~~~      \__\::/  \  \:\  ~~~
##     /__/:/    \  \:\/:/     \  \:\          /__/:/    \  \:\
##     \__\/      \  \::/       \  \:\         \__\/      \  \:\
##                 \__\/         \__\/                     \__\/
##

#########################################################################

pathlen=${#1}
i=$(( pathlen - 1 ))
re='^[0-9]+$'
pnumr=""

while [ $i -gt -1 ]
do  
    tmp=${1:i:1}
    if  [[ $tmp =~ $re ]]; then
       pnumr="$pnumr$tmp"
    fi
    i=$(( i - 1 ))
done

copy=${pnumr}
len=${#copy}
for((i=$len-1;i>=0;i--)); do 
    pnum="$pnum${copy:$i:1}"
done


echo "Problem Number (Default: $pnum)"
printf ">> "
read tmp
if ! [ "$tmp" == "" ]
then
    pnum=$tmp
fi
echo
echo "Language (Default: C++11)"
echo "  1 = ANSI C      2 = JAVA        3 = C++"
echo "  4 = Pascal      5 = C++11       6 = Python"
printf ">> "
read lan
if [ "$lan" == "" ]
then
   lan=5
fi

echo

uva-tool -submit $pnum "$1" $lan


