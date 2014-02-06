DIGIT [0-9]
ID [a-z]+

%%

{DIGIT}+ {
    printf( "digit %s\n", yytext );
}

{ID}+ {
    printf( "id: %s", yytext);
}



%%
