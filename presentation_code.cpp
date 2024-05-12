struct Syms{std::string}
using namespace std;
#include <iostream>
#include <vector>

Syms& Big_O_notation( 
    Time_Complexity,
    Space_Complexity
);

enum Resources{
    COMPUTATIONS,
    MEMORY,
    TIME,
    EFFORT
};

class Function{
    Syms time_complexity;
}

class BubbleSort:Function;
class Quicksort:Function;
class BinarySearch:Function;
class AllCombinations:Function;
class ForLoop:Function;
class GenericFunction:Function;

struct example{};

vector<example> examples = {


    GenericFunction.time_complexity("O(1)"),
       BinarySearch.time_complexity("O(log(n))"), 
            ForLoop.time_complexity("O(n)"),
          Quicksort.time_complexity("O(n log(n))"), 
         BubbleSort.time_complexity("O(n^2)"),
    AllCombinations.time_complexity("O(n!)"),


};

class Ast;

string main(OutStream source){

    string code = source.get_string();

    vector<Token> tokens = code.parse();

    Ast new_ast = getAstFrom(tokens);

    string time_comlexity= new_ast.calcTimeComplexity();

    string space_complexity= new_ast.calcSpaceComplexity();

    string result = "Time complexity: "+ time_comlexity +
                    "\nSpace Complexity: "+ space_complexity;
    
    return(result);
}

// not actual code, for demonstration purpouses only


Ast* head_node;

head_node->code->


( code.time_comp == O(1) )? :


( code.time_comp == O(n) )? : 




( code.time_comp == O(log(n)) )? :




( code.time_comp == O(exp(n)) )? :


( code.time_comp == O(n!) )? : 


if(code.type == CONSTANT){
    code.time_comp = O(1);
}
if ((code.type == WHILE_LOOP && code.type.rate = CONST) ||
    (code.type == FOR_LOOP   && code.type.rate = CONST) ||
    (code.type == RECURSION  && code.type.rate = LIN_DECR) ) {
    code.time_comp = O(n);
}
if ((code.type == WHILE_LOOP && code.type.rate = LINEAR) ||
    (code.type == FOR_LOOP   && code.type.rate = LINEAR) ||
    (code.type == RECURSION  && code.type.rate = NLIN_DECR)) {
    code.time_comp = O(log(n));
}
if (code.type == RECURSION && code.type.rate = LIN_INCR){
    code.time_comp = O(exp(n));
}
if (code.type == RECURSION && code.type.rate = NLIN_INCR){
    code.time_comp = O(n!);
}



