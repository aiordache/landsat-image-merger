#include <string.h>
#include <vector>
#include <unordered_map>

class Eval {
    private:
        std::vector<std::string> pfexpr;
        std::string         expr;
        const std::string   operators = "+-*/";
            
        void ToPostfixNotation(std::string e);
        
    public:
        Eval(std::string expr) : expr(expr)
        {
            ToPostfixNotation(expr); 
        };
        int operator()(std::unordered_map<std::string, int> values) const; 

     
};

