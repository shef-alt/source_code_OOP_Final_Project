#pragma once
#include "LibraryItem.h"

// INHERITANCE: Book, magazine,dan DVD adalah LibraryItem (relasi is-a).
// Atribut id, judul, status pinjam diwarisi dari LibraryItem.
// Tipe, detail, masa denda, dan rumus denda dispesialisasi per kelas dari LibraryItem.

class Book : public LibraryItem {
public:
    Book(int id, string title, string author) : LibraryItem(id, title) {
        this->author = author;
    }
    // Polymorphirsm Overriding
    string type() const override { return "Book"; }
    string details() const override { return "Author: " + author; }
    int loanPeriodDays() const override { return 14; }
    double calculateLateFee(int daysLate) const override { return daysLate * 1000.0; }

private:
    string author;
};

class Magazine : public LibraryItem {
public:
    Magazine(int id, string title, string issue) : LibraryItem(id, title) {
        this->issue = issue;
    }
    string type() const override { return "Magazine"; }
    string details() const override { return "Issue: " + issue; }
    int loanPeriodDays() const override { return 7; }
    double calculateLateFee(int daysLate) const override {
        double fee = daysLate * 500.0;
        if (fee > 5000) fee = 5000;
        return fee;
    }

private:
    string issue;
};

class DVD : public LibraryItem {
public:
    DVD(int id, string title, int minutes) : LibraryItem(id, title) {
        this->minutes = minutes;
    }
    string type() const override { return "DVD"; }
    string details() const override { return "Duration: " + to_string(minutes) + " min"; }
    int loanPeriodDays() const override { return 3; }
    double calculateLateFee(int daysLate) const override {
        if (daysLate <= 0) return 0;
        return daysLate * 2000.0 + 5000.0;
    }

private:
    int minutes;
};
