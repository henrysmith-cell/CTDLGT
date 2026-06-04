#include <iostream>

using namespace std;

#define MaxLength 100
typedef int ElementType;
typedef int Position;

// Cấu trúc danh sách đặc chuẩn giáo trình
typedef struct {
    ElementType Elements[MaxLength];
    Position Last;
} List;

// --- CÁC PHÉP TOÁN NỀN TẢNG ---
void makeNullList(List *L) { L->Last = 0; }
int emptyList(List L) { return L.Last == 0; }
Position first(List L) { return 1; }
Position endList(List L) { return L.Last + 1; }
Position next(Position p, List L) { return p + 1; }
ElementType retrieve(Position p, List L) { return L.Elements[p - 1]; }

void insertList(ElementType x, Position p, List *L) {
    if (L->Last == MaxLength) {
        cout << "Danh sach day\n";
    } else if (p < 1 || p > L->Last + 1) {
        cout << "Vi tri khong hop le\n";
    } else {
        Position q;
        for (q = L->Last; q >= p; q--) {
            L->Elements[q] = L->Elements[q - 1];
        }
        L->Elements[p - 1] = x;
        L->Last++;
    }
}

// Kiểm tra số nguyên tố
int laNguyenTo(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Tìm số chính phương nhỏ nhất lớn hơn n (không dùng cmath)
int chinhPhuongTiepTheo(int n) {
    int i = 1;
    while (i * i <= n) {
        i++;
    }
    return i * i;
}

// --- CÁC HÀM XỬ LÝ THEO ĐỀ BÀI ---

// Câu a: Tính tổng giá trị của các nút
long long tinhTong(List L) {
    long long tong = 0;
    for (Position p = first(L); p != endList(L); p = next(p, L)) {
        tong += retrieve(p, L);
    }
    return tong;
}

// Câu b: Đếm số nút chẵn và lẻ
void demChanLe(List L, int &soChan, int &soLe) {
    soChan = 0; 
    soLe = 0;
    for (Position p = first(L); p != endList(L); p = next(p, L)) {
        if (retrieve(p, L) % 2 == 0) soChan++;
        else soLe++;
    }
}

// Câu c: Tìm số nguyên tố lớn nhất
int nguyenToMax(List L) {
    int max_nt = -1;
    for (Position p = first(L); p != endList(L); p = next(p, L)) {
        ElementType x = retrieve(p, L);
        if (laNguyenTo(x)) {
            if (max_nt == -1 || x > max_nt) {
                max_nt = x;
            }
        }
    }
    return max_nt;
}

// Câu d: Tạo danh sách L1 chỉ chứa các số nguyên tố từ L
void taoDanhSachL1(List L, List *L1) {
    makeNullList(L1);
    for (Position p = first(L); p != endList(L); p = next(p, L)) {
        ElementType x = retrieve(p, L);
        if (laNguyenTo(x)) {
            insertList(x, endList(*L1), L1);
        }
    }
}

// Câu e: Chèn số chính phương nhỏ nhất lớn hơn vào sau số nguyên tố
void chenChinhPhuongSauNguyenTo(List *L) {
    Position p = first(*L);
    while (p != endList(*L)) {
        ElementType x = retrieve(p, *L);
        if (laNguyenTo(x)) {
            int canChen = chinhPhuongTiepTheo(x);
            insertList(canChen, p + 1, L);
            p = next(p, *L);
            p = next(p, *L); // Bỏ qua phần tử vừa chèn để tránh lặp vô hạn
        } else {
            p = next(p, *L);
        }
    }
}

Position timViTri(ElementType x, List L) {
    for (Position p = first(L); p != endList(L); p = next(p, L)) {
        if (retrieve(p, L) == x) return p;
    }
    return 0;
}

void inDanhSach(List L) {
    for (Position p = first(L); p != endList(L); p = next(p, L)) {
        cout << retrieve(p, L) << " ";
    }
    cout << endl;
}

int main() {
    List L, L1;
    makeNullList(&L);

    int n;
    cout << "Nhap so luong phan tu n: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        ElementType value;
        cout << "Nhap phan tu thu " << i + 1 << ": ";
        cin >> value;
        insertList(value, endList(L), &L);
    }

    ElementType x_tim;
    cout << "\nNhap gia tri x can tim vi tri: ";
    cin >> x_tim;

    cout << "\n------ KET QUA ------\n";
    cout << "Vi tri cua x trong danh sach: " << timViTri(x_tim, L) << endl;
    cout << "a. Tong cac nut: " << tinhTong(L) << endl;

    int chan = 0, le = 0;
    demChanLe(L, chan, le);
    cout << "b. So nut chan: " << chan << " | So nut le: " << le << endl;

    int max_nt = nguyenToMax(L);
    if (max_nt != -1) {
        cout << "c. So nguyen to lon nhat: " << max_nt << endl;
    } else {
        cout << "c. Khong co so nguyen to trong danh sach\n";
    }

    taoDanhSachL1(L, &L1);
    cout << "d. Danh sach L1 (so nguyen to): ";
    inDanhSach(L1);

    chenChinhPhuongSauNguyenTo(&L);
    cout << "e. Danh sach sau khi chen so chinh phuong: ";
    inDanhSach(L);

    return 0;
}