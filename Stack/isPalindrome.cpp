// Palindrome 여부 check 프로그램
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

int main() {
    op_stack stack1;

    string input;
    int i;
    int bidx; // 뒷쪽 절반 시작 인덱스
    bool isValid = true;

    cout << "Input a string : ";
    cin >> input;

    for (i = 0 ; i < input.size() / 2 ; i++)
        stack1.push(input[i]);
    
    // 홀수 길이는 중간 문자 무시
    if (input.size() % 2 != 0) 
        bidx = input.size() / 2 + 1;
    else 
        bidx = input.size() / 2;

    for (i = bidx ; i < input.size() ; i++) {
        if (input[i] != stack1.pop()) {
            isValid = false;
            break;
        }
    }

    if (isValid == true)
        cout << "Yes, it’s a palindrome." << endl;
    else
        cout << "No, it’s not a palindrome." << endl;

    return 0;
}