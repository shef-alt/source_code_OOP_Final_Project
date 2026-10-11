#pragma once 
#include <string> 
using namespace std;

// INTERFACE: kontrak kemampuan "bisa dipinjam". 
// Dengan semua method pure virtual, tidak ada data. 

class IBorrowable { 
public: 
 virtual ~IBorrowable() {} 
 virtual bool isAvailable() const = 0; 
 virtual string checkOut(int memberId, int today) = 0; 
 virtual string checkIn() = 0; 
}; 
