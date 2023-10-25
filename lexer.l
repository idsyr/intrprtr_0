%option c++
%{
#include "lexer_defines.h"
%}

WS [ \t\n]+
DIGIT [0-9]
DIGIT1 [1-9]
LETTER [a-z]
%%
{WS}
"="                 return yy::parser::token_type::ASSIG ;
"+"                 return yy::parser::token_type::PLUS ;
"-"                 return yy::parser::token_type::MINUS ;
";"                 return yy::parser::token_type::SCOLN ;
{DIGIT1}{DIGIT}*    return yy::parser::token_type::NUMBER ; 
{DIGIT}             return yy::parser::token_type::NUMBER ; 
"."                 return yy::parser::token_type::ERR ;
"*"                 return yy::parser::token_type::MULT ;
"/"                 return yy::parser::token_type::MOD ;
"<"                 return yy::parser::token_type::LESS ;
">"                 return yy::parser::token_type::GRTR ;
"=="                return yy::parser::token_type::EQUAL ;
"{"                 return yy::parser::token_type::OPSC ;
"}"                 return yy::parser::token_type::CLSC ;
"("                 return yy::parser::token_type::OPB ;
")"                 return yy::parser::token_type::CLB ;
"while"             return yy::parser::token_type::WHILE ;
"if"                return yy::parser::token_type::IF ;
{LETTER}{LETTER}*   return yy::parser::token_type::NAME ;
"?"                 return yy::parser::token_type::INPUT ;
"!"                 return yy::parser::token_type::OUTPUT ;
%%
