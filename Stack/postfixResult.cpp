// Calculate postfix expression
#include <iostream>
#include <string>

using namespace std;

#define SIZE 100

class op_stack {
    int s[SIZE];
    int top;

    public :
        op_stack();
        void push(int x);
        int pop();
        bool empty();
        char top_element(); // 현재 top 원소와 새로운 연산자 간 우선순위 비교하기 위해 필요
};

op_stack::op_stack() {
    top = 0;
}

void op_stack:: push(int x) { 
    s[top] = x;
    top++; 
}

int op_stack::pop() { 
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

int main() {
    op_stack stack1;

    string input;

    int v1;
    int v2;
    int res;

    cout << "Input an posfix expression to calculate : ";
    cin >> input;

    for (int i = 0 ; i < input.size() ; i++) {
        if (is_operand(input[i]))
            stack1.push(input[i] - '0');
        else {
            v1 = stack1.pop();
            v2 = stack1.pop();
            if (input[i] == '+')
                res = v2 + v1;
            if (input[i] == '-')
                res = v2 - v1;
            if (input[i] == '*')
                res = v2 * v1;
            if (input[i] == '/')
                res = v2 / v1;
            stack1.push(res);
        }
    }
    cout << "Result : " << stack1.pop() << endl;
}