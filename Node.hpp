#pragma once
#include "INode.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
struct Value : public INode{
    int val_;
    Value(int val);
    int exec(INode*) override;
};
struct Variable : public INode{
    std::string name_;
    int exec(INode*) override;
    Variable(std::string name);
};
struct Op : public INode{
     INode* left_;
    INode* right_;
    Ops op_;
    Op(INode *l, Ops op, INode *r);
    int exec(INode*) override;
};
struct Ifstmt : public INode{
    INode* head_;
    INode* body_;
    Ifstmt(INode *head, INode *body);
    int exec(INode*) override;
};
struct Whilestmt : public INode{
    INode* head_;
    INode* body_;
    Whilestmt(INode *head, INode *body);
    int exec(INode*) override;
};
struct Assig : public INode{
    INode* left_;
    INode* right_;
    Assig(INode*, INode*);
    int exec(INode*) override; 
};
struct Scope : public IScope{
    std::vector<INode*> lent_;
    std::unordered_map<std::string, int> vars_;
    IScope* prev_;
    INode* recent_;
    Scope(IScope* prev);
    void add_branch(INode* branch) override;
    int exec(INode*) override;
    IScope* prev() override;
    void setRecently(INode* r){recent_ = r;}
    INode* getRecently(){return recent_;}
};
struct Output : public INode{
    INode* expr_;
    Output(INode* expr);
    int exec(INode*) override;
};
