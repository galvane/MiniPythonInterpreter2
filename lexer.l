
/*** Definition Section has one variable 
which can be accessed inside yylex()  
and main() ***/
%{ 
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
int linenumber = 1;
int prevlinenumber= 1;
int indentlevel = 0;
int numberofspaces = 0;
bool newline = false;
%}
%%
[" "]{3,3} {indentlevel++;}

((if[ ])|else:) {printf("LINE=%d TYPE=KEYWORD TOKEN=%s LEVEL=%d\n", linenumber, yytext, indentlevel);}
print\((.*)\) {printf("LINE=%d TYPE=PRINT_STATEMENT TOKEN=%s LEVEL=%d\n", linenumber, yytext, indentlevel);}
def[ ]+([a-zA-Z_$][a-zA-Z_$0-9]*)\(([a-zA-Z_$][a-zA-Z_$0-9]*)*(,([a-zA-Z_$][a-zA-Z_$0-9]*))*\): {printf("LINE=%d TYPE=FUNCTION TOKEN=%s LEVEL=%d\n", linenumber, yytext, indentlevel);}
([a-zA-Z_$][a-zA-Z_$0-9]*)[" "]*\((.*)\) {printf("LINE=%d TYPE=FUNCTIONCALL TOKEN=%s LEVEL=%d\n", linenumber, yytext, indentlevel);} 
return {printf("LINE=%d TYPE=RETURN TOKEN=%s LEVEL=%d\n", linenumber, yytext, indentlevel);}
":" {printf("LINE=%d TYPE=COLON TOKEN=%s LEVEL=%d\n", linenumber, yytext, indentlevel);}
"(" {printf("LINE=%d TYPE=OPEN_PARENTHESIS TOKEN=%s LEVEL=%d\n", linenumber, yytext, indentlevel);}
")" {printf("LINE=%d TYPE=CLOSE_PARENTHESIS TOKEN=%s LEVEL=%d\n",linenumber, yytext, indentlevel);}
"," {printf("LINE=%d TYPE=COMMA TOKEN=%s LEVEL=%d\n",linenumber, yytext, indentlevel);}
[ ]*\"(.*)\"[ ]* {printf("LINE=%d TYPE=STRING TOKEN=%s LEVEL=%d\n",linenumber, yytext, indentlevel);}
[a-zA-Z_$][a-zA-Z_$0-9]* {printf("LINE=%d TYPE=VARIABLE TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel); }
"==" {printf("LINE=%d TYPE=EQUALSCOMPARISON TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel);}
">" {printf("LINE=%d TYPE=GREATER_THAN TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel);}
"<" {printf("LINE=%d TYPE=LESS_THAN TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel);}
"=" {printf("LINE=%d TYPE=EQUALS TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel);}
"-" {printf("LINE=%d TYPE=MINUS TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel);}
"+" {printf("LINE=%d TYPE=PLUS TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel);}
"*" {printf("LINE=%d TYPE=TIMES TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel);}
"/" {printf("LINE=%d TYPE=DIVIDE TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel);}
[0-9]+ {printf("LINE=%d TYPE=INTEGER TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel);}
"#"(.*) {printf("LINE=%d TYPE=COMMENT TOKEN=%s LEVEL=%d\n", linenumber,yytext, indentlevel);}
\n{2,2} {prevlinenumber = linenumber; linenumber+=2; newline = true; indentlevel=0; numberofspaces = 0;}
\n{1,1} {prevlinenumber = linenumber; linenumber++; indentlevel=0; numberofspaces = 0;}

%% 
/*** Code Section***/
int yywrap(){} 
int main(){ 
  
// Explanation: 
// yywrap() - wraps the above rule section 
/* yyin - takes the file pointer  
          which contains the input*/
/* yylex() - this is the main flex function 
          which runs the Rule Section*/
// yytext is the text in the buffer 
  
// Uncomment the lines below  
// to take input from file 
 FILE *fp; 
 //char filename[50]; 
 char filename[50] = "program3.py";
 //printf("Enter the filename: \n"); 
 //scanf("%s", filename); 
 fp = fopen(filename,"r"); 
 yyin = fp; 
  
yylex();

return 0; 
}
