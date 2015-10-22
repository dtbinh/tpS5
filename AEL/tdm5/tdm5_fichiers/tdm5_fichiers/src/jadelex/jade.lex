package jadelex ;


%%


%class TokenizerV1
%implements Tokenizer
%public
%line
%column
%{
  private int compteurCommentaire = 0 ;
%} 

%unicode

%state COMMENTAIRE


NORD=[nord]|[NORD]
SUD=[sud]|[SUD]
EST=[est]|[EST]
OUEST=[ouest]|[OUEST]

LEVER=[lever]|[LEVER]
BAISSER=[baisser]|[BAISSER]

ESPACE=[\s$]
COMMENTAIRES=[\/\/][^[\n$]\/\*]*[\n$]
UNKNOWN=[]




%%

<YYINITIAL> {
      {LEVER}
      		{return new PenMode(false);}

      {BAISSER}
      		{return new PenMode(true);}

      {COMMENTAIRES}|{ESPACE}   
      		{}
      
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


