#include <iostream>

using namespace std;

// heap에 저장될 내용을 위한 class 정의
class element {
    public :
        string name;
        double score;
        void set_data(string n, double s);
};

void element::set_data(string n, double s) {
    name = n;
    score = s;
}

#define HSIZE 100

// heap 기본 구조 class 정의
class my_heap {
    element h[HSIZE];
    int csize; // the number of elements
    void adjust(int t_root);

    public :
        my_heap();
        my_heap(element a[], int n);
        int h_size(); // class 외부에서 heap 크기 알고 싶을 때 사용
        element delete_heap();
        double score_sum();
        double score_average();
        int node_delete_by_name(string tname);
};

my_heap::my_heap() {
    csize = 0;
}

my_heap::my_heap(element a[], int n) {
    int k;

    for (k = 1; k <= n; k++)
        h[k] = a[k-1];
    csize = n;

    for (k = n/2 ; k >= 1 ; k--)
        adjust(k);
}

void my_heap::adjust(int t_root) {
    element tmp;
    double tmpkey;
    int child;

    tmp = h[t_root];
    tmpkey = h[t_root].score;
    child = t_root * 2;

    while (child <= csize) {
        if ((child < csize) && (h[child].score < h[child+1].score))
            child++;
        if (tmpkey > h[child].score)
            break;
        else {
            h[child/2] = h[child];
            child *= 2;
        }
    }
    h[child/2] = tmp;
}

int my_heap::h_size() {
    return csize;
}

// node 삭제
element my_heap::delete_heap() {
    element t;
    element tmp;
    int parent, child;

    t = h[1]; // return 할 원소
    tmp = h[csize]; // 끝 원소
    csize--; // 원소 하나 삭제 되기에 전체 원소 개수는 하나 줄어듬
    parent = 1;
    child = 2;
    
    while((child <= csize)) { // 더 이상 child가 없을 때까지 다음을 반복
        if ((child < csize ) && (h[child].score < h[child+1].score)) // 오른쪽에 있는 child가 더 값이 크면
            child++; // 오른쪽에 있는 child 선택
        if (tmp.score >= h[child].score) // 끝 원소가 child 원소보다 더 크거나 같으면 break
            break;
        h[parent] = h[child]; // parent 위치에 child가 오고
        parent = child; 
        child *= 2;
    }
    h[parent] = tmp; // parent 위치에 끝 원소 오기
    return t; 
}

double summation(element a[], int troot, int n) {
    if (troot > n) 
        return 0;
    return (a[troot].score + summation(a, 2*troot, n) + summation (a, 2*troot+1, n));
}

double my_heap::score_sum() {
    return summation(h, 1, csize);
}

double my_heap::score_average() {
    if (csize == 0) return 0;
    return score_sum() / csize;
}

// member 함수의 adjust() 기능을 일반함수로서 구현
// 주어진 배열과 주어진 size에 대하여 적용하도록 구현
void heap_adjust(element a[], int t_root, int size) {
    element tmp;
    double tmpkey;
    int child;

    tmp = a[t_root];
    tmpkey = a[t_root].score;
    child = t_root * 2;

    while (child <= size) {
        if ((child < size) && (a[child].score < a[child+1].score))
            child++;
        if (tmpkey > a[child].score)
            break;
        else {
            a[child/2] = a[child];
            child *= 2;
        }
    }
    a[child/2] = tmp;
}

int delete_node(element a[], int troot, string tname, int n) {
    if (troot > n)
        return 0;
    else if (a[troot].name == tname) {
        element tmp = a[troot];
        a[troot] = a[n];
        a[n] = tmp;

        if (n != troot*2) {
            if (n != troot*2+1)
                heap_adjust(a, troot, n);
            else
                heap_adjust(a, troot, n-1); 
        }
        return 1;
    }
    else {
        int res;
        res = delete_node(a, troot*2, tname, n);
        if (res == 1)
            return res;
        return delete_node(a, troot*2+1, tname, n);
    }
}

int my_heap::node_delete_by_name(string tname) {
    if (csize == 0) 
        return 0;
    if (delete_node(h, 1, tname, csize) == 1) {
        csize--;
        return 1; 
    }
    else
        return 0;
}

int main() {
    element a[10] = {{"Kim", 88}, {"Lee", 77}, {"Park", 98}, {"Choi", 74}, {"Ryu", 94}, {"Cho", 85}};

    my_heap h1(a, 6);

    cout << "Number of nodes : " << h1.h_size() << endl;
    cout << "Score Sum = " << h1.score_sum() << endl;
    cout << "Score average = " << h1.score_average() << endl;

    h1.node_delete_by_name("Kim");
    cout << "\n-- After the deletion operation. --\n\n";
    cout << "Number of nodes : " << h1.h_size() << endl;
    cout << "Score Sum = " << h1.score_sum() << endl;
    cout << "Score average = " << h1.score_average() << endl;
    cout << "\n";

    while(h1.h_size() > 0) {
        element temp = h1.delete_heap();
        cout<<temp.name<<":"<<temp.score<<"\n";
    }
}