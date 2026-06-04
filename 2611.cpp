#include <iostream>
using namespace std;

// =========================== CẤU TRÚC NODE ===========================
struct Node {
    int data;
    Node* next;
    
    // Constructor
    Node(int value = 0, Node* nextPtr = nullptr) 
        : data(value), next(nextPtr) {}
};

// =========================== TẠO NODE MỚI ===========================
Node* createNode(int value) {
    return new Node(value);
}

// =========================== THÊM VÀO CUỐI DANH SÁCH ===========================
void append(Node*& head, int value) {
    Node* newNode = createNode(value);
    
    if (head == nullptr) {
        head = newNode;
        return;
    }
    
    Node* cur = head;
    while (cur->next != nullptr) {
        cur = cur->next;
    }
    cur->next = newNode;
}

// =========================== HIỂN THỊ DANH SÁCH ===========================
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "Danh sách rỗng." << endl;
        return;
    }
    
    Node* cur = head;
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

// =========================== GIẢI PHÓNG BỘ NHỚ ===========================
void freeList(Node*& head) {
    Node* cur = head;
    while (cur != nullptr) {
        Node* temp = cur;
        cur = cur->next;
        delete temp;
    }
    head = nullptr;
}

// =========================== MERGE SORT CHO LINKED LIST ===========================

// Chia danh sách thành 2 nửa (slow/fast pointer)
Node* split(Node* head) {
    Node* slow = head;
    Node* fast = head->next;  // Fast đi trước 2 bước
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    Node* mid = slow->next;
    slow->next = nullptr;     // Cắt liên kết giữa 2 nửa
    return mid;
}

// Trộn 2 danh sách đã sắp xếp
Node* merge(Node* left, Node* right) {
    // Trường hợp cơ bản
    if (!left) return right;
    if (!right) return left;
    
    Node* result = nullptr;
    
    // Chọn phần tử nhỏ hơn làm đầu
    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    
    return result;
}

// Sắp xếp Merge Sort
Node* mergeSort(Node* head) {
    // Điều kiện dừng: danh sách rỗng hoặc có 1 phần tử
    if (!head || !head->next) {
        return head;
    }
    
    // Chia danh sách thành 2 nửa
    Node* mid = split(head);
    
    // Đệ quy sắp xếp từng nửa
    Node* left = mergeSort(head);
    Node* right = mergeSort(mid);
    
    // Trộn 2 nửa đã sắp xếp
    return merge(left, right);
}

// =========================== HÀM CHÍNH ===========================
int main() {
    Node* head = nullptr;
    int value;
    
    cout << "Nhập các số nguyên (nhập -1 để kết thúc):" << endl;
    
    while (cin >> value && value != -1) {
        append(head, value);
    }
    
    cout << "\nDanh sách ban đầu: " << endl;
    displayList(head);
    
    // Sắp xếp
    head = mergeSort(head);
    
    cout << "Danh sách sau khi sắp xếp (tăng dần): " << endl;
    displayList(head);
    
    // Giải phóng bộ nhớ
    freeList(head);
    
    return 0;
}