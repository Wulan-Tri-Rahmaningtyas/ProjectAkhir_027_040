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

void simpanRiwayatKeFile(NodeRiwayat* node){
    FILE* pf = fopen("riwayat_antrian.txt", "a");
    if (pf == NULL){
		SetConsoleTextAttribute(hConsole, 4);
        cout << "Gagal menyimpan ke file!!" << endl;
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }
    fprintf(pf, "%d\n", node->nomorAntrian);
    fprintf(pf, "%s\n", node->namaCustomer);
    fprintf(pf, "%d\n", node->jumlahItem);
    for (int i = 0; i < node->jumlahItem; i++){
        fprintf(pf, "%s\n", node->daftarPesan[i].namaPesanan);
        fprintf(pf, "%d\n", node->daftarPesan[i].harga);
    }
    fprintf(pf, "%d\n", node->totalHarga);
    fclose(pf);
}

int bacaRiwayatDariFile(NodeRiwayat* arrayRiwayat[], int maxData){
    FILE* pf = fopen("riwayat_antrian.txt", "r");
    if (pf == NULL)
    return 0;

    int n = 0;
    while (n < maxData){
        NodeRiwayat* node = new NodeRiwayat;
        node->next = NULL;

        if (fscanf(pf, "%d\n", &node->nomorAntrian) != 1){
            delete node;
            break;
        }
        if (fgets(node->namaCustomer, 50, pf) == NULL){
			delete node;
			break;
		}
        int k = 0;
        while (node->namaCustomer[k] != '\0'){
            if (node->namaCustomer[k] == '\n'){ 
				node->namaCustomer[k] = '\0';
				break;
			}
            k++;
        }
        if (fscanf(pf, "%d\n", &node->jumlahItem) != 1){
			delete node;
			break;
		}

        bool gagal = false;
        for (int i = 0; i < node->jumlahItem; i++){
            if (fgets(node->daftarPesan[i].namaPesanan, 50, pf) == NULL){
				gagal = true;
				break;
			}
            k = 0;
            while (node->daftarPesan[i].namaPesanan[k] != '\0'){
                if (node->daftarPesan[i].namaPesanan[k] == '\n'){
                    node->daftarPesan[i].namaPesanan[k] = '\0';
                    break;
                }
                k++;
            }
            if (fscanf(pf, "%d\n", &node->daftarPesan[i].harga) != 1) {
				gagal = true; break;
			}
        }
        if (gagal){
			delete node;
			break;
		}
        if (fscanf(pf, "%d\n", &node->totalHarga) != 1){ 
			delete node;
			break;
		}
        arrayRiwayat[n] = node;
        n++;
    }
    fclose(pf);
    return n;
}

// Sorting BUBBLE SORT
void bubbleSortRiwayat(NodeRiwayat* arr[], int n, bool ascending){
    NodeRiwayat* temp;
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - 1 - i; j++){
            bool tukar = false;
            if ( ascending && arr[j]->nomorAntrian > arr[j+1]->nomorAntrian) tukar = true;
            if (!ascending && arr[j]->nomorAntrian < arr[j+1]->nomorAntrian) tukar = true;
            if (tukar){
                temp	= arr[j];
                arr[j]	= arr[j+1];
                arr[j+1]= temp;
            }
        }
    }
}

//Searching SEQUENTIAL SEARCH
NodeAntrian* sequentialSearch(const char* namaCari){
    NodeAntrian* bantu = headAntrian;
    while (bantu != NULL){
        bool cocok = true;
        int i = 0;
        while (namaCari[i] != '\0' || bantu->namaCustomer[i] != '\0'){
            if (bantu->namaCustomer[i] != namaCari[i]){
                cocok = false;
                break;
            }
            i++;
        }
        if (cocok) return bantu;
        bantu = bantu->next;
    }
    return NULL;
}

//Linked list ANTRIAN
// sisipBelakang = tambah node di akhir linked list
// hapusDepan = hapus node di awal linked list

void sisipBelakang(const char* nama, ItemPesanan items[], int jumlah, int total){
    NodeAntrian* nodeBaru = new NodeAntrian; //memindahkan node baru pakai pointer

    counterAntrian++;
    nodeBaru->nomorAntrian = counterAntrian;
    nodeBaru->jumlahItem   = jumlah;
    nodeBaru->totalHarga   = total;
    nodeBaru->next         = NULL;

    //nyalin karakter
    int i = 0;
    while (nama[i] != '\0'){
        nodeBaru->namaCustomer[i] = nama[i];
        i++;
    }
    nodeBaru->namaCustomer[i] = '\0';

    for (int j = 0; j < jumlah; j++){
        nodeBaru->daftarPesan[j] = items[j];
    }

    // sisip di belakang: klo list kosong, head & tail = node baru
    // kalo ga kosong, sambungin tail lama ke node baru, lalu geser tail
    if (headAntrian == NULL){
        headAntrian = nodeBaru; //head = orang paling depan
        tailAntrian = nodeBaru; //tail = orang paling belakang
    }
    else{
        tailAntrian->next = nodeBaru;
        tailAntrian = nodeBaru;
    }
    cout << "\n★★ Antrian berhasil ditambahkan!" << endl;
    cout << "Nomor Antrian : " << nodeBaru->nomorAntrian << endl;
    cout << "Nama          : " << nodeBaru->namaCustomer << endl;
    cout << "Jumlah Item   : " << nodeBaru->jumlahItem << " item" << endl;
    cout << "Total Harga   : Rp " << nodeBaru->totalHarga << endl;
}
