#include <cstring>
#include <iostream>
using namespace std;


struct TaxPayment {
    char ime[32];
    char prezime[32];
    char jmbg[14];
    int godina;
    
    TaxPayment() : godina(0) {
        ime[0] = '\0';
        prezime[0] = '\0';
        jmbg[0] = '\0';
    }
    
    TaxPayment(const char* i, const char* p, const char* j, int g) 
        : godina(g) {
        strncpy(ime, i, 31); ime[31] = '\0';
        strncpy(prezime, p, 31); prezime[31] = '\0';
        strncpy(jmbg, j, 13); jmbg[13] = '\0';
    }
};

struct ScatterObject {
    char key[20];       // imamo kompozitni kljuc jmbg-godina
    TaxPayment payment;
    int status;
    
    ScatterObject() : status(0) {
        key[0] = '\0';
    }
    
    ScatterObject(const char* jmbg, int godina, const TaxPayment& p) 
        : payment(p), status(2) {
        snprintf(key, sizeof(key), "%s-%d", jmbg, godina);
    }
    
    bool isEqualKey(const char* k) const { //ovo mozda i nepotrebno
        return status == 2 && strcmp(key, k) == 0;
    }
};

class OpenScatterTable {
private:
    static const int m = 16384;   // 2^14 - u zadatku kaze ~8000 obaveznika
    ScatterObject t[m];
    int count;
    
    int strCmp(const char* a, const char* b) const {
        return strcmp(a, b);
    }
    
public:
    OpenScatterTable() : count(0) {
        for (int i = 0; i < m; i++)
            t[i].status = 0;
    }
    

    unsigned int f(char* key) const {
        unsigned int res = 0;
        int i = 0;
        while (key[i] != '\0') {
            res = res * 31 + (unsigned char)key[i];
            i++;
        }
        return res;
    }
    
    unsigned int h(char* key) const {
        return f(key) % (unsigned int)m;
    }
    
    unsigned int c(unsigned int i) const {
        return (i * i + i) / 2; //moze i samo i*i
    }
    

    void insert(ScatterObject o) {
        if (count >= m) {
            cout << "Tablica je puna" << endl;
            return;
        }
        
        unsigned int base = h(o.key);
        int firstDeleted = -1;
        
        for (int i = 0; i < m; i++) {
            int idx = (base + c(i)) % m;
            
            if (t[idx].status == 2) {
                if (strCmp(t[idx].key, o.key) == 0) {
                    t[idx] = o;  // update
                    return;
                }
                continue;
            }
            
            // tombstone
            if (t[idx].status == 1) {
                if (firstDeleted == -1) 
                    firstDeleted = idx;
                continue;
            }
            
            if (firstDeleted != -1) {
                t[firstDeleted] = o;
            } else {
                t[idx] = o;
            }
            count++;
            return;
        }
        
        if (firstDeleted != -1) {
            t[firstDeleted] = o;
            count++;
            return;
        }
        
        cout << "Tablica je puna" << endl;
    }
    

    bool hasPaid(int year, char* jmbg) const {
        char searchKey[20]; //kompozitni kljuc
        snprintf(searchKey, sizeof(searchKey), "%s-%d", jmbg, year);
        
        unsigned int base = h(searchKey);
        
        for (int i = 0; i < m; i++) {
            int idx = (base + c(i)) % m;
            
            if (t[idx].status == 0)
                return false;
            
            if (t[idx].status == 2 && strCmp(t[idx].key, searchKey) == 0) {
                return true;
            }
            
        }
        
        return false;
    }
    
    int getCount() const {
        return count;
    }
    
    void printStats() const {
        int used = 0, deleted = 0;
        for (int i = 0; i < m; i++) {
            if (t[i].status == 2) used++;
            if (t[i].status == 1) deleted++;
        }
        cout << "Zauzeto: " << used << " / " << m 
             << " (" << (used * 100.0 / m) << "%)" << endl;
        cout << "Obrisano (tombstone): " << deleted << endl;
    }
    
    TaxPayment* getPaymentInfo(int year, char* jmbg) const {
        char searchKey[20];
        snprintf(searchKey, sizeof(searchKey), "%s-%d", jmbg, year);
        
        unsigned int base = h(searchKey);
        
        for (int i = 0; i < m; i++) {
            int idx = (base + c(i)) % m;
            
            if (t[idx].status == 0)
                return nullptr;
            
            if (t[idx].status == 2 && strCmp(t[idx].key, searchKey) == 0) {
                return &(t[idx].payment);
            }
        }
        
        return nullptr;
    }
    
    bool erase(int year, char* jmbg) {
        char searchKey[20];
        snprintf(searchKey, sizeof(searchKey), "%s-%d", jmbg, year);
        
        unsigned int base = h(searchKey);
        
        for (int i = 0; i < m; i++) {
            int idx = (base + c(i)) % m;
            
            if (t[idx].status == 0)
                return false;
            
            if (t[idx].status == 2 && strCmp(t[idx].key, searchKey) == 0) {
                t[idx].status = 1;
                count--;
                return true;
            }
        }
        
        return false;
    }
};

// TESTIRANJE
int main() {
    OpenScatterTable table;
    
    cout << "TEST" << endl << endl;
    
    //test uplate
    TaxPayment p1("Marko", "Markovic", "0101995123456", 2023);
    TaxPayment p2("Ana", "Anic", "1502996234567", 2023);
    TaxPayment p3("Petar", "Petrovic", "2003997345678", 2022);
    TaxPayment p4("Marko", "Markovic", "0101995123456", 2024); //isti jmbg
    
    ScatterObject o1(p1.jmbg, p1.godina, p1);
    ScatterObject o2(p2.jmbg, p2.godina, p2);
    ScatterObject o3(p3.jmbg, p3.godina, p3);
    ScatterObject o4(p4.jmbg, p4.godina, p4);
    
    cout << "Dodavanje uplate poreza" << endl;
    table.insert(o1);
    table.insert(o2);
    table.insert(o3);
    table.insert(o4);
    
    cout << "Dodato uplata: " << table.getCount() << endl << endl;
    table.printStats();
    

    cout << "\n PROVERA " << endl;
    
    char jmbg1[] = "0101995123456";
    if (table.hasPaid(2023, jmbg1)) {
        cout << "Marko Markovic JE PLATIO porez za 2023. godinu" << endl;
    } else {
        cout << "Marko Markovic NIJE platio porez za 2023. godinu" << endl;
    }
    
    if (table.hasPaid(2024, jmbg1)) {
        cout << "Marko Markovic JE PLATIO porez za 2024. godinu" << endl;
    } else {
        cout << "Marko Markovic NIJE platio porez za 2024. godinu" << endl;
    }
    
    if (table.hasPaid(2022, jmbg1)) {
        cout << "Marko Markovic JE PLATIO porez za 2022. godinu" << endl;
    } else {
        cout << "Marko Markovic NIJE platio porez za 2022. godinu" << endl;
    }
    
    char jmbg2[] = "1502996234567";
    if (table.hasPaid(2023, jmbg2)) {
        cout << "Ana Anic JE PLATILA porez za 2023. godinu" << endl;
    } else {
        cout << "Ana Anic NIJE platila porez za 2023. godinu" << endl;
    }
    
    char jmbg3[] = "9999999999999";  // Nepostojeci korisnik
    if (!table.hasPaid(2023, jmbg3)) {
        cout << "Nepoznati korisnik (9999999999999) NIJE platio porez za 2023." << endl;
    }
    
    // Prikaz detalja o uplati
    cout << "\n INFORMACIJE O UPLATI " << endl;
    TaxPayment* found = table.getPaymentInfo(2023, jmbg1);
    if (found) {
        cout << "Pronadjena uplata: " << found->ime << " " << found->prezime 
             << ", JMBG: " << found->jmbg << ", godina: " << found->godina << endl;
    }
    
    return 0;
}