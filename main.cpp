#include "headers/master.h"

int main(){
    vector<Token> token_vector;
    fstream file("code.txt");
    string code = read_f(file);
    file.close();

    parse(token_vector,code);
    log_vec(token_vector);
    vector<Function> test_lambda;

    for(Token tk: token_vector)
        tk.printToken();


    shared_ptr<Ast> ast = make_shared<Ast>();
    
    Ast::Ast_machine new_machine;
    new_machine.run_v2(ast,token_vector);

    ast->display(0);
    return 0;
}