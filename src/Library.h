#pragma once
#include "Items.h"
#include "Member.h"
#include <string>
#include <vector>
using namespace std;

// ABSTRACTION: GUI/console hanya memanggil borrowItem, returnItem, dst.
// Validasi, perhitungan jatuh tempo, dan denda disembunyikan di sini.
// Semua method yang bisa gagal mengembalikan pesan error, "" jika berhasil.

class Library {
public:
    Library();
    ~Library();

    int addItem(string type, string title, string detail, string &error);
    int addMember(string role, string name, string &error);

    string borrowItem(int memberId, int itemId);
    string returnItem(int itemId, double &fee);   // fee = denda (0 jika tepat waktu)
    string payFines(int memberId, double &paid);
    void advanceDays(int days) { today += days; }
    int getToday() const { return today; }

    // Polymorphism static/overloading, dua versi findItems (GUI memakai yang versi pertama, konsol memakai keduanya)
    vector<const LibraryItem*> findItems(string keyword) const; // tampilkan semua items
    vector<const LibraryItem*> findItems(string keyword, bool availableOnly) const; // tampilkan items yang tersedia/tidak

    vector<const LibraryItem*> itemList() const;
    vector<const Member*> memberList() const;
    const LibraryItem* getItem(int id) const; 
    const Member* getMember(int id) const;    

    void seedSampleData();

private:
    LibraryItem* findItem(int id) const;
    Member* findMember(int id) const;

    // Polymorphism dynamic, koleksi pointer ke base class
    vector<LibraryItem*> items;
    vector<Member*> members;
    int nextItemId;
    int nextMemberId;
    int today;
};
