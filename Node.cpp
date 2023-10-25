#include "Node.hpp"
INode *make_var     (std::string name)              {return new Variable(name);}
INode *make_val     (int val)                       {return new Value(val);}
INode *make_op      (INode* l, Ops op, INode* r)    {return new Op(l,op,r);}
INode *make_if      (INode* head, INode* body)      {return new Ifstmt(head, body);}
INode *make_while   (INode* head, INode* body)      {return new Whilestmt(head, body);}
INode *make_assig   (INode* left, INode *right)     {return new Assig(left, right);}
IScope *make_scope  (IScope* prev)                  {return new Scope(prev);}
INode *make_out     (INode* expr)                   {return new Output(expr);}

int Variable::exec(INode* iscope){
    Scope* scope = static_cast<Scope*>(iscope); 
    std::unordered_map<std::string, int>::iterator search;
    while(scope!=nullptr){
        search = scope->vars_.find(name_);
        if(search != scope->vars_.end()) break;
        scope = static_cast<Scope*>(scope->prev());
    } if(scope==nullptr) return 0;
    return search->second;
}
int Value::exec(INode*){
    return val_;
}
int Op::exec(INode* scope){
    int l, r;
    if(left_!=nullptr && right_!=nullptr){
        l = left_->exec(scope);
        r = right_->exec(scope);
    }
    switch(op_){
    case(Ops::PLUS):  return l+r;
    case(Ops::LESS):  return l<r;
    case(Ops::GRTR):  return l>r;
    case(Ops::MINUS): return l-r;
    case(Ops::MOD):   if(r==0) return 1; return l/r;
    case(Ops::MULT):  return l*r;
    }
    return 0;
}
int Ifstmt::exec(INode* scope){
    if(head_->exec(scope)==1)
        body_->exec(scope);
    return 0;
}
int Whilestmt::exec(INode* scope){
    while(Whilestmt::head_->exec(scope)==1){
        Whilestmt::body_->exec(scope);        
    }
    return 0;
}
int Scope::exec(INode* s){
    for(int i = 0, sz = lent_.size(); i<sz; ++i){
        lent_[i]->exec(this);
    }
    return 0;
}
int Assig::exec(INode* iscope){
    std::unordered_map<std::string, int>::iterator search;
    Scope* scope = static_cast<Scope*>(iscope);
    Variable* var = static_cast<Variable*>(left_); 
    int r =  right_->exec(scope);
    while(scope->prev()!=nullptr){
        search = scope->vars_.find(var->name_);
        if(search != scope->vars_.end()) break;
        scope = static_cast<Scope*>(scope->prev());
    } 
    scope->vars_[var->name_] = r;
    search = scope->vars_.find(var->name_);
    return 0;
}
int Output::exec(INode* iscope){
    std::cout<<expr_->exec(iscope)<<std::endl;
    return 0;
}

Variable::Variable(std::string name):name_{name}{}
Value::Value(int val):val_(val){}
Op::Op(INode* l, Ops op, INode* r):left_(l), right_(r), op_(op){}
Ifstmt::Ifstmt(INode* head, INode* body):head_(head), body_(body){}
Whilestmt::Whilestmt(INode* head, INode* body):head_(head), body_(body){}
Scope::Scope(IScope* prev): prev_{prev}{}
Assig::Assig(INode* left, INode *right): left_{left}, right_{right}{}
Output::Output(INode* expr): expr_{expr}{}

void Scope::add_branch(INode* branch) {Scope::lent_.push_back(branch);}
IScope* Scope::prev(){return prev_;}

