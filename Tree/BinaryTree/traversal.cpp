#include <iostream>

using namespace std;

class node {
    public :
        string name;
        double score;
        node *left, *right, *link;
        void set_data(string s, double n);
};

void node::set_data(string s, double n) {
    name = s;
    score = n;
}

class my_tree {
    public :
        int node_count;
        node *root;
        my_tree();
        int insert_root(node t);
        int insert_left(string tname, node t);
        int insert_right(string tname, node t);

        void print_data_inorder();
        void print_data_preorder();
        void print_data_postorder();
        void print_data_levelorder(); //level order 구현 
};

my_tree::my_tree() {
    node_count = 0;
    root = NULL;
}

// node의 포인터 타입을 저장하는 queue 생성
class my_queue {
    node *front, *rear;
    public :
        my_queue();
        void insert_q(node *t);
        node* delete_q();
        bool is_q_empty();
};

my_queue::my_queue() {
    front=NULL;
    rear=NULL;
}

// root node 설정
int my_tree::insert_root(node t) {
    if (root != NULL)
        return 0;
    node* p;
    p = new node;
    (*p) = t;
    p->left = NULL;
    // (*p).left = NULL; 와 같은 표현
    p->right = NULL;
    root = p;
    node_count++;
    return 1;
}

int node_insert_left(node *p, string tname, node tnode) {
    if (p == NULL)
        return 0;
    if (p->name == tname) {
        if (p->left != NULL)
            return -1;
        node *t;
        t = new node;
        (*t) = tnode;
        t->left = NULL;
        t->right = NULL;
        p->left = t;
        return 1;
    }
    else {
        int result;
        result = node_insert_left(p->left, tname, tnode);
        if (result != 0)
            return result;
        return node_insert_left(p->right, tname, tnode);
    }
}

// 이름이 tname인 node의 왼쪽에 tnode를 넣어라
int my_tree::insert_left(string tname, node tnode) {
    int result = node_insert_left(root, tname, tnode);
    if (result == 1)
        node_count++;
    return result;
}

int node_insert_right(node *p, string tname, node tnode) {
    if (p == NULL)
        return 0;
    if (p->name == tname) {
        if (p->right != NULL)
            return -1;
        node *t;
        t = new node;
        (*t) = tnode;
        t->left = NULL;
        t->right = NULL;
        p->right = t;
        return 1;
    }
    else {
        int result;
        result = node_insert_right(p->left, tname, tnode);
        if (result != 0)
            return result;
        return node_insert_right(p->right, tname, tnode);
    }
}

// 이름이 tname인 node의 오른쪽에 tnode를 넣어라
int my_tree::insert_right(string tname, node tnode) {
    int result = node_insert_right(root, tname, tnode);
    if (result == 1)
        node_count++;
    return result;
}

void inorder_print(node *p) {
    if (p == NULL)
        return;
    inorder_print(p->left);
    cout<<p->name<<":"<<p->score<<"\n";
    inorder_print(p->right);
}

// inorder traversal
void my_tree::print_data_inorder() {
    inorder_print(root);
}

void preorder_print(node *p) {
    if (p == NULL)
        return;
    cout<<p->name<<":"<<p->score<<"\n";
    preorder_print(p->left);
    preorder_print(p->right);
}

// preorder traversal
void my_tree::print_data_preorder() {
    preorder_print(root);
}

void postorder_print(node *p) {
    if (p == NULL)
        return;
    postorder_print(p->left);
    postorder_print(p->right);
    cout<<p->name<<":"<<p->score<<"\n";
}

// postorder traversal
void my_tree::print_data_postorder() {
    postorder_print(root);
}

void my_queue::insert_q(node *t) {
    node *p;
    p = new node;
    p = t;
    p->link = NULL;
    if (rear != NULL)
        rear->link = p;
    else
        front = p;
    rear = p;
}

node* my_queue::delete_q() {
    if (!is_q_empty()) {
        node *p = front;
        node *t = front;
        front = front->link;
        delete t;
        if (front == NULL)
            rear = NULL;
        return p;
    }
    else {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
}

bool my_queue::is_q_empty() {
    if (front == NULL)
        return true;
    else
        return false;
}

// level order traversal
void my_tree::print_data_levelorder() {
    my_queue a1;
    node *t;
    if (root == NULL)
        return;
    a1.insert_q(root);
    while(1) {
        if (a1.is_q_empty())
            return;
        t = a1.delete_q();
        cout<<t->name<<":"<<t->score<<"\n";
        if (t->left != NULL)
            a1.insert_q(t->left);
        if (t->right != NULL)
            a1.insert_q(t->right);
    }
}

int main() {
    my_tree thetree;
    node tmp;

    tmp.set_data("Kim", 8.1);
    thetree.insert_root(tmp);

    tmp.set_data("Lee", 6.5);
    thetree.insert_left("Kim",tmp);

    tmp.set_data("Park", 8.3);
    thetree.insert_right("Kim", tmp);

    tmp.set_data("Choi", 7.2);
    thetree.insert_left("Lee",tmp);

    tmp.set_data("Ryu", 9.0);
    thetree.insert_right("Lee",tmp);

    tmp.set_data("Cho", 7.7);
    thetree.insert_right("Park",tmp);

    cout<<"\nInorder Traversal Result \n"; 
    thetree.print_data_inorder();

    cout<<"\nPreorder Traversal Result \n"; 
    thetree.print_data_preorder();

    cout<<"\nPostorder Traversal Result \n"; 
    thetree.print_data_postorder();

    cout<<"\nLevel order Traversal Result \n";
    thetree.print_data_levelorder();

    return 0;
}