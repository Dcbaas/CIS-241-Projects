%{
#include <stdio.h>
%}

%%

[0-9]{4}-[0-9]{2}-[0-9]{2}-[0-9]{2}-[0-9]{2}-[0-9]{2}   { printf("DATE"); }

%%

int main(int argc, char** argv){
  yylex();
}
