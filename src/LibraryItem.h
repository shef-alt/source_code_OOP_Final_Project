#pragma once
#include <string>
#include "IBorrowable.h"
using namespace std;

// ABSTRACTION: Pengguna cukup tahu item library punya jenis, 
// detail, masa pinjam, dan denda, tanpa tahu aturan detail tiap jenis.

class LibraryItem : public IBorrowable { // INTERFACE: Dengan menggunakan kontrak bisa meminjam
public:
    LibraryItem(int id, string title);
    virtual ~LibraryItem() {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    bool isAvailable() const { return borrowerId == -1; } // Implementasi kontrak IBorrowable
    int getBorrowerId() const { return borrowerId; }
    int getDueDay() const { return dueDay; }

    // ENCAPSULATION: status pinjam hanya berubah lewat dua method ini.
    // Mengembalikan pesan error, atau "" jika berhasil.
    string checkOut(int memberId, int today);
    string checkIn();

    int daysLate(int today) const;
    bool matches(string keyword) const;  // pencarian tanpa membedakan huruf besar/kecil

    // Digunakan oleh kelas turunan (POLYMORPHISM)
    virtual string type() const = 0;
    virtual string details() const = 0;
    virtual int loanPeriodDays() const = 0;
    virtual double calculateLateFee(int daysLate) const = 0;

private:
    int id;
    string title;
    int borrowerId;  // -1 artinya tidak sedang dipinjam
    int dueDay;
};
