// 수식 표현에서 괄호 사용의 오류 점검
#include <iostream>
#include <string>

using namespace std;

#define SIZE 100

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

bool is_parenthesis(char ch) {
    return((ch == '(') || (ch == ')' || ch == '{') || (ch == '}' || ch == '[') || (ch == ']'));
}

bool check_parenthesis (char close, char open) { 
    if (close == ')')
        return (open == '(');
    if (close == '}')
        return (open == '{');
    if (close == ']')
        return (open == '[');
    return 0;
}

// 열린 괄호에 필요한 닫힌 괄호
char close_parenthesis (char open) {
    if (open == '(')
        return ')';
    if (open == '{')
        return '}';
    if (open == '[')
        return ']';
    return 0;
}

// 닫힌 괄호에 필요한 열린 괄호
char open_parenthesis (char close) {
    if (close == ')')
        return '(';
    if (close == '}')
        return '{';
    if (close == ']')
        return '[';
    return 0;
}

int main() {
    op_stack stack1;

    string input;
    int i;
    char temp;

    cout << "Input an infix expression to check for balanced parenthesis : ";
    cin >> input;

    for (i = 0 ; i < input.size() ; i++) {
        if (is_parenthesis(input[i])) {
            // 여는 괄호는 stack에 넣기
            if (input[i] == '(' || input[i] == '{' || input[i] == '[') {
                stack1.push(input[i]);
            }
            // 닫는 괄호는 stack에 있는 여는 괄호와 비교
            else  {
                // 여는 괄호 부족
                if (stack1.empty()) {
                    cout << "여는 괄호 부족" << endl;
                    cout << "An extra parenthesis " << input[i] << " is found!" << endl;
                    // cout << open_parenthesis(input[i]) << " is expected." << endl;
                    break;
                }
                // 여는 괄호는 존재하고 type 비교
                else {
                    char temp = stack1.pop();
                    if (!check_parenthesis (input[i], temp)) {
                        cout << "괄호 type이 맞지 않음" << endl;
                        cout << close_parenthesis(temp) << " is expected." << endl;
                        break;
                    }
                }
            }
        }
    }
    
    if (i == input.size()) {
        // 끝까지 불일치가 발생하지 않고, 최종 stack의 상태가 empty
        if (stack1.empty())
            cout << "정상적 수식" << endl;
        // 입력 처리가 종료된 후에 stack에 내용이 남아있음
        else {
            cout << "닫는 괄호 부족" << endl;
            cout << "An extra parenthesis " << stack1.pop() << " is found!" << endl;
        }
    }
   
    return 0;
}