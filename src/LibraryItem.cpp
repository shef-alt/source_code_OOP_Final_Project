#include "LibraryItem.h"

static string toLower(string s) {
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') c = c + 32;
    }
    return s;
}

LibraryItem::LibraryItem(int id, string title) {
    this->id = id;
    this->title = title;
    borrowerId = -1;
    dueDay = 0;
}

string LibraryItem::checkOut(int memberId, int today) {
    if (!isAvailable()) return "Item '" + title + "' is already borrowed.";
    borrowerId = memberId;
    dueDay = today + loanPeriodDays();  
    return "";
}

string LibraryItem::checkIn() {
    if (isAvailable()) return "Item '" + title + "' is not borrowed.";
    borrowerId = -1;
    dueDay = 0;
    return "";
}

int LibraryItem::daysLate(int today) const {
    if (isAvailable()) return 0;
    int late = today - dueDay;
    return late > 0 ? late : 0;
}

bool LibraryItem::matches(string keyword) const {
    keyword = toLower(keyword);
    return toLower(title).find(keyword) != string::npos ||
           toLower(type()).find(keyword) != string::npos ||
           toLower(details()).find(keyword) != string::npos;
}
