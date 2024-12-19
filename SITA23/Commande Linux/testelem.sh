#!/bin/bash
if [[ -d "$1" ]] # Test si repertoire
then
	echo "L'element $1 est un repertoire"
	exit 0
fi

if [[ -f "$1" ]] # Test si repertoire
then
	echo "L'element $1 est fichier régulier"
	exit 0
fi

if [[ ! -f "$1" ]] # Test si repertoire
then
	echo "L'element $1 n'est pas un fichier régulier"
	exit 0
fi
