// Use linked list to implement stack

// the first element of the linked list is the top of the stack
// push and pop operations are all conducted in the top of the stack

#include <iostream>

using namespace std;

// data node
class node {
    public:
        string name;
        double score;
        node *link; // 다음 노드를 가리키는 포인터
        void set_data(string s, double n);
};

void node::set_data(string s, double n){
    name = s;
    score = n;
}

// list node 
class my_stack {
    node *top; // top 노드를 가리키는 포인터 
    public :
        my_stack();
        void push(node t);
        node pop();
        bool stack_empty();
};

my_stack::my_stack(){
    top = NULL;
}

void my_stack::push(node t){
    node *p;
    p = new node;
    (*p) = t;
    p->link = top;
    top = p;
}

bool my_stack::stack_empty(){
    if(top == NULL)
        return true;
    else    
        return false;
}

node my_stack::pop(){
    node temp;
    if(!stack_empty()){
        node *t;
        t = top;
        temp = *top;
        top = top->link;
        delete t;
        
    }
    return temp;
}

int main() {
    my_stack a;
    node tmp;
    
    tmp.set_data("KIM", 22.2);
    a.push(tmp);
    tmp.set_data("LEE",33.3);
    a.push(tmp);
    tmp.set_data("PARK", 44.4);
    a.push(tmp);
    tmp.set_data("CHOI",55.5);
    a.push(tmp); 

    tmp=a.pop();
    cout<<tmp.name<<":"<<tmp.score<<"\n";
    tmp=a.pop();
    cout<<tmp.name<<":"<<tmp.score<<"\n";
    return 0;
}
