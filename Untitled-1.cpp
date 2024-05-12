#include <stack>
#include "headers\ast.h"

void Ast::load_f_tokens(std::vector<Token>& tokens) {
    // Create a stack to keep track of the current scope
    std::stack<Ast*> scope_stack;
    scope_stack.push(this);

    // Iterate through the tokens
    for (size_t i = 0; i < tokens.size(); i++) {
        Token& token = tokens[i];

        // Check if the token is a function declaration
        if (token.type == Token::FUNCTION) {
            // Create a new Function object
            Function* function = new Function();
            function->set_function(FunctionType::FUNCTION_DEF);
            function->name = new std::string(token.val);

            // Skip the next token (the function name)
            i++;
            token = tokens[i];

            // Parse the function arguments
            std::string arg_str;
            while (token.type != Token::ARG_END) {
                arg_str += token.val;
                arg_str += " ";
                i++;
                token = tokens[i];
            }
            function->argumets = new std::string(arg_str);

            // Create a new Ast object for the function scope
            Ast* function_scope = new Ast(*function);
            scope_stack.top()->next = function_scope;
            scope_stack.push(function_scope);

            // Parse the function body
            while (tokens[i].type != Token::SCOPE_END) {
                i++;
                function_scope->load_f_tokens(tokens);
            }

            // Pop the function scope from the stack
            scope_stack.pop();
        }
        // Check if the token is a function call
        else if (token.type == Token::FN_CALL) {
            // Create a new Function object
            Function* function = new Function();
            function->set_function(FunctionType::FUNCTION_CALL);
            function->name = new std::string(token.val);

            // Skip the next token (the function name)
            i++;
            token = tokens[i];

            // Parse the function arguments
            std::string arg_str;
            while (token.type != Token::ARG_END) {
                arg_str += token.val;
                arg_str += " ";
                i++;
                token = tokens[i];
            }
            function->argumets = new std::string(arg_str);

            // Create a new Ast object for the function call
            Ast* function_call = new Ast(*function);
            scope_stack.top()->next = function_call;
        }
        // Check if the token is a for loop
        else if (token.type == Token::FOR_LOOP) {
            // Create a new Function object
            Function* function = new Function();
            function->set_function(FunctionType::FOR_LOOP);

            // Skip the next token (the for keyword)
            i++;
            token = tokens[i];

            // Parse the loop initialization
            std::string init_str;
            while (token.type != Token::SEMICOLON) {
                init_str += token.val;
                init_str += " ";
                i++;
                token = tokens[i];
            }
            function->argumets = new std::string(init_str);

            // Parse the loop condition
            std::string cond_str;
            i++;
            token = tokens[i];
            while (token.type != Token::SEMICOLON) {
                cond_str += token.val;
                cond_str += " ";
                i++;
                token = tokens[i];
            }
            function->name = new std::string(cond_str);

            // Parse the loop increment
            std::string inc_str;
            i++;
            token = tokens[i];
            while (token.type != Token::SCOPE_START) {
                inc_str += token.val;
                inc_str += " ";
                i++;
                token = tokens[i];
            }
            function->argumets = new std::string(inc_str);

            //Create a new Ast object for the for loop
            Ast* for_loop = new Ast(*function);
            scope_stack.top()->next = for_loop;

            // Parse the loop body
            i++;
            token = tokens[i];
            while (token.type != Token::SCOPE_END) {
                i++;
                for_loop->load_f_tokens(tokens);
            }
        }
        // Check if the token is a while loop
        else if (token.type == Token::WHILE_LOOP) {
            // Create a new Function object
            Function* function = new Function();
            function->set_function(FunctionType::WHILE_LOOP);

            // Skip the next token (the while keyword)
            i++;
            token = tokens[i];

            // Parse the loop condition
            std::string cond_str;
            while (token.type != Token::SCOPE_START) {
                cond_str += token.val;
                cond_str += " ";
                i++;
                token = tokens[i];
            }
            function->name = new std::string(cond_str);

            // Create a new Ast object for the while loop
            Ast* while_loop = new Ast(*function);
            scope_stack.top()->next = while_loop;

            // Parse the loop body
            i++;
            token = tokens[i];
            while (token.type != Token::SCOPE_END) {
                i++;
                while_loop->load_f_tokens(tokens);
            }
        }
        // Check if the token is a statement
        else if (token.type == Token::STATEMENT) {
            // Create a new Ast object for the statement
            Ast* statement = new Ast();
            statement->code = new Function();
            statement->code->set_function(FunctionType::STATEMENTS);
            statement->code->name = new std::string(token.val);
            scope_stack.top()->next = statement;
        }
    }
}