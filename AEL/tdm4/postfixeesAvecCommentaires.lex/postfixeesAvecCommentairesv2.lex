package postfixees;

%%

%unicode
%line
%column
%{
  private int compteurCommentaire = 0 ;
%} 

%unicode

%state COMMENTAIRE

ENTIER_SIMPLE=[0-9]+
PLUS=[+]|plus

%% 

<YYINITIAL> {
      {ENTIER_SIMPLE}
            {
                  return new Valeur(yytext());
            }
      {PLUS}
            {
                  return new Plus(yytext());
            }
}
"/*"
      {
            yybegin(COMMENTAIRE) ;
            compteurCommentaire++;
      } 
<COMMENTAIRE>{
      [^*]+|[*][^/]
            {
            }

      "*/"
            {
                  compteurCommentaire--;
                  if(compteurCommentaire==0)
                        { yybegin(YYINITIAL);}
            }
}

/* ajouter le cas des espaces et fins de ligne */

/* ajouter les autres tokens */