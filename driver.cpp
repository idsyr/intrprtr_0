#include "driver.hpp"
IScope* tecScope = nullptr;
int yyFlexLexer::yywrap() {return 1;}
int main(int argc, char* argv[]){
    if(argc<2){
        std::cout<<"too few args"<<std::endl;
        return 0;}
    std::ifstream* ifs = new std::ifstream();
    ifs->open(argv[1]);
    tecScope = make_scope(nullptr);
    FlexLexer *lexer = new yyFlexLexer(ifs);
    yy::Driver driver(lexer);
    driver.parse();
    delete lexer;
    delete tecScope;
}
