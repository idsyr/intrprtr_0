#pragma once
#include <string>
struct INode{
    virtual int exec(INode*) = 0;
    virtual ~INode(){}
};

struct IScope : public INode{
    virtual void add_branch(INode* branch) = 0;
    virtual IScope* prev() = 0;
    virtual void setRecently(INode*) = 0;
    virtual INode* getRecently() = 0;
};

enum class Ops{
    MINUS,
    PLUS,
    MULT,
    MOD,
    GRTR,
    LESS,
    EQUAL,
    ASSIG,
    INPUT
};

INode *make_val(int);
INode *make_var(std::string);
INode *make_op(INode* l, Ops op, INode* r);
INode *make_if(INode* head, INode* body);
INode *make_while(INode* head, INode* body);
IScope *make_scope(IScope* prev);
INode *make_assig(INode* left, INode* right);
INode *make_out(INode* expr);
