#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

const int MAX_ITEM = 10;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

struct ItemPesanan {
    char namaPesanan[50];
    int harga;
};

//Node untuk linked list  antrian (pointer)
struct NodeAntrian {
    int nomorAntrian;
    char namaCustomer[50];
    ItemPesanan daftarPesan[MAX_ITEM];
    int jumlahItem;
    int totalHarga;
    NodeAntrian* next;
};

//Node untuk linked list riwayat selesai
struct NodeRiwayat {
    int nomorAntrian;
    char namaCustomer[50];
    ItemPesanan daftarPesan[MAX_ITEM];
    int jumlahItem;
    int totalHarga;
    NodeRiwayat* next;
};

const int JUMLAH_MENU = 8;
ItemPesanan daftarMenu[JUMLAH_MENU] ={
    {"Caramel Latte", 16000},
    {"Americano", 18000},
    {"Matcha Latte", 20000},
    {"Iced Chocolate",15000},
    {"Thai Tea", 15000},
    {"Croissant", 18000},
    {"Toast Strawberry", 16000},
    {"Churros", 15000}
};

NodeAntrian* headAntrian = NULL;
NodeAntrian* tailAntrian = NULL;
NodeRiwayat* headRiwayat = NULL;
int counterAntrian = 0;

void cetakGaris(){
    cout << "==============================================" << endl;
}

void cetakGaris2(){
    cout << "----------------------------------------------" << endl;
}

void cetakJudul(const char* judul){
    cetakGaris2();
    cout << setw(10) << " "  << judul << " " << endl;
    cetakGaris2();
}

void tampilMenuCafe(){
	cetakGaris2();
	cout << setw(8) << " " << "★★★★★ DAFTAR MENU CAFE ★★★★★" << endl;
	cetakGaris2();
    cout << left << setw(5)  << "| No." << setw(22) << "| Menu" << "| Harga" << setw(11) << left << " " <<  "|" << endl;
    cetakGaris2();
    
    for (int i = 0; i<JUMLAH_MENU; i++) {
		cout << "| " << left << setw(3) << i + 1 << "| " << setw(20) << daftarMenu[i].namaPesanan << "| Rp " << daftarMenu[i].harga << setw(8) << left << " " <<  "|" << endl;
    }
    cetakGaris2();
}

void tampilRingkasanPesanan(const char* nama, ItemPesanan items[], int jumlah, int total){
    cetakGaris2();
    cout << setw(10) << " "  << "★ RINGKASAN PESANAN ★" << " " << endl;
	cetakGaris2();
    cout << " " << setw(5) << "Nama Customer : " << nama << endl;
    cetakGaris2();
    cout << left << setw(5)  << "| No." << setw(22) << "| Menu" << "| Harga" << setw(11) << left << " " <<  "|" << endl;
    cetakGaris2();
    for (int i = 0; i < jumlah; i++){
        cout << "| "  << left << setw(3)  << i + 1 << "| "<< setw(20) << items[i].namaPesanan << "| Rp " << items[i].harga << setw(8) << left << " " <<  "|" << endl;
    }
    cetakGaris2();
    cout << right << setw(26) << "Total : Rp " << total << endl;
    cetakGaris2();
}