#include <iostream>
#include <cstdlib>
using namespace std;

typedef int elementtype;
typedef struct Node* nodetype;
struct Node {
    elementtype elements;
    nodetype Next;
};

typedef nodetype position;
typedef position list;

void makenulllist(list *header) {
    (*header) = (nodetype)malloc(sizeof(struct Node));
    (*header)->Next = NULL;
}

int emptylist(list l) {
    return l->Next == NULL;
}

position first(list l) {
    return l;
}

position endlist(list l) {
    position p = first(l);
    while (p->Next != NULL) {
        p = p->Next;
    }
    return p;
}

position next(position p, list l) {
    return p->Next;
}

// Hàm retrieve đã sửa lỗi Warning của bạn
elementtype retrieve(position p, list l) {
    if (p->Next != NULL) {
        return p->Next->elements;
    }
    return -1; 
}

void insertlist(elementtype x, position p, list *l) {
    position t;
    t = (nodetype)malloc(sizeof(struct Node));
    t->elements = x;
    t->Next = p->Next;
    p->Next = t;
}

void nhapds(list *l) {
    int n;
    cout << "Nhap so luong phan tu : ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        elementtype pt;
        cout << "Phan tu thu " << i + 1 << ": ";
        cin >> pt;
        insertlist(pt, endlist(*l), l);
    }
}

void inds(list l) {
    position p = first(l);
    while (p != endlist(l)) {
        cout << retrieve(p, l) << " ";
        p = next(p, l);
    }
    cout << endl;
}

// --- HÀM CHÈN GIỮ NGUYÊN THỨ TỰ TĂNG ---
void insertSorted(list *l) {
    elementtype x;
    cout << "\nNhap gia tri x can chen: ";
    cin >> x;

    position p = first(*l);
    while (p != endlist(*l)) {
        if (retrieve(p, *l) >= x) {
            break; 
        }
        p = next(p, *l);
    }
    insertlist(x, p, l);
}

int main() {
    list l;
    makenulllist(&l);
    
    cout << "--- NHAP DANH SACH TANG DAN ---" << endl;
    nhapds(&l); // Bạn hãy nhập các số tăng dần, ví dụ: 2 5 8 10
    
    cout << "\nDanh sach truoc khi chen: ";
    inds(l);
    
    // Gọi hàm chèn x
    insertSorted(&l);
    
    cout << "Danh sach sau khi chen x: ";
    inds(l);
    
    return 0;
}