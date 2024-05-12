#pragma once
#include <string>
#include <vector>
using namespace std;

vector<string> data_types = {"int", "char","bool","float", "void"};
sentence functions = {"main"};
sentence operations = {"*", "*=", "+", "+=", "-", "-=", "/", "/="};
class Token {
public:
    enum TokenType {
        STATEMENT,
        FN_CALL,
        ARG_START,
        ARG_END,
        SCOPE_START,
        SCOPE_END,
        COMMENT_DEL,
        CHAR_LITERAL,
        STR_LITERAL,
        NUMB_LITERAL,
        DATA_TYPE,
        FUNCTION,
        SEMICOLON,
        COMMA,
        OPERATION,
        FOR_DECL,
        WHILE_DECL,
        IF_DECL,
        ELSE_DECL,
        RETURN
    } type;

    string val;

   Token(string input) : val(input) {
        if (isdigit(input[0])){
            type = NUMB_LITERAL;
        } else if (input[0] == '\''){
            type = CHAR_LITERAL;
        } else if (input[0] == '\"'){
            type = STR_LITERAL;
        } else if (input == "return"){
            type = RETURN;
        } else if (input == "else"){
            type = ELSE_DECL;
        } else if (input == "if"){
            type = IF_DECL;
        } else if (input == "while"){
            type = WHILE_DECL;
        } else if (input == "for"){
            type = FOR_DECL;
        } else if (input == ","){
            type = COMMA;
        } else if (input == ";"){
            type = SEMICOLON;
        } else if (input == "(") {
            type = ARG_START;
        } else if (input == ")") {
            type = ARG_END;
        } else if (input == "{") {
            type = SCOPE_START;
        } else if (input == "}") {
            type = SCOPE_END;
        } else if (find(data_types.begin(), data_types.end(), input)!= data_types.end()) {
            type = DATA_TYPE;
        } else if (find(functions.begin(), functions.end(), input)!= functions.end()) {
            type = FUNCTION;
        } else if (find(operations.begin(), operations.end(), input)!= operations.end()) {
            type = OPERATION;
        } else type = STATEMENT;
    }
    
    void printToken() const {
        string typeName;
        switch (type) {
            case STATEMENT: typeName = "STATEMENT"; break;
            case FN_CALL: typeName = "FN_CALL"; break;
            case ARG_START: typeName = "ARG_START"; break;
            case ARG_END: typeName = "ARG_END"; break;
            case SCOPE_START: typeName = "SCOPE_START"; break;
            case SCOPE_END: typeName = "SCOPE_END"; break;
            case COMMENT_DEL: typeName = "COMMENT_DEL"; break;
            case STR_LITERAL: typeName = "STR_LITERAL"; break;
            case DATA_TYPE: typeName = "DATA_TYPE"; break;
            case FUNCTION: typeName = "FUNCTION"; break;
            case FOR_DECL: typeName = "FOR_DECL"; break;
            case IF_DECL: typeName = "IF_DECL"; break;
            case ELSE_DECL: typeName = "ELSE_DECL"; break;
            case WHILE_DECL: typeName = "WHILE_DECL"; break;
            case SEMICOLON: typeName = "SEMICOLON"; break;
            case CHAR_LITERAL: typeName = "CHAR_LITERAL"; break;
            case NUMB_LITERAL: typeName = "NUMB_LITERAL"; break;
            case RETURN: typeName = "RETURN"; break;
            case OPERATION: typeName = "OPERATION"; break;
            case COMMA: typeName = "COMMA"; break;
            default: typeName = "UNKNOWN"; break;
        }
        cout << "Token: " << val << " (Type: " << typeName << ")" << endl;
    }
};

ostream& operator<<(ostream& stream, const Token& tk) {
    stream << tk.val;
    return stream;
}

// ================= PARSING =================


string delimiter = "(){}+=-*,;:<>/ \n\t";

bool isDelimiter(char c) {
    for (char d : delimiter) {
        if (c == d) return true;
    }
    return false;
}

void parse(vector<Token>& tokens, const string& code) {
    string buffer = "";

    for(char c : code){

        if(isDelimiter(c)){
            if(buffer.length() > 0) {
                tokens.emplace_back(buffer);
                buffer.clear();
            }

            if(find(delimiter.begin(),delimiter.end()-3,c)!=delimiter.end()-3){
                string s(1,c);
                tokens.emplace_back(s);
            }
            continue;
        }
        // add to buffer if it's not white space
        if(c ==' ' || c=='\n' || c=='\t')
            continue;
        buffer.push_back(c);
    }
}


