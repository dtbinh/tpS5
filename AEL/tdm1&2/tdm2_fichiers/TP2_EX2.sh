#!/bin/bash


#Valeur d'attribut en XML "([^<"&]*|(&[a-zA-z:_]([a-zA-z:_0-9.-])*;)*)*"
#     
nom='([[:alpha:]]|_|:) ([[:alpha:]]|_|:|[[:digit:]|-|.|$])'                   
ref="&$nom_XML;"
val=\"[^[\&<\"]]|"$ref"\"

echo Q1
egrep "$valeur_attribut" html/*.html
echo
echo Q2
#egrep 
echo
echo Q3
#egrep 



