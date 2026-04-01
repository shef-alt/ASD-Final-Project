// ======================================================
//  SISTEM ANTREAN LAYANAN ADMINISTRASI AKADEMIK - GUI
//  Queue  : menyimpan mahasiswa yang menunggu layanan
//  Stack  : menyimpan riwayat layanan yang telah selesai
//  GUI Framework: wxWidgets
// ======================================================

#include <wx/wx.h>
#include <wx/textdlg.h>
#include <string>
#include <sstream>

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

    string getAntreanText() {
        stringstream ss;
        ss << "---------------- DAFTAR ANTREAN ----------------\n";
        if (isEmpty()) {
            ss << "[INFO] Antrean kosong.\n";
            return ss.str();
        }

        NodeQueue* current = front;
        int nomor = 1;
        while (current != nullptr) {
            ss << nomor << ". " << current->data.namaMahasiswa
               << " | " << current->data.jenisLayanan
               << " | " << current->data.statusLayanan << "\n";
            current = current->next;
            nomor++;
        }
        ss << "Total antrean: " << jumlah << "\n";
        return ss.str();
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
        return topNode->data;sudo apt install libwxgtk3.0-gtk3-dev
    }

    string getRiwayatText() {
        stringstream ss;
        ss << "---------------- RIWAYAT LAYANAN ----------------\n";
        if (isEmpty()) {
            ss << "[INFO] Riwayat kosong.\n";
            return ss.str();
        }

        NodeStack* current = topNode;
        int nomor = 1;
        while (current != nullptr) {
            ss << nomor << ". " << current->data.namaMahasiswa
               << " | " << current->data.jenisLayanan
               << " | " << current->data.statusLayanan << "\n";
            current = current->next;
            nomor++;
        }
        ss << "Total riwayat: " << jumlah << "\n";
        return ss.str();
    }
};

// Main Frame
class MainFrame : public wxFrame {
private:
    QueueLayanan antrean;
    StackRiwayat riwayat;
    wxTextCtrl* outputText;

public:
    MainFrame() : wxFrame(nullptr, wxID_ANY, "Sistem Antrean Layanan Administrasi Akademik", wxDefaultPosition, wxSize(800, 600)) {

        wxPanel* panel = new wxPanel(this);
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        // Title
        wxStaticText* title = new wxStaticText(panel, wxID_ANY, "SISTEM ANTREAN LAYANAN ADMINISTRASI AKADEMIK");
        wxFont titleFont = title->GetFont();
        titleFont.SetPointSize(14);
        titleFont.SetWeight(wxFONTWEIGHT_BOLD);
        title->SetFont(titleFont);
        mainSizer->Add(title, 0, wxALL | wxCENTER, 10);

        // Buttons
        wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

        wxButton* btnTambah = new wxButton(panel, wxID_ANY, "Tambah Antrean");
        wxButton* btnProses = new wxButton(panel, wxID_ANY, "Proses Layanan");
        wxButton* btnTerakhir = new wxButton(panel, wxID_ANY, "Layanan Terakhir");
        wxButton* btnAntrean = new wxButton(panel, wxID_ANY, "Lihat Antrean");
        wxButton* btnRiwayat = new wxButton(panel, wxID_ANY, "Lihat Riwayat");
        wxButton* btnTerdepan = new wxButton(panel, wxID_ANY, "Antrean Terdepan");

        buttonSizer->Add(btnTambah, 0, wxALL, 5);
        buttonSizer->Add(btnProses, 0, wxALL, 5);
        buttonSizer->Add(btnTerakhir, 0, wxALL, 5);

        mainSizer->Add(buttonSizer, 0, wxCENTER);

        wxBoxSizer* buttonSizer2 = new wxBoxSizer(wxHORIZONTAL);
        buttonSizer2->Add(btnAntrean, 0, wxALL, 5);
        buttonSizer2->Add(btnRiwayat, 0, wxALL, 5);
        buttonSizer2->Add(btnTerdepan, 0, wxALL, 5);

        mainSizer->Add(buttonSizer2, 0, wxCENTER);

        // Output text area
        outputText = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                                    wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH);
        wxFont monoFont(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
        outputText->SetFont(monoFont);
        mainSizer->Add(outputText, 1, wxALL | wxEXPAND, 10);

        panel->SetSizer(mainSizer);

        // Event bindings
        btnTambah->Bind(wxEVT_BUTTON, &MainFrame::OnTambahAntrean, this);
        btnProses->Bind(wxEVT_BUTTON, &MainFrame::OnProsesLayanan, this);
        btnTerakhir->Bind(wxEVT_BUTTON, &MainFrame::OnLayananTerakhir, this);
        btnAntrean->Bind(wxEVT_BUTTON, &MainFrame::OnLihatAntrean, this);
        btnRiwayat->Bind(wxEVT_BUTTON, &MainFrame::OnLihatRiwayat, this);
        btnTerdepan->Bind(wxEVT_BUTTON, &MainFrame::OnAntreanTerdepan, this);

        outputText->SetValue("Selamat datang di Sistem Antrean Layanan Administrasi Akademik\n\nSilakan pilih menu di atas.");
    }

    void OnTambahAntrean(wxCommandEvent& event) {
        wxTextEntryDialog namaDialog(this, "Masukkan nama mahasiswa:", "Tambah Antrean");
        if (namaDialog.ShowModal() == wxID_CANCEL) return;

        string nama = string(namaDialog.GetValue().mb_str());
        if (nama.empty()) {
            wxMessageBox("Nama tidak boleh kosong!", "Error", wxICON_ERROR);
            return;
        }

        const wxString choices[] = {"Legalisir", "Surat Aktif Kuliah", "Verifikasi Dokumen",
                                    "Pengambilan Berkas", "Lainnya"};
        wxSingleChoiceDialog jenisDialog(this, "Pilih jenis layanan:", "Jenis Layanan",
                                         5, choices);

        if (jenisDialog.ShowModal() == wxID_CANCEL) return;

        string jenis;
        int selection = jenisDialog.GetSelection();

        if (selection == 4) {
            wxTextEntryDialog customDialog(this, "Masukkan jenis layanan:", "Jenis Layanan Lainnya");
            if (customDialog.ShowModal() == wxID_CANCEL) return;
            jenis = string(customDialog.GetValue().mb_str());
        } else {
            jenis = string(choices[selection].mb_str());
        }

        DataLayanan dataBaru;
        dataBaru.namaMahasiswa = nama;
        dataBaru.jenisLayanan = jenis;
        dataBaru.statusLayanan = "Menunggu";

        antrean.enqueue(dataBaru);

        stringstream ss;
        ss << "---------------- TAMBAH ANTREAN ----------------\n";
        ss << "[SUKSES] Mahasiswa berhasil ditambahkan ke antrean.\n";
        ss << "Nama   : " << dataBaru.namaMahasiswa << "\n";
        ss << "Layanan: " << dataBaru.jenisLayanan << "\n";
        ss << "Status : " << dataBaru.statusLayanan << "\n";

        outputText->SetValue(ss.str());
    }

    void OnProsesLayanan(wxCommandEvent& event) {
        stringstream ss;
        ss << "---------------- PROSES LAYANAN ----------------\n";

        if (antrean.isEmpty()) {
            ss << "[INFO] Tidak ada antrean untuk diproses.\n";
            outputText->SetValue(ss.str());
            return;
        }

        DataLayanan data = antrean.dequeue();
        data.statusLayanan = "Selesai";
        riwayat.push(data);

        ss << "[SUKSES] Layanan berhasil diproses.\n";
        ss << "Nama   : " << data.namaMahasiswa << "\n";
        ss << "Layanan: " << data.jenisLayanan << "\n";
        ss << "Status : " << data.statusLayanan << "\n";

        outputText->SetValue(ss.str());
    }

    void OnLayananTerakhir(wxCommandEvent& event) {
        stringstream ss;
        ss << "---------------- LAYANAN TERAKHIR ----------------\n";

        if (riwayat.isEmpty()) {
            ss << "[INFO] Belum ada layanan yang diproses.\n";
            outputText->SetValue(ss.str());
            return;
        }

        DataLayanan data = riwayat.peek();
        ss << "Nama   : " << data.namaMahasiswa << "\n";
        ss << "Layanan: " << data.jenisLayanan << "\n";
        ss << "Status : " << data.statusLayanan << "\n";

        outputText->SetValue(ss.str());
    }

    void OnLihatAntrean(wxCommandEvent& event) {
        outputText->SetValue(antrean.getAntreanText());
    }

    void OnLihatRiwayat(wxCommandEvent& event) {
        outputText->SetValue(riwayat.getRiwayatText());
    }

    void OnAntreanTerdepan(wxCommandEvent& event) {
        stringstream ss;
        ss << "---------------- ANTREAN TERDEPAN ----------------\n";

        if (antrean.isEmpty()) {
            ss << "[INFO] Tidak ada antrean.\n";
            outputText->SetValue(ss.str());
            return;
        }

        DataLayanan data = antrean.peek();
        ss << "Nama   : " << data.namaMahasiswa << "\n";
        ss << "Layanan: " << data.jenisLayanan << "\n";
        ss << "Status : " << data.statusLayanan << "\n";

        outputText->SetValue(ss.str());
    }
};

// Application class
class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        MainFrame* frame = new MainFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
