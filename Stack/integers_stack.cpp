#include <iostream>

using namespace std;

const int SIZE = 5;

class my_stack {
    int mystack[SIZE];
    int top;

    public :
        void init();
        void push(int x);
        int pop();
        bool stack_full();
        bool stack_empty();
};

void my_stack::init() {
    top = 0;
}

void my_stack::push(int a) {
    if (stack_full()) {
        cout<<"\n\nStack is Full!\n";
        exit(EXIT_FAILURE);
    }
    mystack[top] = a;
    top++;
}

int my_stack::pop() {
    if (stack_empty()) {
        cout<<"\n\nStack is Empty!\n";
        exit(EXIT_FAILURE);
    }
    top--;
    return(mystack[top]);
}

bool my_stack::stack_full() {
    if (top >= SIZE)
        return true;
    else
        return false;
}

bool my_stack::stack_empty() {
    if (top == 0)
        return true;
    else
        return false;
}

int main() {
    my_stack s1;
    
    s1.init();

    int list[5] = { 32, 123, 27, 131, 242 }, i, x;

    for (i = 0 ; i < 5 ; i++)
        if (list[i] > 100)
            s1.push(list[i]);
    
    while (!s1.stack_empty()) {
        x = s1.pop();
        cout << x << endl;
    }

    return 0;
}