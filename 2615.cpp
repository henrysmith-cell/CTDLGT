#include <iostream>

using namespace std;

#define MaxLength 100
typedef int ElementType;
typedef int Position;

// Cấu trúc danh sách (Linear List dạng mảng)
typedef struct
{
    ElementType Elements[MaxLength];
    Position Last;
} List;

// ==========================================
// CÁC HÀM CƠ BẢN
// ==========================================

void makeNullList(List *L)
{
    L->Last = 0;
}

int emptyList(List L)
{
    return L.Last == 0;
}

Position first(List L)
{
    return 1;
}

Position endList(List L)
{
    return L.Last + 1;
}

Position next(Position p, List L)
{
    return p + 1;
}

ElementType retrieve(Position p, List L)
{
    return L.Elements[p - 1];
}

void insertList(ElementType x, Position p, List *L)
{
    if (L->Last == MaxLength)
    {
        cout << "Danh sach day\n";
    }
    else if (p < 1 || p > L->Last + 1)
    {
        cout << "Vi tri khong hop le\n";
    }
    else
    {
        Position q;
        for (q = L->Last; q >= p; q--)
        {
            L->Elements[q] = L->Elements[q - 1];
        }
        L->Elements[p - 1] = x;
        L->Last++;
    }
}

// ==========================================
// HÀM SẮP XẾP (Sử dụng Insertion Sort)
// ==========================================

void selectionSort(List *L)
{
    for (Position p = first(*L); p != endList(*L); p = next(p, *L))
    {
        Position minPos = p;
        for (Position q = next(p, *L); q != endList(*L); q = next(q, *L))
        {
            if (retrieve(q, *L) < retrieve(minPos, *L))
            {
                minPos = q;
            }
        }
        // Hoán đổi
        ElementType x = retrieve(p, *L);
        ElementType y = retrieve(minPos, *L);
        L->Elements[p - 1] = y;
        L->Elements[minPos - 1] = x;
    }
}

// ==========================================
// HÀM TRỘN HAI DANH SÁCH ĐÃ SẮP XẾP
// ==========================================

void mergeLists(List L1, List L2, List *L3)
{
    makeNullList(L3);
    
    Position p1 = first(L1);
    Position p2 = first(L2);
    
    // Trộn theo phương pháp trộn (merge) - giống Merge Sort
    while (p1 != endList(L1) && p2 != endList(L2))
    {
        ElementType x1 = retrieve(p1, L1);
        ElementType x2 = retrieve(p2, L2);
        
        if (x1 <= x2)
        {
            insertList(x1, endList(*L3), L3);
            p1 = next(p1, L1);
        }
        else
        {
            insertList(x2, endList(*L3), L3);
            p2 = next(p2, L2);
        }
    }
    
    // Chèn các phần tử còn lại của L1 (nếu có)
    while (p1 != endList(L1))
    {
        insertList(retrieve(p1, L1), endList(*L3), L3);
        p1 = next(p1, L1);
    }
    
    // Chèn các phần tử còn lại của L2 (nếu có)
    while (p2 != endList(L2))
    {
        insertList(retrieve(p2, L2), endList(*L3), L3);
        p2 = next(p2, L2);
    }
}

// ==========================================
// HÀM NHẬP VÀ IN DANH SÁCH
// ==========================================

void nhapDanhSach(List *L, const char *ten)
{
    int n;
    cout << "Nhap so luong phan tu cua " << ten << ": ";
    cin >> n;
    
    makeNullList(L);
    
    for (int i = 0; i < n; i++)
    {
        ElementType value;
        cout << "  Phan tu thu " << i + 1 << ": ";
        cin >> value;
        insertList(value, endList(*L), L);
    }
}

void inDanhSach(List L, const char *ten)
{
    if (emptyList(L))
    {
        cout << ten << " rong\n";
        return;
    }
    
    cout << ten << ": ";
    for (Position p = first(L); p != endList(L); p = next(p, L))
    {
        cout << retrieve(p, L) << " ";
    }
    cout << endl;
}

// ==========================================
// HÀM CHÍNH
// ==========================================

int main()
{
    List L1, L2, L3;
    
    cout << "===========================================\n";
    cout << "    TRON HAI DANH SACH L1 VA L2 THANH L3\n";
    cout << "         (sap xep tang dan)\n";
    cout << "===========================================\n\n";
    
    // Nhập danh sách L1
    nhapDanhSach(&L1, "L1");
    
    // Nhập danh sách L2
    nhapDanhSach(&L2, "L2");
    
    // In danh sách trước khi sắp xếp
    cout << "\n--- Truoc khi sap xep ---\n";
    inDanhSach(L1, "L1");
    inDanhSach(L2, "L2");
    
    // Sắp xếp L1 và L2 tăng dần
    cout << "\n--- Sap xep L1 va L2 tang dan ---\n";
    selectionSort(&L1);
    selectionSort(&L2);
    inDanhSach(L1, "L1 (da sap xep)");
    inDanhSach(L2, "L2 (da sap xep)");
    
    // Trộn L1 và L2 thành L3
    cout << "\n--- Tron L1 va L2 thanh L3 ---\n";
    mergeLists(L1, L2, &L3);
    inDanhSach(L3, "L3 (da tron - tang dan)");
    
    cout << "\n===========================================\n";
    cout << "So phan tu L1: " << L1.Last << endl;
    cout << "So phan tu L2: " << L2.Last << endl;
    cout << "So phan tu L3: " << L3.Last << endl;
    cout << "===========================================\n";
    
    return 0;
}