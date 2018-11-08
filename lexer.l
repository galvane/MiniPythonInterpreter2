
/*** Definition Section has one variable 
which can be accessed inside yylex()  
and main() ***/
%{ 
int linenumber = 1;
int indentlevel = 0;
char keywords[32][10] = {"print","False","class","finally","is","return","None",
                            "for","lambda","try","True","def","from","while","and",
                            "del","global","not","elif","if","or","else",
                            "import","break"};
%} 

%%
[" "]{3,} {indentlevel++;}

(print|if.) {printf("%d@KEYWORD@%s@%d\n", linenumber, yytext, indentlevel);}
[a-zA-Z_$][a-zA-Z_$0-9]* {printf("%d@VARIABLE@%s@%d\n", linenumber,yytext, indentlevel); } 
":" {printf("%d@COLON@%s@%d\n", linenumber, yytext, indentlevel);}
"(" {printf("%d@OPEN_PARENTHESIS@%s@%d\n", linenumber, yytext, indentlevel);}
")" {printf("%d@CLOSE_PARENTHESIS@%s@%d\n",linenumber, yytext, indentlevel);}
"," {printf("%d@COMMA@%s@%d\n",linenumber, yytext, indentlevel);}
\"(.*)\" {printf("%d@STRING@%s@%d\n",linenumber, yytext, indentlevel);}
">" {printf("%d@GREATER_THAN@%s@%d\n", linenumber,yytext, indentlevel);}
"<" {printf("%d@LESS_THAN@%s@%d\n", linenumber,yytext, indentlevel);}
"=" {printf("%d@EQUALS@%s@%d\n", linenumber,yytext, indentlevel);}
"-" {printf("%d@MINUS@%s@%d\n", linenumber,yytext, indentlevel);}
"+" {printf("%d@PLUS@%s@%d\n", linenumber,yytext, indentlevel);}
"*" {printf("%d@TIMES@%s@%d\n", linenumber,yytext, indentlevel);}
"/" {printf("%d@DIVIDE@%s@%d\n", linenumber,yytext, indentlevel);}
[0-9]+ {printf("%d@INTEGER@%s@%d\n", linenumber,yytext, indentlevel);}


\n {linenumber++; indentlevel = 0;}

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
char filename[50] = "program.py";
 //printf("Enter the filename: \n"); 
 //scanf("%s", filename); 
 fp = fopen(filename,"r"); 
 yyin = fp; 
  
yylex();

return 0; 
}
