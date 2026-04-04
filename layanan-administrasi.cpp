#include <iostream>

using namespace std;

struct DataLayanan {
    string namaMahasiswa;
    string jenisLayanan;
    string statusLayanan;
};

struct NodeQueue {
    DataLayanan data;
    NodeQueue* next;

    NodeQueue(DataLayanan d) {
        data = d;
        next = nullptr;
    }
};

struct NodeStack {
    DataLayanan data;
    NodeStack* next;

    NodeStack(DataLayanan d) {
        data = d;
        next = nullptr;
    }
};

// Queue berbasis linked list
class QueueLayanan {
private:
    NodeQueue* front;
    NodeQueue* rear;
    int jumlah;

public:
    QueueLayanan() {
        front = nullptr;
        rear = nullptr;
        jumlah = 0;
    }

    void enqueue(DataLayanan data) {
        NodeQueue* nodeBaru = new NodeQueue(data);
        if (rear == nullptr) {
            front = rear = nodeBaru;
        } else {
            rear->next = nodeBaru;
            rear = nodeBaru;
        }
        jumlah++;
    }

    DataLayanan dequeue() {
        if (front == nullptr) {
            DataLayanan kosong = {"", "", ""};
            return kosong;
        }
        NodeQueue* temp = front;
        DataLayanan data = temp->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        jumlah--;
        return data;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    DataLayanan peek() {
        if (front == nullptr) {
            DataLayanan kosong = {"", "", ""};
            return kosong;
        }
        return front->data;
    }

    void tampilkanAntrean() {
        cout << "\n---------------- DAFTAR ANTREAN ----------------\n";
        if (isEmpty()) {
            cout << "[INFO] Antrean kosong.\n";
            return;
        }

        NodeQueue* current = front;
        int nomor = 1;
        while (current != nullptr) {
            cout << nomor << ". " << current->data.namaMahasiswa
                 << " | " << current->data.jenisLayanan
                 << " | " << current->data.statusLayanan << "\n";
            current = current->next;
            nomor++;
        }
        cout << "Total antrean: " << jumlah << "\n";
    }
};

// Stack berbasis linked list
class StackRiwayat {
private:
    NodeStack* topNode;
    int jumlah;

public:
    StackRiwayat() {
        topNode = nullptr;
        jumlah = 0;
    }

    void push(DataLayanan data) {
        NodeStack* nodeBaru = new NodeStack(data);
        nodeBaru->next = topNode;
        topNode = nodeBaru;
        jumlah++;
    }

    DataLayanan pop() {
        if (topNode == nullptr) {
            DataLayanan kosong = {"", "", ""};
            return kosong;
        }
        NodeStack* temp = topNode;
        DataLayanan data = temp->data;
        topNode = topNode->next;
        delete temp;
        jumlah--;
        return data;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }

    DataLayanan peek() {
        if (topNode == nullptr) {
            DataLayanan kosong = {"", "", ""};
            return kosong;
        }
        return topNode->data;
    }

    void tampilkanRiwayat() {
        cout << "\n---------------- RIWAYAT LAYANAN ----------------\n";
        if (isEmpty()) {
            cout << "[INFO] Riwayat kosong.\n";
            return;
        }

        NodeStack* current = topNode;
        int nomor = 1;
        while (current != nullptr) {
            cout << nomor << ". " << current->data.namaMahasiswa
                 << " | " << current->data.jenisLayanan
                 << " | " << current->data.statusLayanan << "\n";
            current = current->next;
            nomor++;
        }
        cout << "Total riwayat: " << jumlah << "\n";
    }
};

// Forward declarations
string inputTidakBolehKosong(const string &pesan);
string pilihJenisLayanan();
void prosesLayanan(QueueLayanan& antrean, StackRiwayat& riwayat);
void tampilkanLayananTerakhir(StackRiwayat& riwayat);
void tampilkanAntreanTerdepan(QueueLayanan& antrean);

// FUNGSI OPSI LAYANAN
void tambahAntrean(QueueLayanan& antrean) {
    cout << "\n---------------- TAMBAH ANTREAN ----------------\n";

    cin.ignore();
    string nama = inputTidakBolehKosong("Masukkan nama mahasiswa : ");
    string jenis = pilihJenisLayanan();

    DataLayanan dataBaru;
    dataBaru.namaMahasiswa = nama;
    dataBaru.jenisLayanan = jenis;
    dataBaru.statusLayanan = "Menunggu";

    // antrean.enqueue(dataBaru);
    antrean.enqueue(dataBaru);

    cout << "\n[SUKSES] Mahasiswa berhasil ditambahkan ke antrean.\n";
    cout << "Nama   : " << dataBaru.namaMahasiswa << "\n";
    cout << "Layanan: " << dataBaru.jenisLayanan << "\n";
    cout << "Status : " << dataBaru.statusLayanan << "\n";
}

string pilihJenisLayanan() {
    int pilih;
    while (true) {
        cout << "\nPilih Jenis Layanan:\n";
        cout << "1. Legalisir\n";
        cout << "2. Surat Aktif Kuliah\n";
        cout << "3. Verifikasi Dokumen\n";
        cout << "4. Pengambilan Berkas\n";
        cout << "5. Lainnya\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: return "Legalisir";
            case 2: return "Surat Aktif";
            case 3: return "Verifikasi";
            case 4: return "Ambil Berkas";
            case 5:
                cin.ignore();
                return inputTidakBolehKosong("Masukkan jenis layanan: ");
            default:
                cout << "[PERINGATAN] Pilihan tidak valid.\n";
        }
    }
}

string inputTidakBolehKosong(const string &pesan){
    string input;
    do {
        cout << pesan;
        getline(cin, input);

        if (input.empty()) {
            cout << "Input tidak boleh kosong! Silakan isi lagi.\n";
        }
    } while (input.empty());

    return input;
}



// MENU PROGRAM
void garis() {
    cout << "===============================================================\n";
}

void judulProgram() {
    garis();
    cout << "         SISTEM ANTREAN LAYANAN ADMINISTRASI AKADEMIK          \n";
    garis();
    cout << " Queue : Antrean mahasiswa yang menunggu layanan\n";
    cout << " Stack : Riwayat layanan yang telah selesai diproses\n";
    garis();
}

void tampilkanMenu() {
    cout << "\nMENU UTAMA\n";
    cout << "1. Tambah mahasiswa ke antrean\n";
    cout << "2. Proses layanan berikutnya\n";
    cout << "3. Tampilkan layanan terakhir yang diproses\n";
    cout << "4. Tampilkan antrean layanan\n";
    cout << "5. Tampilkan riwayat layanan\n";
    cout << "6. Tampilkan mahasiswa terdepan antrean\n";
    cout << "0. Keluar\n";
    garis();
    cout << "Pilih menu: ";
}

void tekanEnter(){
    cout << "\nTekan ENTER untuk kembali ke menu...";
    cin.get();
    cin.get();
}

void prosesLayanan(QueueLayanan& antrean, StackRiwayat& riwayat) {
    cout << "\n---------------- PROSES LAYANAN ----------------\n";
    if (antrean.isEmpty()) {
        cout << "[INFO] Tidak ada antrean untuk diproses.\n";
        return;
    }

    DataLayanan data = antrean.dequeue();
    data.statusLayanan = "Selesai";
    riwayat.push(data);

    cout << "[SUKSES] Layanan berhasil diproses.\n";
    cout << "Nama   : " << data.namaMahasiswa << "\n";
    cout << "Layanan: " << data.jenisLayanan << "\n";
    cout << "Status : " << data.statusLayanan << "\n";
}

void tampilkanLayananTerakhir(StackRiwayat& riwayat) {
    cout << "\n---------------- LAYANAN TERAKHIR ----------------\n";
    if (riwayat.isEmpty()) {
        cout << "[INFO] Belum ada layanan yang diproses.\n";
        return;
    }

    DataLayanan data = riwayat.peek();
    cout << "Nama   : " << data.namaMahasiswa << "\n";
    cout << "Layanan: " << data.jenisLayanan << "\n";
    cout << "Status : " << data.statusLayanan << "\n";
}

void tampilkanAntreanTerdepan(QueueLayanan& antrean) {
    cout << "\n---------------- ANTREAN TERDEPAN ----------------\n";
    if (antrean.isEmpty()) {
        cout << "[INFO] Tidak ada antrean.\n";
        return;
    }

    DataLayanan data = antrean.peek();
    cout << "Nama   : " << data.namaMahasiswa << "\n";
    cout << "Layanan: " << data.jenisLayanan << "\n";
    cout << "Status : " << data.statusLayanan << "\n";
}

int main() {
    QueueLayanan antrean;
    StackRiwayat riwayat;

    int pilihan;

    do {
        judulProgram();
        tampilkanMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahAntrean(antrean);
                tekanEnter();
                break;
            case 2:
                prosesLayanan(antrean, riwayat);
                tekanEnter();
                break;
            case 3:
                tampilkanLayananTerakhir(riwayat);
                tekanEnter();
                break;
            case 4:
                antrean.tampilkanAntrean();
                tekanEnter();
                break;
            case 5:
                riwayat.tampilkanRiwayat();
                tekanEnter();
                break;
            case 6:
                tampilkanAntreanTerdepan(antrean);
                tekanEnter();
                break;
            case 0:
                cout << "\nTerima kasih. Program selesai.\n";
                break;
            default:
                cout << "\nInputan tidak valid! Silahkan coba ulang.\n";
                tekanEnter();
                break;
        }

        cout << "\n\n";
    } while (pilihan != 0);

    return 0;
}
