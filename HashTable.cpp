#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
private:
    vector<int> table;       // The hash table itself
    vector<bool> occupied;   // To track occupied positions
    int currentSize;         // Current number of elements in the table
    int tableSize;           // The size of the table
    const double loadFactorThreshold = 0.8; // Load factor threshold

    // Helper function to check if a number is prime
    bool isPrime(int num) {
        if (num < 2) return false;
        for (int i = 2; i <= sqrt(num); ++i) {
            if (num % i == 0) return false;
        }
        return true;
    }

    // Helper function to find the next prime number greater than or equal to n
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Hash function: h(k) = k mod tableSize
    int hashFunction(int key) {
        return key % tableSize;
    }

    // Function to resize the table when the load factor exceeds threshold
    void resizeTable() {
        int newTableSize = nextPrime(tableSize * 2);  // Find next prime
        vector<int> oldTable = table;
        vector<bool> oldOccupied = occupied;

        // Initialize new table
        table.assign(newTableSize, -1);   // Reset table
        occupied.assign(newTableSize, false);  // Reset occupancy
        currentSize = 0;                  // Reset current size
        tableSize = newTableSize;         // Update table size

        // Rehash all existing elements into the new table
        for (int i = 0; i < oldTable.size(); ++i) {
            if (oldOccupied[i]) {
                insert(oldTable[i]);  // Reinsert to the new table
            }
        }
    }

public:
    // Constructor
    HashTable(int initialSize = 5) {
        tableSize = nextPrime(initialSize);
        table.assign(tableSize, -1);  // Initialize with -1 to signify empty
        occupied.assign(tableSize, false); // Initialize occupied status
        currentSize = 0;
    }

    // Insert a key
    void insert(int key) {
        // Check if the key already exists
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        // Resize if load factor exceeds the threshold
        double a= (currentSize+1) / tableSize; //load factor after adding one more element
        if (a >= loadFactorThreshold) {  //resize if adding the new element would make the load factor cross 0.8
            resizeTable();
        }

        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing to handle collisions
        while (occupied[index]) {
            i++;
            index = (hashFunction(key) + i * i) % tableSize;

            // If max probing limit is reached
            if (i >= ((tableSize+1)/2)) {
                cout << "Max probing limit reached!" << endl;
                return;
            }
        }

        // Insert the key into the table
        table[index] = key;
        occupied[index] = true;
        currentSize++;
    }

    // Search for a key and return its index, or -1 if not found
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;

        // Quadratic probing to find the key
        while (occupied[index]) {
            if (table[index] == key) {
                return index;
            }
            i++;
            index = (hashFunction(key) + i * i) % tableSize;

            // Stop searching if we have completed one full loop
            if (i >= tableSize) {
                return -1;
            }
        }

        return -1;  // Key not found
    }

    // Remove a key from the table
    void remove(int key) {
        int index = search(key);

        if (index == -1) {
            cout << "Element not found" << endl;
            return;
        }

        // Mark the slot as deleted
        table[index] = -1;          // Mark as empty
        occupied[index] = false;    // Mark slot as unoccupied for future insertions
        currentSize--;
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < tableSize; ++i) {
            if (!occupied[i]) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};

// Sample main.cpp for testing
int main() {
    int initialSize = 5; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 
    ht.insert(33);  
    ht.printTable(); 

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}
