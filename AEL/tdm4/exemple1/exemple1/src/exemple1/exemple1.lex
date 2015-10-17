/* Exemple 1 */
package exemple1;

%%

%unicode

MOT_USUEL=[:letter:]+
ENTIER_SIMPLE=[0-9]+
OPERATEUR=([-+*/])
IDENTIFICATEUR=([A-Za-z][A-Za-z0-9]*)
%% 

{MOT_USUEL}|{ENTIER_SIMPLE}|{OPERATEUR}|{IDENTIFICATEUR}
      {return new Yytoken(yytext());}


[^-+*/[:letter:]0-9]+
      {}  
