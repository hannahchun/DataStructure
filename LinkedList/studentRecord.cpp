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
class my_list {
    node *head, *tail; // data node의 첫 노드와 마지막 노드를 가리키는 포인터
    public:
        my_list(); // head와 tail이 NULL로 초기화된 linked list 만들어
        void add_to_head(node t);
        void add_to_tail(node t);
        node delete_from_head();
        int num_nodes();
        bool list_empty();
        double score_sum();
        double get_score(string t_name);
        int remove_node(string t_name);
};

my_list::my_list(){
    head = NULL;
    tail = NULL;
}

// add to head
void my_list::add_to_head(node t){
    // Dynamic memory로부터 node 공간 확보
    node *p;
    p = new node;
    // node에 데이터값 저장
    (*p) = t;
    // link를 조정하여 list에 연결 
    p->link = head;
    head = p;
    if(tail == NULL)
        tail = p;
}

// add to tail
void my_list::add_to_tail(node t){
    // Dynamic memory로부터 node 공간 확보
    node *p;
    p = new node;
    // node에 데이터값 저장
    (*p) = t;
    // tail node가 가리키는 node는 없음
    p->link = NULL;
    if(tail != NULL) // 이전 상태가 empty가 아니었다면
        tail->link = p;
    else
        head = p;
    tail = p;
}

// delete from head
node my_list::delete_from_head(){
    node temp; // 삭제된 head 내용 리턴하기 위함
    node *t; 
    t = head; // 지워질 head를 붙잡아
    temp = *head; // temp로 head 내용을 복사
    head = head->link;
    delete t; // 기존 head 삭제
    if(head == NULL)
        tail = NULL;
    return temp;
}

// the total number of nodes
int my_list::num_nodes(){
    node *t;
    int count = 0;
    for(t = head ; t != NULL ; t = t->link)
        count++;
    return count;
}

// is the list empty
bool my_list::list_empty(){
    if(head == NULL)
        return true;
    else
        return false;
}

// the total score of all nodes
double my_list::score_sum(){
    node *t;
    double sum = 0.0;
    for(t = head ; t != NULL ; t = t->link)
        sum += t->score;
    return sum;
}

// get the score of the node whose name is 't_name'
double my_list::get_score(string t_name){
    node *t;
    double score = 0.0;
    for(t = head ; t != NULL ; t = t->link){
        if(t->name == t_name){
            score = t->score;
            break;
        }
    }
    return score;
}

// remove the node whose name is 't_name'
// success: return 1 , fail: return 0
int my_list::remove_node(string t_name){
    // find the node whose name is 't_name'
    node *t;
    for(t = head ; t != NULL ; t = t->link){
        if(t->name == t_name)
            break;
    }

    // could not find the node with the given name
    if(t == NULL)
        return 0;

    // found the node with the given name
    // find the position of that node
    if(t == head) {
        head = head->link;
        delete t;
        if(head == NULL)
            tail = NULL;
        return 1;
    }

    else if(t == tail) {
        // find the second to the last node
        node *s;
        for(s = head ; s != NULL ; s = s->link){
            if(s->link->link == NULL)
                break;
        }
        tail = s;
        tail->link = NULL;
        delete t;
        return 1;
    }

    else{
        // find the node right before it
        node *b;
        for(b = head ; b != NULL ; b = b->link){
            if(b->link == t)
                break;
        }
        b->link = t->link;
        delete t;
        return 1;
    }
}

int main(){
    my_list a;
    node tmp;

    // add two nodes in the head position
    tmp.set_data("Kim",83.5);
    a.add_to_head(tmp);
    tmp.set_data("Lee",78.2);
    a.add_to_head(tmp);
    cout<<a.num_nodes()<<": "<<a.score_sum()<<"\n"; // check

    // add a node in the tail position
    tmp.set_data("Park",91.3);
    a.add_to_tail(tmp);
    cout<<a.num_nodes()<<": "<<a.score_sum()<<"\n"; // check

    // delete a node in the head position
    tmp = a.delete_from_head();
    cout<<tmp.name<< " is deleted.\n"; //check

    // add a node in the tail position and another in the head position
    tmp.set_data("Choi",85.1);
    a.add_to_tail(tmp);
    tmp.set_data("Ryu",94.3);
    a.add_to_head(tmp);
    cout<<a.num_nodes()<<": "<<a.score_sum()<<"\n"; // check

    // get the score of the node with the name, "Park"
    cout<<"Park's score: "<<a.get_score("Park")<<"\n";
    
    // remove the node with the name, "Kim"
    if(a.remove_node("Kim")==1)
        cout<<"Kim is deleted from the list. \n";
    cout<<a.num_nodes()<<": "<<a.score_sum()<<"\n"; // check 
    return 0;
}
