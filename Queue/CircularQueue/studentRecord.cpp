#include <iostream>

using namespace std;

const int SIZE = 8;

class element {
    public :
        string s_name;
        string phone_no;
        void set_data(string s1, string s2);
};

void element::set_data(string s1, string s2) {
    s_name = s1;
    phone_no = s2;
}

// element 의 object 를 원소로 저장하는 circular queue 구현
class my_queue {
    element q[SIZE];
    int front, rear;

    public :
        my_queue();
        void insert_q(element x);
        element delete_q();
        bool queue_full();
        bool queue_empty();
};

my_queue:: my_queue() {
    front = 0;
    rear = 0; 
}

void my_queue::insert_q(element x) {
    if (!queue_full()) {
        q[rear] = x;
        rear = (rear + 1) % SIZE;
    }
    else{
        cout<<"\nQueue is Full\n";
        exit(EXIT_FAILURE);
    }
}

element my_queue::delete_q() {
    element tmp;
    if (!queue_empty()) {
        tmp = q[front];
        front = (front + 1) % SIZE;
        return tmp;
    }
    else{
        cout<<"\n\nQueue is Empty!\n";
        exit(EXIT_FAILURE);
    }
}

bool my_queue::queue_full() {
    if ((rear + 1) % SIZE == front)
        return true;
    else
        return false;
}

bool my_queue::queue_empty() {
    if (rear == front)
        return true;
    else
        return false;
}

int main() {
    my_queue a; 
    element tmp;
    
    tmp.set_data("KIM", "010-1234-5678"); 
    a.insert_q(tmp);
    tmp.set_data("LEE", "010-1357-2468"); 
    a.insert_q(tmp);
    tmp.set_data("PARK", "010-9876-5432"); 
    a.insert_q(tmp);
    
    while (!a.queue_empty() ) {
        tmp = a.delete_q();
        cout << tmp.s_name << " : " << tmp.phone_no<< "\n"; 
    }
    return 0; 
}
