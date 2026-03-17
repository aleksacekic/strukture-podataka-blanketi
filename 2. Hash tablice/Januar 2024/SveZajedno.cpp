#include <string.h>
#include <stdio.h>
#include <stdbool.h>

struct Player {
    int playerNumber;
    char name[32];
    char lastName[32];
    int yearBorn;
    int jerseyNumber;
}


typedef struct {
    int key;
    Player player;
    int status;
} ScatterObject;



int VELTABLICE = 1024;
ScatterObject hashTable[VELTABLICE];
int playerCount = 0;


void initHashTable(void) {
    int i;
    for (i = 0; i < VELTABLICE; i++) {
        hashTable[i].status = 0;
        hashTable[i].key = 0;
    }
    playerCount = 0;
}


unsigned int f(int yearBorn) {
    unsigned int hash = (unsigned int)yearBorn * 2654435761U;
    
    hash ^= (hash >> 16);
    
    return hash;
}


unsigned int h(int yearBorn) {
    return f(yearBorn) % VELTABLICE;
}

unsigned int c(unsigned int i) {
    return (i * i + i) / 2;
}


bool isPlayerRegistered(int playerNumber) {
    int i;
    for (i = 0; i < VELTABLICE; i++) {
        if (hashTable[i].status == 2 && 
            hashTable[i].player.playerNumber == playerNumber) {
            return true;
        }
    }
    return false;
}


bool signup(int playerNumber, char* name, char* lastName, int yearBorn, int jerseyNumber) {
    unsigned int base;
    unsigned int i;
    int idx;
    

    if (isPlayerRegistered(playerNumber)) {
        printf("greska: Kosarkas %d (%s %s) je vec prijavljen!\n", 
               playerNumber, name, lastName);
        return false;
    }
    

    if (playerCount >= VELTABLICE) {
        printf("greska: Kamp je pun\n");
        return false;
    }
    

    base = h(yearBorn);
    
    for (i = 0; i < VELTABLICE; i++) {
        idx = (base + c(i)) % VELTABLICE;
        
        if (hashTable[idx].status != 2) {
            hashTable[idx].key = yearBorn;
            hashTable[idx].player.playerNumber = playerNumber;
            strncpy(hashTable[idx].player.name, name, 31);
            hashTable[idx].player.name[31] = '\0';
            strncpy(hashTable[idx].player.lastName, lastName, 31);
            hashTable[idx].player.lastName[31] = '\0';
            hashTable[idx].player.yearBorn = yearBorn;
            hashTable[idx].player.jerseyNumber = jerseyNumber;
            hashTable[idx].status = 2;
            
            playerCount++;
            printf("Prijavljen: %s %s (broj %d, godiste %d)\n", 
                   name, lastName, playerNumber, yearBorn);
            return true;
        }
    }
    
    printf("Nema slobodnog mesta!\n");
    return false;
}


int countPlayersBornIn(int yearBorn) {
    unsigned int base = h(yearBorn); 
    unsigned int i;
    int idx;
    int count = 0;
    

    for (i = 0; i < VELTABLICE; i++) {
        idx = (base + c(i)) % VELTABLICE;
        
        if (hashTable[idx].status == 0) {
            break;
        }
        

        if (hashTable[idx].status == 2 && hashTable[idx].key == yearBorn) {
            count++;
        }
    }
    
    return count;
}



void listPlayersBornIn(int yearBorn) {
    unsigned int base = h(yearBorn);
    unsigned int i;
    int idx;
    
    for (i = 0; i < VELTABLICE; i++) {
        idx = (base + c(i)) % VELTABLICE;
        
        if (hashTable[idx].status == 0) break;
        
        if (hashTable[idx].status == 2 && hashTable[idx].key == yearBorn) {
            printf("  %d. %s %s (dres %d)\n",
                   hashTable[idx].player.playerNumber,
                   hashTable[idx].player.name,
                   hashTable[idx].player.lastName,
                   hashTable[idx].player.jerseyNumber);
        }
    }
}

void printStatsByYear(void) {
    int year;
    int count;
    
    for (year = 2000; year <= 2015; year++) {
        count = countPlayersBornIn(year);
        if (count > 0) {
            printf("Godiste %d: %d igrasa\n", year, count);
        }
    }
}

int main(void) {
    
    initHashTable();
    
    signup(12345, "Marko", "Markovic", 2008, 10);
    signup(12346, "Nikola", "Nikolic", 2008, 23);
    signup(12347, "Stefan", "Stefanovic", 2008, 7);
    

    signup(12345, "Marko", "Markovic", 2008, 10);//false?
    
    printf("Godiste 2008: %d igraca\n", countPlayersBornIn(2008));


    listPlayersBornIn(2008);

    
    printStatsByYear();
    
    return 0;
}