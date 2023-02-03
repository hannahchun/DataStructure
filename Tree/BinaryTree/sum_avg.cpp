#include <iostream>

using namespace std;

class node {
    public :
        string name;
        double score;
        node *left, *right;
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
        double score_sum();
        double score_average();
};

my_tree::my_tree() {
    node_count = 0;
    root = NULL;
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

double sum_allnodes(node *p) {
    if (p == NULL)
        return 0;
    return sum_allnodes(p->left) + sum_allnodes(p->right) + p->score;
}

// 모든 node의 score 합
double my_tree::score_sum() {
    return sum_allnodes(root);
}

// 모든 node의 score 평균
double my_tree::score_average() {
    double sum = sum_allnodes(root);
    return sum/node_count;
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

    cout<<"Score Sum: "<<thetree.score_sum()<<"\n";
    cout<<"Score Average: "<<thetree.score_average()<<"\n";
    cout<<"\nInorder Traversal Result \n"; 
    thetree.print_data_inorder();

    return 0;
}