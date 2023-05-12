// Use linked list to implement queue

// the first element of the linked list is the front position (place to delete) of the queue
// the last element of the linked list is the rear position (place to add) of the queue

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
class my_queue {
    node *front, *rear; // top 노드를 가리키는 포인터 
    public :
        my_queue();
        void insert_queue(node t);
        node delete_queue();
        bool queue_empty();
};

my_queue::my_queue(){
    front = NULL;
    rear = NULL;
}

void my_queue::insert_queue(node t){
    node *p;
    p = new node;
    (*p) = t;
    p->link = NULL;
    if(rear != NULL)
        rear->link = p;
    else
        front = p;
    rear = p;
}

bool my_queue::queue_empty(){
    if(front == NULL)
        return true;
    else    
        return false;
}

node my_queue::delete_queue(){
    node temp;
    if(!queue_empty()){
        node *t;
        temp = *front;
        t = front;
        front = front->link;
        delete t;
        if(front == NULL)
            rear = NULL;
    }
    return temp;
}

int main() {
    my_queue a;
    node tmp;
    
    tmp.set_data("KIM", 22.2);
    a.insert_queue(tmp);
    tmp.set_data("LEE",33.3);
    a.insert_queue(tmp);
    tmp.set_data("PARK", 44.4);
    a.insert_queue(tmp);
    tmp.set_data("CHOI",55.5);
    a.insert_queue(tmp); 

    tmp=a.delete_queue();
    cout<<tmp.name<<":"<<tmp.score<<"\n";
    tmp=a.delete_queue();
    cout<<tmp.name<<":"<<tmp.score<<"\n";
    return 0;
}