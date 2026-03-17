#include <cstring>
#include <iostream>
#include <cstdint>
using namespace std;


struct Vehicle {
    char registration[10];
    
    Vehicle() {
        registration[0] = '\0';
    }
    
    Vehicle(const char* reg) {
        strncpy(registration, reg, 9);
        registration[9] = '\0';
    }
};


struct ChainedScatterObject {
    char key[10];
    Vehicle vehicle;
    int status;
    int next;
    
    ChainedScatterObject() : status(0), next(-1) {
        key[0] = '\0';
    }
    
    ChainedScatterObject(const char* k, const Vehicle& v) 
        : vehicle(v), status(2), next(-1) {
        strncpy(key, k, 9);
        key[9] = '\0';
    }
    
    bool isEqualKey(const char* k) const {
        return status == 2 && strcmp(key, k) == 0;
    }
};


class ChainedScatterTable {
private:
    ChainedScatterObject* a;
    int m;
    int lrmp;
    int count;
    
public:
    explicit ChainedScatterTable(int vehicles = 1000) : m(vehicles), count(0) {
        a = new ChainedScatterObject[2 * m];
        
        lrmp = m;
        for (int i = m; i < 2*m - 1; ++i) 
            a[i].next = i + 1;
        a[2*m - 1].next = -1;
    }
    
    ~ChainedScatterTable() {
        delete[] a;
    }
    

    static uint32_t f(const char* key) {
        uint32_t hash = 0;
        
        for (int i = 0; key[i] != '\0'; ++i) {
            hash = hash * 31 + (uint8_t)key[i];
        }
        
        return hash;
    }
    
    unsigned int h(ChainedScatterObject o) const {
        return f(o.key) % (uint32_t)m;
    }
    
    unsigned int h(const char* key) const {
        return f(key) % (uint32_t)m;
    }
    
    bool isIn(char* key) const {
        int probe = (int)h(key);
        

        while (probe != -1) {
            if (a[probe].isEqualKey(key)) {
                return true;
            }
            probe = a[probe].next;
        }
        
        return false;
    }
    
    bool insert(const char* registration) {
        Vehicle v(registration);
        ChainedScatterObject obj(registration, v);
        
        uint32_t bucket = h(obj);
        
        if (a[bucket].status != 2) {
            a[bucket] = obj;
            a[bucket].status = 2;
            a[bucket].next = -1;
            ++count;
            return true;
        }
        

        int probe = (int)bucket;
        while (probe != -1) {
            if (a[probe].isEqualKey(registration)) {
                cout << "Vozilo " << registration << " je vec u sistemu!" << endl;
                return false;
            }
            probe = a[probe].next;
        }
        
        int tail = (int)bucket;
        while (a[tail].next != -1) 
            tail = a[tail].next;
        
        if (lrmp == -1) {
            cout << "Nema vise mesta u prostoru za sinonime!" << endl;
            return false;
        }
        
        int newSlot = lrmp;
        lrmp = a[lrmp].next;
        
        a[tail].next = newSlot;
        a[newSlot] = obj;
        a[newSlot].status = 2;
        a[newSlot].next = -1;
        ++count;
        return true;
    }
    

    void deleteVehicle(char* key) {
        int hash = (int)h(key);
        int prev = -1;
        
        while (hash != -1 && a[hash].status == 2 && !a[hash].isEqualKey(key)) {
            prev = hash;
            hash = a[hash].next;
        }
        
        if (hash == -1) {
            cout << "Vozilo " << key << " nije pronadjeno" << endl;
            return;
        }
        
        if (prev != -1) {
            a[prev].next = a[hash].next;
            a[hash].status = 1;
            
            a[hash].next = lrmp;
            lrmp = hash;
        } 
        else {
            if (a[hash].next == -1) {
                a[hash].status = 1;
                a[hash].next = -1;
            } 
            else {
                int sinonim = a[hash].next;
                a[hash] = a[sinonim];
                
 
                a[sinonim].status = 1;
                a[sinonim].next = lrmp;
                lrmp = sinonim;
            }
        }
        
        count--;
        cout << "Vozilo " << key << " je obrisano iz sistema" << endl;
    }
    
    int getCount() const {
        return count;
    }
    
  
    
    void printTable() const {
        for (int i = 0; i < m; i++) {
            if (a[i].status == 2) {
                cout << "Kofa " << i << ": ";
                int probe = i;
                while (probe != -1) {
                    cout << a[probe].key;
                    if (a[probe].next != -1) {
                        if (a[probe].next >= m) {
                            cout << " -> [S" << (a[probe].next - m) << "]";
                        } else {
                            cout << " -> [" << a[probe].next << "]";
                        }
                    }
                    probe = a[probe].next;
                }
                cout << endl;
            }
        }
    }
};

int main() {
    
    ChainedScatterTable table(1000);
    

    table.insert("NI123AB");
    table.insert("BG456CD");
    table.insert("NI345KL");
    
    
    
    char reg1[] = "NI123AB";
    if (table.isIn(reg1)) {
        cout << "DA, Vozilo " << reg1 << " ima dozvolu za pristup zoni" << endl;
    } else {
        cout << "NE, Vozilo " << reg1 << " nema dozvolu" << endl;
    }
    
  
    table.insert("NI123AB");
    
 
    table.deleteVehicle(reg1);
    
  
    if (!table.isIn(reg1)) {
        cout << "Vozilo " << reg1 << " je obrisano" << endl;
    }
    
   
    char reg4[] = "XX999YY";
    table.deleteVehicle(reg4);
    
   
    table.printTable();
    
    return 0;
}