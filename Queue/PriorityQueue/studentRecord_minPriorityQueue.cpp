// STL을 이용하지 않은 풀이

#include <iostream>
#include <string>

using namespace std;

// heap에 저장될 내용을 위한 class 정의
class element {
    public :
        string name;
        string id;
        string school;
        void set_data(string n, string i, string s);
};

void element::set_data(string n, string i, string s) {
    name = n;
    id = i;
    school = s;
}

#define HSIZE 30

// heap 기본 구조 class 정의
class my_heap {
    element mp_queue[HSIZE];
    int size; // the number of elements

    public :
        my_heap();
        int h_size(); // class 외부에서 heap 크기 알고 싶을 때 사용
        void insert_heap(element stu);
        element extract_min();
        element minimum();
        int decrease_key(int troot, string id);
        void print_record();
};

my_heap::my_heap() {
    size = 0;
}

int my_heap::h_size() {
    return size;
}

void my_heap::insert_heap(element stu) {
    int k;
    size++; 
    k = size; 
    while((k != 1) && (stu.id < mp_queue[k/2].id)) { 
        mp_queue[k] = mp_queue[k/2];
        k/=2; 
    }
    mp_queue[k] = stu;
    cout << "\nNew element " << "[" << mp_queue[k].name << ", " << mp_queue[k].id << ", " << mp_queue[k].school << "]" << " is inserted." <<endl;
}

element my_heap ::minimum() {
    return mp_queue[1];
}

element my_heap::extract_min() {
    element del;

    del = minimum(); // return 할 원소
    element tmp;
    int parent, child;

    tmp = mp_queue[size]; // 끝 원소
    size--; // 원소 하나 삭제 되기에 전체 원소 개수는 하나 줄어듬
    parent = 1;
    child = 2;
    while((child <= size)) { // 더 이상 child가 없을 때까지 다음을 반복
        if ((child < size ) && (mp_queue[child + 1].id < mp_queue[child].id)) // 오른쪽에 있는 child가 더 값이 작으면
            child++; // 오른쪽에 있는 child 선택
        if (tmp.id <= mp_queue[child].id) // 끝 원소가 child 원소보다 더 작거나 같으면 break
            break;
        mp_queue[parent] = mp_queue[child]; 
        parent = child; 
        child *= 2;
    }
    mp_queue[parent] = tmp; // parent 위치에 끝 원소 오기
    return del; 
}

void adjust_heap(element a[], int t_root, int size) {
    element tmp;
    string tmpkey;
    int child;

    tmp = a[t_root];
    tmpkey = a[t_root].id;
    child = t_root * 2;

    while (child <= size) {
        if ((child < size) && (a[child + 1].id < a[child].id))
            child++;
        if (tmpkey < a[child].id)
            break;
        else {
            a[child/2] = a[child];
            child *= 2;
        }
    }
    a[child/2] = tmp;
}

int update_heap(element mp_queue[], int troot, int idx, string nId, int size) {
    if (idx < 1 || idx > size)
        return 0;
    mp_queue[idx].id = nId;
    for (int k = idx/2 ; k >= 1 ; k--)
        adjust_heap(mp_queue, k, size);
    return 1;
}

int my_heap::decrease_key(int idx, string nId) {
    if (update_heap(mp_queue, 1, idx, nId, size) == 1) {
        return 1; 
    }
    else
        return 0;
}

void my_heap::print_record() {
    cout << endl;
    if (h_size() == 0) {
        cout << "No elements to print!" << endl;
    }
    for (int i = 1 ; i <= h_size() ; i++) {
        cout << "[" << mp_queue[i].name << ", " <<  mp_queue[i].id << ", " << mp_queue[i].school << "]" << " ";
    }
}

// 메뉴
char selectMenu(){
    char menu;
    cout << "\n\n*** MENU *** \n" << endl; 
    cout << "I : Insert new element into queue." << endl;
    cout << "D : Delete element with smallest key from queue." << endl;
    cout << "C : Decrease key of element in queue." << endl;
    cout << "P : Print out all elements in queue." << endl;
    cout << "Q : Quit \n" << endl;
    cout << "Choose menu : "; 
    cin >> menu;
    return menu;
}

string checkValid(string id) {
    while(1) {
        bool v = true;

        if (id.length() != 4) 
            v = false;
        else {
            if (id[0] - '0' <= 0 || 9 < id[0] - '0')
                v = false;
            else {
                for (int i = 1 ; i < 4 ; i++) {
                    if (id[i] - '0' < 0 || 9 < id[i] - '0')
                        v = false;
                } 
            }
        }

        if (v == true)
            return id;

        cout << "Invalid id!" << endl;
        cout << "Enter id of element : ";
        getline(cin, id);
    }
}

int main() {
    char menu;

    string name;
    string id;
    string school;

    element stu;
    int idx;
    string nId;

    my_heap h1;

    while (1) {
        menu = selectMenu();
        if (menu == 'Q') {
            cout << "\nThank you. Bye!" << endl;
            break; 
        }
        if (menu == 'I'){
            cout << "Enter name of element : ";
            cin >> name;
            cout << "Enter id of element : ";
            cin.ignore();
            getline(cin, id);
            id = checkValid(id);
            cout << "Enter school of element : ";
            cin >> school;
            while (school != "Handong" & school != "Doodong" & school != "Sedong") {
                cout << "School name should be either 'Handong' or 'Doodong' or 'Sedong'" <<  endl;
                cout << "Enter school of element : ";
                cin >> school;
            }
            stu.set_data(name, id, school);
            h1.insert_heap(stu);
        }
        else if (menu == 'D'){
            if (h1.h_size() == 0)
                cout << "\nNo elements to delete!" << endl;
            else {
                stu = h1.extract_min();
                cout << "\n[" << stu.name << ", " << stu.id << ", " <<stu.school << "]" << " is deleted." <<endl;  
            }
        }
        else if (menu == 'C'){
            if (h1.h_size() == 0)
                cout << "\nNo elements to modify!" << endl;
            else {
                cout << "Enter index of element : ";
                cin >> idx;
                cout << "Enter id value : ";
                cin.ignore();
                getline(cin, nId);
                nId = checkValid(nId);
                int r = h1.decrease_key(idx, nId);
                if (r == 0) 
                    cout << "\nNo such element! " << endl;
                else {
                    cout << "\nSuccessfully updated! " << endl;
                } 
            }
        }
        else if (menu == 'P'){
            h1.print_record();
        }
    }
}