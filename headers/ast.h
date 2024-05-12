#pragma once

enum class ComplexityType {
    Polynomial,
    Supernomial,
    Factorial,
};
class Complexity {
public:
    ComplexityType type;
    unsigned int power; 
    unsigned int ln_power;
    unsigned int f_power;
    Complexity():power(0),ln_power(0),f_power(0),type(ComplexityType::Polynomial){}
    Complexity(
        ComplexityType _type, 
        unsigned int pow = 0, 
        unsigned int ln = 0, 
        unsigned int f = 0): 
        type(_type), power(pow),ln_power(ln), f_power(f)
    {}
};

Complexity operator+(Complexity a, Complexity b){
    return (a.f_power > b.f_power)? a : 
        (b.f_power > a.f_power)? b :
        (a.power > b.power)? a :
        (b.power > a.power)? b :
        (a.ln_power > b.ln_power)? a : b;
}
Complexity operator*(Complexity a, Complexity b){
    unsigned int ln_power = a.ln_power + b.ln_power;
    unsigned int power = a.power + b.power;
    unsigned int f_power = a.f_power + b.f_power;

    if(ln_power == 0 && f_power == 0)
        return {ComplexityType::Polynomial , power, 0 , 0};
   
    if(f_power == 0)
        return {ComplexityType::Supernomial, power, ln_power, 0};

    return {ComplexityType::Factorial,0,0,f_power};
}

enum FunctionType{
    FOR_LOOP,
    WHILE_LOOP,
    FUNCTION_DEF,
    FUNCTION_CALL,
    STATEMENTS,
    IF_STATEMENT,
    ELSE_STATEMENT
};

class Function{
public:
    unique_ptr<string> name;
    FunctionType type;
    unique_ptr<vector<Token>> arguments;
    Complexity complexity;

    Function() : 
        name(make_unique<string>()), 
        type(FunctionType::STATEMENTS),
        complexity(), 
        arguments(make_unique<vector<Token>>())
    {}

    Function(string name) : 
        name(make_unique<string>(move(name))), 
        type(FunctionType::STATEMENTS), 
        complexity(),
        arguments(make_unique<vector<Token>>())
    {}

    Function(string name, vector<Token> arguments) : 
        name(make_unique<string>(move(name))), 
        arguments(make_unique<vector<Token>>(move(arguments))), 
        type(FunctionType::STATEMENTS), 
        complexity() 
    {}
    
    Function(vector<Token> arguments) : 
        name(make_unique<string>()), 
        arguments(make_unique<vector<Token>>(move(arguments))), 
        type(FunctionType::STATEMENTS), 
        complexity() 
    {}

    Complexity get_complexity(){
        return complexity;
    }
};


class Ast;
shared_ptr<Ast> main_func = make_shared<Ast>();

class Ast{
private:
    unique_ptr<Function> code;
    shared_ptr<Ast> scope;
    shared_ptr<Ast> next;
    shared_ptr<Ast> parent;

public:

    // adding data to the class
    Ast(): scope(nullptr), next(nullptr), code(nullptr), parent(nullptr){}
    //Ast(Ast* _parent): scope(nullptr), next(nullptr), code(nullptr), parent(_parent){}

    class Ast_machine{
    private:
        enum Sowing_state{
            SOW_ARGS,
            SOW_SCOPE,
            DEFAULT
        }state;

        void infer_state(shared_ptr<Ast> root){
            if(!root->parent) {
                state = DEFAULT;
                return;
            }

            state = SOW_SCOPE;
            
        }
        vector<Token> buffer;
    public:
        Ast_machine():state(DEFAULT){buffer.emplace_back("");}

        void run(shared_ptr<Ast> head,vector<Token>& tokens,size_t index) {
            // lambdas:
            auto glue = [&](){
                while(tokens[index].type != Token::TokenType::DATA_TYPE && 
                        tokens[index].type != Token::TokenType::SEMICOLON
                        ){
                        buffer.emplace_back(tokens[index++]);
                    }
            };

            auto newFunc = [&]()->bool{
                unique_ptr<Function> func = make_unique<Function>(buffer);
                head->code=move(func);
                buffer.clear();
                return index >= tokens.size();
            };

            auto newNodeRec = [&]{
                if(tokens[index].type == Token::TokenType::DATA_TYPE &&
                    (tokens[index+1].type ==  Token::TokenType::FUNCTION ||  
                    tokens[index+1].type ==  Token::TokenType::STATEMENT)){
                        shared_ptr<Ast> new_node = make_shared<Ast>();
                        new_node->parent = head;
                        head->next = new_node;
                        infer_state(new_node);
                        unique_ptr<Function> new_func = make_unique<Function>(move(tokens[++index].val));
                        new_node->code = move(new_func);
                        run(new_node,tokens,index);
                    }
            };

            auto addArgs = [&]{
                // while the next token isnt ")", add tokens to the args
                while(tokens[index+1].type != Token::TokenType::ARG_END) {
                    index++;
                    // skip over the "("
                    if(tokens[index].type == Token::TokenType::ARG_START)

                    buffer.emplace_back(tokens[index]);  
                    cout << tokens[index].val << endl;
                }
                // create a new ast node 
                shared_ptr<Ast> new_node = make_shared<Ast>();
                new_node->parent = head;
                // emplaces the args for the current piece of code or node in the ast  
                unique_ptr<vector<Token>> args = make_unique<vector<Token>>(buffer);
                head->code->arguments = move(args);
                buffer.clear();
            };

            auto decideScope = [&]{
                switch (tokens[index].type) {
                    case Token::TokenType::SEMICOLON: {
                        shared_ptr<Ast> new_node = make_shared<Ast>();
                        new_node->parent = head;
                        head->next = move(new_node);
                            
                        infer_state(new_node);
                        run(new_node,tokens,index);
                        break;
                    }    
                    case Token::TokenType::SCOPE_START: {
                        shared_ptr<Ast> new_node = make_shared<Ast>();
                        head->scope = move(new_node);
                        state = SOW_SCOPE; 

                        run(new_node,tokens,index+1);
                    }
                    default:
                        break;
                }
            };
            
            auto sowScope = [&]{
                while(tokens[index++].type != Token::TokenType::SCOPE_END){
                    switch (tokens[index].type)
                    {
                    case Token::TokenType::FOR_DECL :{
                        shared_ptr<Ast> new_node = make_shared<Ast>();
                        new_node->parent = head;
                        //new_node-> 
                        break;
                        }
                    
                    default:
                        break;
                    }
                }
            };
            // memorises where the main function is
            if(!main_func && *head->code->name == "main"){
                main_func = head;
            }
            
            // returns early if index a > size
            if(index > tokens.size())
                return;

            
            log("\n starting machine ...");
            // executes different code based on the state of the machine
            switch (state) {
                case DEFAULT: {
                    log("default path");
                    // glues together all that is not a new function 
                    glue();

                    // creates a new Function
                    if(newFunc()) {// if it runs out of tokens it simply returns
                        log("The machine has finished populating the ast");    
                        return;
                    }

                    // if it's a new function declaration or call,creates a new node in the ast
                    newNodeRec();

                    return;
                }
                case SOW_ARGS: {
                    log("started sowing args/n","current token:"+tokens[index].val);

                    // while the next token isnt ")", add tokens to the args
                    addArgs();
                    
                    // switch over token types to find if stay in the same scope or
                    // start a new one 
                    decideScope();
                }
                case SOW_SCOPE:{
                    
                    break;
                }
            }
            run(head,tokens,index+1);
        }
   
        void run_v2(shared_ptr<Ast> head, vector<Token>& tokens) {
            Ast* curr = head.get();
            size_t index = 0;
            unique_ptr<Function> curr_func = nullptr;
            while(index < tokens.length()){
            switch (state) {
                case SOW_ARGS:{
                    while(tokens[index].type != Token::TokenType::ARG_END){
                        buffer.push_back(tokens[index]);
                    }
                    curr_func = make_unique<Function>(buffer);
                    buffer.clear();
                    infer_state(curr);
                    break;
                }
                case SOW_SCOPE:{
                    break;
                }
                case DEFAULT:{
                    for(Token tk = token[index]; tokens[index].type != Token::TokenType::ARG_START; index++){
                        buffer.push_back(tk);
                    }
                    break;
                }
            }}
        }
   
    };


    void eval(shared_ptr<Ast> root, Complexity& result){
        // calculates the complexity within the scope
        if(scope == nullptr)
            return;

        result = code->get_complexity() * result;
        root->eval(scope,result);

        
        // retruns if there is no more code
        if(next == nullptr)
            return;
        
        result = code->get_complexity() + result;
        root->eval(next,result);
    }

    void display(int indent) {
        // Print indentation
        for (int i = 0; i < indent; ++i) {
            std::cout << "  ";
        }

        // Print the code
        if (code) {
            std::cout << "Code: ";
            switch (code->type) {
                case FunctionType::FOR_LOOP:
                    std::cout << "FOR_LOOP";
                    break;
                case FunctionType::WHILE_LOOP:
                    std::cout << "WHILE_LOOP";
                    break;
                case FunctionType::FUNCTION_DEF:
                    std::cout << "FUNCTION_DEF: " << *code->name;
                    break;
                case FunctionType::FUNCTION_CALL:
                    std::cout << "FUNCTION_CALL: " << *code->name;
                    break;
                case FunctionType::STATEMENTS:
                    std::cout << "STATEMENTS";
                    break;
            }
            cout << ", arguments: " ;
            for(Token tk : *code->arguments)
                cout<< tk.val << " ";
            cout << endl;
            cout << *code->name << endl;
        }

        // Print the scope
        if (scope) {
            std::cout << "Scope:" << std::endl;
            scope->display(indent + 1);
        }

        // Print the next node
        if (next) {
            std::cout << "Next:" << std::endl;
            next->display(indent + 1);
        }
    }

};

