%language "c++"
%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::Driver* driver}

%code requires{
    #include <iostream>
    #include <string>
    #include "INode.hpp"
    namespace yy {class Driver; }
    extern IScope *tecScope;
}

%code{
    #include "driver.hpp"
    namespace yy {
        parser::token_type yylex
            (parser::semantic_type* yylval, Driver* driver); }
}

%token EQUAL SCOLN ERR ASSIG OPSC CLSC OPB CLB WHILE IF INPUT OUTPUT
%left MINUS PLUS MULT MOD GRTR LESS 
%token <int> NUMBER
%token <std::string> NAME
%nterm   <INode*>  ifstm whilestm assignstm scstm expr lval stm stms outstm bexp 
%start program

%%

program     : stms                      {tecScope->exec(nullptr);}
;
stms        : stm
            | stm stms
;
stm         : ifstm                     {tecScope->add_branch($1);}
            | whilestm                  {tecScope->add_branch($1);}
            | assignstm                 {tecScope->add_branch($1);}
            | scstm                     {tecScope->add_branch($1);}
            | outstm                    {tecScope->add_branch($1);}       
;
opensc      : OPSC                      {tecScope = make_scope(tecScope);}
;
closesc     : CLSC                      {tecScope->prev()->setRecently(tecScope); tecScope = tecScope->prev();}
;
scstm       : opensc stms closesc       {$$ = tecScope->getRecently();}
;
assignstm   : lval ASSIG expr SCOLN     {$$ = make_assig($1, $3);}
;
lval        : NAME                      {$$ = make_var($1); }
;
expr        : expr PLUS expr            {$$ = make_op($1, Ops::PLUS, $3);}
            | expr MINUS expr           {$$ = make_op($1, Ops::MINUS, $3);}
            | expr MOD expr             {$$ = make_op($1, Ops::MOD, $3);}
            | expr MULT expr            {$$ = make_op($1, Ops::MULT, $3);}
            | lval                      {$$ = $1;}
            | NUMBER                    {$$ = make_val($1);}
            | OPB expr CLB              {$$ = $2;}
            | INPUT                     {int temp; std::cin>>temp; $$ = make_val(temp);}      
;
bexp        : bexp GRTR bexp            {$$ = make_op($1, Ops::GRTR, $3);}
            | bexp LESS bexp            {$$ = make_op($1, Ops::LESS, $3);}
            | lval                      {$$ = $1;}
            | NUMBER                    {$$ = make_val($1);}
;
whilestm    : WHILE OPB bexp CLB scstm  {$$ = make_while($3, $5);} 
;
ifstm       : IF OPB bexp CLB scstm     {$$ = make_if($3, $5);}
;
outstm      : OUTPUT ASSIG expr SCOLN   {$$ = make_out($3);}


%%

    namespace yy {
        parser::token_type yylex
            (parser::semantic_type* yylval, Driver* driver)
                {return driver->yylex(yylval);}
        void parser::error(const std::string& s){
            std::cout<<s<<std::endl;
        }
    }
