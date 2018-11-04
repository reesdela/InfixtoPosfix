#include <iostream>
#include <string>
#include "GenericList.cc"
#include "Queue.cc"
#include "Stack.cc"
#include <math.h>
using namespace std;

bool isOperand(char ch);

void infixToPostfix(Queue<char> &q);

int stackPriority(char);

int infixPriority(char);

void PostfixEval(Queue<char> &q);

double evaluation(double, double, char);




int main()
{
    char input[1024];
    while(cin.getline(input, 1024, ' '))
    {
       
    }
    
    Queue<char> q1;
    char ch;
    int x = 0;
    while(input[x] != '\0')
    {
        ch = input[x];
        q1.Enqueue(ch);
        x++;
    }
    infixToPostfix(q1);
    
}

bool isOperand(char ch)
{
    return !(ch < '0' || ch > '9');
}

void infixToPostfix(Queue<char> &q)
{
    bool yes = true;
    Queue<char> post;
    Stack<char> op;
    Queue<char> copy;
    
    copy = q;
    
    while(!(q.IsEmpty()))
    {
        while(q.Peek() != '\n')
        {
            while(yes)
            {
                while(copy.Peek() != '\n')
                {
                    cout << copy.Dequeue();
                }
                cout << endl;
                yes = false;
            }
             
            
            char token = q.Dequeue();
            if(isOperand(token))
            {
              
                post.Enqueue(token);
            }
            else if(token == ')')
            {
                char x = op.Pop();
                while(x != '(')
                {
                    post.Enqueue(x);
                    x = op.Pop();
                }
            }
            else
            {
                char x = op.Peek();
                if(op.IsEmpty())
                {
                    op.Push(token);
                }
                else if(stackPriority(x) == 4)
                {
                    op.Push(token);
                }
                else
                {
                while(stackPriority(x) >= infixPriority(token))
                {
                    if(stackPriority(x) == 4)
                    {
                        op.Push(token);
                        break;
                    }
                    
                    if(stackPriority(x) == 3 && infixPriority(token) == 3)
                    {
                        op.Push(token);
                        break;
                    }
                    
                    x = op.Pop();
                    post.Enqueue(x);
                    if(op.IsEmpty())
                    {
                        break;
                    }
                    x = op.Peek();
                }
                    
                    if(stackPriority(x) == 3 && infixPriority(token) == 3)
                    {
                        continue;
                    }
                    if(stackPriority(x) == 4)
                    {
                        continue;
                    }
                    op.Push(token);
                }
            
            }
        }
        
        while(!(op.IsEmpty()))
        {
            char x = op.Pop();
            post.Enqueue(x);
        }
        cout << post << endl;
        PostfixEval(post);
        while(!(post.IsEmpty()))
        {
            post.Dequeue();
        }
        q.Dequeue();
        yes = true;
        copy.Dequeue();
    }
}

int infixPriority(char x)
{
    if(x == '-')
    {
        return 1;
    }
    else if(x == '+')
    {
        return 1;
    }
    else if(x == '/')
    {
        return 2;
    }
    else if(x == '*')
    {
        return 2;
    }
    else if(x == '^')
    {
        return 3;
    }
    else if(x == '(')
    {
        return 4;
    }
    return 0;
}

int stackPriority(char y)
{
    if(y == '-')
    {
        return 1;
    }
    else if(y == '+')
    {
        return 1;
    }
    else if(y == '/')
    {
        return 2;
    }
    else if(y == '*')
    {
        return 2;
    }
    else if(y == '^')
    {
        return 3;
    }
    else if(y == '(')
    {
        return 4;
    }
    return 0;
}

void PostfixEval(Queue<char> &q)
{
    Stack<double> eval;
    double answer;
    
    while(!(q.IsEmpty()))
          {
              char x = q.Dequeue();
              if(isOperand(x))
              {
                  double num = x - '0';
                  eval.Push(num);
              }
              else
              {
                  double a = eval.Pop();
                  double b = eval.Pop();
                  answer = evaluation(b, a, x);
                  eval.Push(answer);
              }
          }
    cout << answer << endl;
    cout << endl;
}

double evaluation(double a, double b, char c)
{
    double answer;
    
    if(c == '+')
    {
        answer = a + b;
    }
    else if(c == '-')
    {
        answer = a - b;
    }
    else if(c == '/')
    {
        answer = a / b;
    }
    else if(c == '*')
    {
        answer = a * b;
    }
    
    else if(c == '^')
    {
        answer = pow(a, b);
    }
    
    
    return answer;
}












