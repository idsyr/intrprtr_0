#pragma once
#include <iostream>
#include <numeric>
#include <string>
#include <fstream>
#include <FlexLexer.h>
#include "lexer_defines.h"
#include "INode.hpp"
namespace yy { 
class Driver{
    FlexLexer *plex_;
public:
    Driver(FlexLexer *plex) : plex_(plex){} 
    parser::token_type yylex(parser::semantic_type *yylval){
        parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());
        if(tt == yy::parser::token_type::NUMBER)
            yylval->as<int>() = std::stoi(plex_->YYText());
        if(tt == yy::parser::token_type::NAME)
            yylval->emplace<std::string>(plex_->YYText());
        return tt;
    }
    bool parse(){
        parser tecParser(this);
        bool res = tecParser.parse();
        return !res;
    }
};
    
}
