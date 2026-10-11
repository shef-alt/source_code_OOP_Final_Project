#include "Library.h"
#include <iostream>

void tryBorrow(Library &lib, int memberId, int itemId) {
    string error = lib.borrowItem(memberId, itemId);
    if (error != "") cout << "Ditolak: " << error << "\n";
    else cout << "Berhasil: " << lib.getMember(memberId)->getName() << " meminjam "
              << lib.getItem(itemId)->getTitle() << "\n";
}

int main() {
    Library lib;
    lib.seedSampleData();

    cout << "=== Polymorphism ===\n";
    vector<const LibraryItem*> items = lib.itemList();
    for (const LibraryItem *item : items) {
        cout << item->type() << " | " << item->getTitle()
             << " | loan " << item->loanPeriodDays() << " days"
             << " | fee for 5 days late: Rp " << item->calculateLateFee(5) << "\n";
    }

    cout << "\n=== Skenario peminjaman ===\n";
    tryBorrow(lib, 1, 6);  // Andi pinjam DVD
    tryBorrow(lib, 1, 1);  // Andi pinjam book
    tryBorrow(lib, 2, 6);  // gagal: DVD sudah dipinjam

    lib.advanceDays(6);    // +6 days, DVD terlambat 3 hari, book belum
    cout << "\nHari ke-" << lib.getToday() << ". Mengembalikan DVD...\n";
    double fee = 0;
    lib.returnItem(6, fee);
    cout << "Denda DVD: Rp " << fee << "\n";

    tryBorrow(lib, 1, 2);  // ditolak karena ada denda

    double paid = 0;
    lib.payFines(1, paid);
    cout << "Andi membayar denda: Rp " << paid << "\n";
    tryBorrow(lib, 1, 2);  // baru berhasil setelah bayar fines

    cout << "\n=== Overloading: pencarian ===\n";
    for (const LibraryItem *item : lib.findItems("dvd"))
        cout << " semua    : " << item->getTitle() << "\n";
    for (const LibraryItem *item : lib.findItems("book", true))
        cout << " tersedia : " << item->getTitle() << "\n";
    return 0;
}
