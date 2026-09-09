%{
#include <stdio.h>
%}

%option noyywrap

%%
bool|int|float       { printf("Keyword: %s\n", yytext); }
[-,+]?[0-9]+         { printf("Constant: %s\n", yytext); }
[,.'"]+              { printf("Punctuation Chars: %s\n", yytext); }
[!@#$%^&*()]+        { printf("Special Chars: %s\n", yytext); }
[a-zA-Z]+            { printf("Identifier: %s\n", yytext); }
[ \t\n]+             ;
.                    { printf("Unknown: %s\n", yytext); }
%%

int main()
{
    printf("Enter a line: ");
    yylex();
    return 0;
}
