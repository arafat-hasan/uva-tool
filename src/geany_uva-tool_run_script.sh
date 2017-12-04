#!/bin/bash 
#
# FILE: geany_uva-tool_run_script.sh
#
# @author: Md. Arafat Hasan Jenin <arafathasanjenin[at]gmail[dot]com>
#
# LINK:
#
# DATE CREATED: 4 Dec 2017
# LAST MODIFIED: 4 Dec 2017
#
# DESCRIPTION:
#
# DEVELOPMENT HISTORY:
# Date         Version     Description
# --------------------------------------------------------------
# 04-12-17		1.0         File Created
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

while true
do
    echo "1# Submit"
    echo "2# Hunt"
    echo "3# Login"
    echo "4# Logout"
    echo "Press [CTRL+C] to exit.."
    echo

    read var
	
    if [ "$var" == "1" ]; then
		cd $2
        pathlen=${#1}
        i=$(( pathlen - 1 ))

        while [ $i -gt 0 ];
        do
            if [ ${1:i:1} == "." ]
            then
                break;
            fi
            i=$(( i - 1 ))
        done

        re='^[0-9]+$'
        i=$(( i - 1 ))
        pnumr=""

        while [ $i -gt 0 ]
        do  
            tmp=${1:i:1}
            if ! [[ $tmp =~ $re ]]; then
            break
            fi
            pnumr="$pnumr$tmp"
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
        
    elif [ "$var" == "2" ]; then
        usr=`cat usr`
        rng=`cat rng`
        echo "Enter username (default '$usr')"
        read tmp
        if [ "$tmp" != "" ]; then
            usr=$tmp
            echo $tmp | tee usr
        fi
        echo "Enter range (default '$rng')"
        read tmp
        if [ "$tmp" != "" ]; then
            rng=$tmp
            echo $tmp | tee rng
        fi
        uva-tool -hunt -u $usr -r $rng
        
    elif [ "$var" == "3" ]; then
		uva-tool -login
    elif [ "$var" == "4" ]; then
        uva-tool -logout
    fi
	echo
	echo
done
