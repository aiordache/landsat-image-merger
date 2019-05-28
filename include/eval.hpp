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
        float operator()(std::unordered_map<std::string, float> values) const; 

        std::vector<float> GetInterval(int min, int max);
};

