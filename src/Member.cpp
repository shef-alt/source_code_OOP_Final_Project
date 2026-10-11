#include "Member.h"

Member::Member(int id, string name) {
    this->id = id;
    this->name = name;
    fines = 0;
}

string Member::borrowBlockReason() const {
    if (fines > 0) return name + " has unpaid fines.";
    if ((int)loanedItemIds.size() >= maxLoans())
        return name + " reached the loan limit (" + to_string(maxLoans()) + ").";
    return "";
}

string Member::addLoan(int itemId) {
    string reason = borrowBlockReason();
    if (reason != "") return reason;
    loanedItemIds.push_back(itemId);
    return "";
}

string Member::removeLoan(int itemId) {
    for (int i = 0; i < (int)loanedItemIds.size(); i++) {
        if (loanedItemIds[i] == itemId) {
            loanedItemIds.erase(loanedItemIds.begin() + i);
            return "";
        }
    }
    return "Member does not hold this item.";
}

string Member::addFine(double amount) {
    if (amount < 0) return "Fine cannot be negative.";
    fines += amount;
    return "";
}

double Member::payAllFines() {
    double paid = fines;
    fines = 0;
    return paid;
}
