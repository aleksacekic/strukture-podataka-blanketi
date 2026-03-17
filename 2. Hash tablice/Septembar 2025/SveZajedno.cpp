#include <cstring>
#include <iostream>
using namespace std;

struct TaxData {
    char adresa[128];
    int brojDanaIzdavanja;
    double iznosTakse;
    
    TaxData() : brojDanaIzdavanja(0), iznosTakse(0.0) {
        adresa[0] = '\0';
    }
    
    TaxData(const char* adr, int dani, double taksa) 
        : brojDanaIzdavanja(dani), iznosTakse(taksa) {
        strncpy(adresa, adr, 127); 
        adresa[127] = '\0';
    }
};


struct ScatterObject {
    char oznaka[17];
    TaxData* podaci;
    int status;
    
    ScatterObject() : podaci(nullptr), status(0) {
        oznaka[0] = '\0';
    }
    
    ScatterObject(const char* ozn, TaxData* data) 
        : podaci(data), status(2) {
        strncpy(oznaka, ozn, 16); 
        oznaka[16] = '\0';
    }
    
    ~ScatterObject() {
    }
    
    bool isEqualKey(const char* key) const {
        return status == 2 && strcmp(oznaka, key) == 0;
    }
};


class OpenScatterTable {
private:
    static const int m = 1048576;  // 2^20
    ScatterObject* t;
    int count;
    
public:
    OpenScatterTable() : count(0) {
        t = new ScatterObject[m];
        for (int i = 0; i < m; i++)
            t[i].status = 0;
    }
    
    ~OpenScatterTable() {
        delete[] t;
    }
    
 
    unsigned int f(const char* key) const {
        unsigned int hash = 0;
        int i = 0;
        while (key[i] != '\0') {
            hash = hash * 31 + (unsigned char)key[i];
            i++;
        }
        return hash;
    }
    

    unsigned int h(const char* key) const {
        return f(key) % (unsigned int)m;
    }
    

    unsigned int c(unsigned int i) const {
        return (i * i + i) / 2;
    }
    
 
    bool insert(ScatterObject obj) {
        if (count >= m) {
            cout << "Tablica je puna" << endl;
            return false;
        }
        
        unsigned int base = h(obj.oznaka);
        int firstDeleted = -1;
        
        for (int i = 0; i < m; i++) {
            int idx = (base + c(i)) % m;
            
            if (t[idx].status == 2) {
                if (strcmp(t[idx].oznaka, obj.oznaka) == 0) {
                    t[idx].podaci = obj.podaci;
                    return true;
                }
                continue;
            }
            
            if (t[idx].status == 1) {
                if (firstDeleted == -1) 
                    firstDeleted = idx;
                continue;
            }
            
            if (firstDeleted != -1) {
                t[firstDeleted] = obj;
                t[firstDeleted].status = 2;
            } else {
                t[idx] = obj;
                t[idx].status = 2;
            }
            count++;
            return true;
        }
        
        if (firstDeleted != -1) {
            t[firstDeleted] = obj;
            t[firstDeleted].status = 2;
            count++;
            return true;
        }
        
        cout << "ablica je puna" << endl;
        return false;
    }
    

    bool insertAccommodation(const char* oznaka, TaxData* podatkeOTaksi) {
        ScatterObject obj(oznaka, podatkeOTaksi);
        return insert(obj);
    }
    

    TaxData* find(const char* oznaka) const {
        unsigned int base = h(oznaka);
        
        for (int i = 0; i < m; i++) {
            int idx = (base + c(i)) % m;
            
            if (t[idx].status == 0)
                return nullptr;
            
            if (t[idx].status == 2 && strcmp(t[idx].oznaka, oznaka) == 0) {
                return t[idx].podaci;
            }
        }
        
        return nullptr;
    }
    

    bool erase(const char* oznaka) {
        unsigned int base = h(oznaka);
        
        for (int i = 0; i < m; i++) {
            int idx = (base + c(i)) % m;
            
            if (t[idx].status == 0)
                return false;
            
            if (t[idx].status == 2 && strcmp(t[idx].oznaka, oznaka) == 0) {
                t[idx].status = 1; 
                t[idx].podaci = nullptr;
                count--;
                return true;
            }
        }
        
        return false;
    }
    
    
};


int main() {
    OpenScatterTable table;
    

    TaxData* t1 = new TaxData("Obala 15, Budva", 120, 5000.0);
    //TaxData* t2 = new TaxData("Primorska 23, Kotor", 90, 3500.0);
    //TaxData* t3 = new TaxData("Jadranska 8, Bar", 150, 6200.0);
    //TaxData* t4 = new TaxData("Centralna 42, Herceg Novi", 60, 2800.0);
    

    
    table.insertAccommodation("1234567801001501", t1); 
    
    
    const char* oznaka1 = "1234567801001501";
    TaxData* found1 = table.find(oznaka1);
    
    
    return 0;
}