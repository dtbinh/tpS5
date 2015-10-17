#!/bin/bash
echo Q1
egrep -w --color=auto nez Cyrano.txt
echo
echo Q2
egrep --color=auto '\('*'\)' Cyrano.txt
echo
echo Q3
# '^' -> debut de ligne
# [^[c]] -> tout sauf c
egrep --color=auto '(^|[^[:alpha:]])[[:alpha:]]{4}($|[^[:alpha:]])' Cyrano.txt
echo
echo "Q3(bis)"
#Meilleure expression !
egrep -w --color=auto [[:alpha:]àâéàêîùûÀÂÉÈÊÎÔÙÛ]{4} Cyrano.txt
echo
echo Q4
echo "Car avec l'expression 3 egrep coupe le mot ' vous ' et redemarre sur le deuxieme vous sans l'espace ce qui donne'vous'"
echo
echo Q5
egrep --color=auto  [[:space:]]:[[:space:]]\"*\" Cyrano.txt
echo
