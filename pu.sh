#!/bin/bash
if [ "$#" -ne 3 ]
then
	echo "Syntax : ./pu.sh '<Type>' '<En tete>' '<Body>'"
else
	git add *
	git commit -m "$1 : $2

$3"
	git push
fi
