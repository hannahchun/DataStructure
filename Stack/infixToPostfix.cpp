// Convert infix expression to postfix expression
#include <iostream>
#include <string>

using namespace std;

#define SIZE 100
#define EOS '$'

class op_stack {
    char s[SIZE];
    int top;

    public :
        op_stack();
        void push(char x);
        char pop();
        bool empty();
        char top_element(); // 현재 top 원소와 새로운 연산자 간 우선순위 비교하기 위해 필요
};

op_stack::op_stack() {
    top = 0;
}

void op_stack:: push(char x) { 
    s[top] = x;
    top++; 
}

char op_stack::pop() { 
    top--;
    return(s[top]); 
}

bool op_stack::empty() { 
    return (top == 0);
}

char op_stack::top_element() {
    return (s[top-1]);
}

bool is_operand(char ch) {
    if ( (ch == '(') || (ch == ')') || (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '%') || (ch == '$') )
        return false; 
    else
        return true;
}

int get_precedence(char op) {
    if ( (op == '$') || (op == '(' ) ) 
        return 0;
    if ( (op == '+') || (op == '-' ) ) 
        return 1;
    if ( (op == '*') || (op == '/' ) || (op == '%' ) ) 
        return 2;
    else
        return -1;
}

int main() {
    op_stack stack1;

    string input, output;

    cout << "Input an infix expression to convert: ";
    cin >> input;

    stack1.push(EOS);

    for (int i = 0 ; i < input.size() ; i++) {
        if (is_operand(input[i]))
            output += input[i];
        else {
            if (input[i] == '(')
                stack1.push(input[i]);
            else {
                if (input[i] == ')') {
                    while (stack1.top_element() != '(' )
                       output += stack1.pop();
                    stack1.pop();
                }
                else {
                    while (get_precedence(input[i]) < get_precedence(stack1.top_element()))
                        output += stack1.pop();
                    stack1.push(input[i]);
                }
            }
        }
    }

    while(stack1.top_element() != '$')
        output += stack1.pop();
    
    cout<<output<<endl;
}