#include "Library.h"
#include <cstdlib>

Library::Library() {
    nextItemId = 1;
    nextMemberId = 1;
    today = 1;
}

Library::~Library() {
    for (LibraryItem *item : items) delete item;
    for (Member *member : members) delete member;
}

int Library::addItem(string type, string title, string detail, string &error) {
    error = "";
    if (title == "") {
        error = "Title cannot be empty.";
        return -1;
    }
    int id = nextItemId;
    if (type == "Book") {
        items.push_back(new Book(id, title, detail));
    } else if (type == "Magazine") {
        items.push_back(new Magazine(id, title, detail));
    } else if (type == "DVD") {
        int minutes = atoi(detail.c_str());
        if (minutes <= 0) {
            error = "DVD duration must be a positive number.";
            return -1;
        }
        items.push_back(new DVD(id, title, minutes));
    } else {
        error = "Unknown item type: " + type;
        return -1;
    }
    nextItemId++;
    return id;
}

int Library::addMember(string role, string name, string &error) {
    error = "";
    if (name == "") {
        error = "Name cannot be empty.";
        return -1;
    }
    int id = nextMemberId;
    if (role == "Student") {
        members.push_back(new StudentMember(id, name));
    } else if (role == "Lecturer") {
        members.push_back(new LecturerMember(id, name));
    } else {
        error = "Unknown role: " + role;
        return -1;
    }
    nextMemberId++;
    return id;
}

LibraryItem* Library::findItem(int id) const {
    for (LibraryItem *item : items)
        if (item->getId() == id) return item;
    return nullptr;
}

Member* Library::findMember(int id) const {
    for (Member *member : members)
        if (member->getId() == id) return member;
    return nullptr;
}

const LibraryItem* Library::getItem(int id) const { return findItem(id); }
const Member* Library::getMember(int id) const { return findMember(id); }

string Library::borrowItem(int memberId, int itemId) {
    Member *member = findMember(memberId);
    LibraryItem *item = findItem(itemId);
    if (member == nullptr) return "Member not found.";
    if (item == nullptr) return "Item not found.";
    if (!item->isAvailable()) return "Item '" + item->getTitle() + "' is already borrowed.";

    string error = member->addLoan(itemId);  // menolak jika member tidak boleh pinjam
    if (error != "") return error;
    item->checkOut(memberId, today);
    return "";
}

string Library::returnItem(int itemId, double &fee) {
    fee = 0;
    LibraryItem *item = findItem(itemId);
    if (item == nullptr) return "Item not found.";
    if (item->isAvailable()) return "Item '" + item->getTitle() + "' is not borrowed.";

    Member *member = findMember(item->getBorrowerId());
    fee = item->calculateLateFee(item->daysLate(today));  
    item->checkIn();
    if (member != nullptr) {
        member->removeLoan(itemId);
        if (fee > 0) member->addFine(fee);
    }
    return "";
}

string Library::payFines(int memberId, double &paid) {
    paid = 0;
    Member *member = findMember(memberId);
    if (member == nullptr) return "Member not found.";
    paid = member->payAllFines();
    return "";
}

vector<const LibraryItem*> Library::findItems(string keyword) const {
    return findItems(keyword, false);
}

vector<const LibraryItem*> Library::findItems(string keyword, bool availableOnly) const {
    vector<const LibraryItem*> result;
    for (LibraryItem *item : items) {
        if (item->matches(keyword) && (!availableOnly || item->isAvailable()))
            result.push_back(item);
    }
    return result;
}

vector<const LibraryItem*> Library::itemList() const {
    vector<const LibraryItem*> result;
    for (LibraryItem *item : items) result.push_back(item);
    return result;
}

vector<const Member*> Library::memberList() const {
    vector<const Member*> result;
    for (Member *member : members) result.push_back(member);
    return result;
}

// Sample data
void Library::seedSampleData() {
    string error;
    addItem("Book", "Clean Code", "Robert C. Martin", error);
    addItem("Book", "Design Patterns", "Erich Gamma et al.", error);
    addItem("Book", "The C++ Programming Language", "Bjarne Stroustrup", error);
    addItem("Magazine", "National Geographic", "Oct 2026", error);
    addItem("Magazine", "Tempo", "Edition 41", error);
    addItem("DVD", "Inside the Machine", "95", error);
    addItem("DVD", "Algorithms Explained", "120", error);
    addMember("Student", "Andi", error);
    addMember("Lecturer", "Dr. Budi", error);
}
