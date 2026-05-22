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
