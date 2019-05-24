
#include <stack>
#include "eval.hpp"

using namespace std;

int Eval::operator()(unordered_map<std::string, int> values) const 
{ 
    stack<int> s;
    for(int i = 0; i < pfexpr.size(); i++)
    {
        int pos = operators.find(pfexpr[i]); 
        if (pos < 0 || pos >= operators.size())
            s.push(values[pfexpr[i]]);
        else
        {
            int v1 = s.top();s.pop(); 
            int v2 = s.top();s.pop();
            switch (pfexpr[i][0])  
            {  
                case '+': s.push(v2 + v1); break;  
                case '-': s.push(v2 - v1); break;  
                case '*': s.push(v2 * v1); break;  
                case '/': s.push(v2 / v1); break;  
            }  
        }
    }
    return s.top(); 
}


void Eval::ToPostfixNotation(string e)
{
    unordered_map<char, int> precedence = {{'+',1},{'-',1},{'*',2},{'/',2},{'(',0},{')',0}};
    stack<char> s;
    int i = 0;
    for(int i = 0; i < e.length(); i++)
    {
        if (precedence.count(e[i]) > 0)
        {
            if (e[i] == ')')
                while(!s.empty())
                {
                    if (s.top() == '(')
                    {
                        s.pop();
                        break;
                    }
                    pfexpr.push_back(""s+s.top());
                    s.pop();
                }
            else
                if (s.empty() || precedence[s.top()] < precedence[e[i]] || e[i] == '(')
                    s.push(e[i]);
                else
                {
                    while(precedence[e[i]] <= precedence[s.top()])
                    {
                        pfexpr.push_back(""s+s.top());
                        s.pop();
                        if (s.empty())
                            break;
                    }
                    s.push(e[i]);
                }
        }
        else
        {
            int j = i+1;
            while(precedence.count(e[j]) == 0) j++;
            pfexpr.push_back(e.substr(i, j - i));  
            i = j - 1;      
        }
    }
    while(!s.empty())
    {
        pfexpr.push_back(""s+s.top());
        s.pop();
    }
};
