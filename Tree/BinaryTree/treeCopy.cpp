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

// root 이하의 내용과 동일한 tree 생성하여 root에 copy
node * make_copy(node *p) {
    if (p == NULL)
        return NULL;
    node *t = new node; 
    *t = *p;
    t->left = make_copy(p->left);
    t->right = make_copy(p->right);
    return t;
}

// t1에 t2의 구조와 내용을 copy
void copy_tree(my_tree &t1, my_tree t2) {
    t1.node_count = t2.node_count;
    t1.root = make_copy(t2.root);
}

bool equal_test(node* p1, node* p2) {
    if ((p1 == NULL) && (p2 == NULL))
        return true;
    if (p1 == NULL)
        return false;
    if (p2 == NULL)
        return false;
    if (p1->name != p2->name)
        return false;
    if (p1->score != p2->score)
        return false;
    
    if (equal_test(p1->left, p2->left) && equal_test(p1->right, p2->right))
        return true;
    else
        return false;
}

// t1과 t2의 구조와 내용이 같은지 확인
bool equal_tree(my_tree t1, my_tree t2) {
    if (t1.node_count != t2.node_count)
        return false;
    return equal_test(t1.root,t2.root);
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

    my_tree tree2;
    // thetree의 구조와 내용을 tree2에 복사
    copy_tree(tree2, thetree); 

    // 확인 1
    cout<<"\nInorder Traversal Result \n"; 
    tree2.print_data_inorder();

    // 확인 2
    if (equal_tree(tree2, thetree)) 
        cout<<"\nYes\n";
    else
        cout<<"\nNo\n";

    // thetree의 내용에 변화를 주기
    tmp.set_data("Youn", 7.7);
    thetree.insert_right("Cho", tmp);
    if (equal_tree(tree2, thetree)) 
        cout<<"\nYes\n";
    else
        cout<<"\nNo\n";
    return 0;
}