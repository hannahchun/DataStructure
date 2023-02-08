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

    public :
        my_heap();
        int h_size(); // class 외부에서 heap 크기 알고 싶을 때 사용
        void insert_heap(element t);
        element delete_heap();
        bool heap_full();
        bool heap_empty();
};

my_heap::my_heap() {
    csize = 0;
}

bool my_heap::heap_empty() {
    if (csize == 0)
        return true;
    else
        return false;
}

bool my_heap::heap_full() {
    if (csize >= HSIZE - 1)
        return true;
    else
        return false;
}

int my_heap::h_size() {
    return csize;
}

// node 추가
void my_heap::insert_heap(element t) {
    int k;
    csize++; // size 1 증가
    k = csize; // 맨 끝 위치부터 시작
    while((k != 1) && (t.score > h[k/2].score)) { // k가 root가 아니거나, parent의 값이 t보다 작으면 아래 반복
        h[k] = h[k/2]; // 현재 위치에 parent 값 넣어
        k/=2; // parent 위치로 옮김
    }
    h[k] = t; // 확정된 위치에 t 넣음
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

int main() {
    my_heap h1;

    element temp;
    temp.set_data("Kim", 88);
    h1.insert_heap(temp);
    temp.set_data("Lee", 77);
    h1.insert_heap(temp);
    temp.set_data("Park", 98);
    h1.insert_heap(temp);
    temp.set_data("Choi", 74);
    h1.insert_heap(temp);
    temp.set_data("Ryu", 94);
    h1.insert_heap(temp);
    temp.set_data("Cho", 85);
    h1.insert_heap(temp);

    while(h1.h_size() > 0) {
        temp = h1.delete_heap();
        cout<<temp.name<<":"<<temp.score<<"\n";
    }
    return 0;
}