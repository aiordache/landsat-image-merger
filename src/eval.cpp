#include <stack>
#include <opencv2/imgcodecs.hpp>
#include "eval.hpp"

using namespace std;
using namespace cv;

float Eval::operator()(unordered_map<std::string, float> values) const 
{ 
    stack<float> s;
    for(int i = 0; i < pfexpr.size(); i++)
    {
        int pos = operators.find(pfexpr[i]); 
        if (pos < 0 || pos >= operators.size())
        {
            if (values.find(pfexpr[i]) == values.end())
                s.push(stof(pfexpr[i]));
            else
                s.push(values[pfexpr[i]]);
        }
        else
        {
            float v1 = s.top();s.pop(); 
            float v2 = s.top();s.pop();
            switch (pfexpr[i][0])  
            {  
                case '+': s.push(v2 + v1); break;  
                case '-': s.push(v2 - v1); break;  
                case '*': s.push(v2 * v1); break;  
                case '/': v1 == 0 && v2 == 0? s.push(0) : v1 == 0 ? s.push(v2/0.000001f): s.push(v2/v1); break;  
            }
        }
    }
    return s.top(); 
}


void Eval::ToPostfixNotation(string e)
{
    unordered_map<char, int> precedence = {{'+',1},{'-',1},{'*',2},{'/',2},{'(',0},{')',0}};
    stack<char> s;
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
