#pragma once
#include <string>
#include <vector>
using namespace std;

// ENCAPSULATION: daftar pinjaman dan denda bersifat private. Perubahan hanya
// lewat method yang menggunakan aturan (batas pinjam, denda tidak negatif).
// INHERITANCE + POLYMORPHISM: batas pinjam berbeda untuk tiap peran.

class Member {
public:
    Member(int id, string name);
    virtual ~Member() {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getFines() const { return fines; }
    const vector<int>& getLoans() const { return loanedItemIds; }

    virtual string role() const = 0;
    virtual int maxLoans() const = 0;

    string borrowBlockReason() const;  // "" jika boleh meminjam

    // Method di bawah mengembalikan pesan error, atau "" jika berhasil
    string addLoan(int itemId);
    string removeLoan(int itemId);
    string addFine(double amount);
    double payAllFines();  // mengembalikan jumlah yang dibayar

private:
    int id;
    string name;
    double fines;
    vector<int> loanedItemIds;
};

class StudentMember : public Member {
public:
    StudentMember(int id, string name) : Member(id, name) {}
    string role() const override { return "Student"; }
    int maxLoans() const override { return 3; }
};

class LecturerMember : public Member {
public:
    LecturerMember(int id, string name) : Member(id, name) {}
    string role() const override { return "Lecturer"; }
    int maxLoans() const override { return 6; }
};
