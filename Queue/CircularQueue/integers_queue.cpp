#include <iostream>

using namespace std;

const int SIZE = 8;

class my_queue {
    int q[SIZE];
    int front, rear;

    public :
        my_queue();
        void insert_q(int x);
        int delete_q();
        bool queue_full();
        bool queue_empty();
        void print_q();
};

my_queue :: my_queue() {
    front = 0;
    rear = 0;
}

void my_queue::insert_q(int x) {
    if (!queue_full()) {
        q[rear] = x;
        rear = (rear + 1) % SIZE;
    }
    else{
        cout<<"\nQueue is Full\n";
        exit(EXIT_FAILURE);
    }
}

int my_queue::delete_q() {
    int tmp;
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

void my_queue::print_q() {
    cout<<"front [";

    for(int i = front ; i < rear ; i++){
        if(i == rear - 1)
            cout<<q[i];
        else
            cout<<q[i]<<",";
    }
    cout<<"] rear\n";
}

int main() {
    my_queue a;
    int t;
    a.print_q();

    // 1~SIZE-1까지의 숫자를 차례로 insert
    // SIZE까지 하면, queue가 full이라서, insert가 안됨
    for(int i = 1; i < SIZE; i++){ 
        cout<<"\nInsert queue "<<i<<"\n";
        a.insert_q(i);
        a.print_q();
    }
    cout<<endl;

    // SIZE 횟수만큼 delete 시도
    // queue가 empty인 마지막 지점은 delete가 안 되는 거 확인!
    for(int i = 0; i < SIZE; i++){
        cout<<"\nDelete queue "<<a.delete_q()<<"\n";
        a.print_q();
    }

    return 0;
}