#include <bits/stdc++.h>
using namespace std;

struct Expense {
    int id;
    string date;       // format: YYYY-MM-DD
    string category;
    double amount;
    string note;
};

class ExpenseManager {
private:
    vector<Expense> expenses;
    int nextId;
    const string filename = "expenses.txt";

public:
    ExpenseManager() : nextId(1) {
        loadFromFile();
    }

    void addExpense() {
        Expense e;
        e.id = nextId++;
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> e.date;
        cout << "Enter category (Food/Travel/Other): ";
        cin >> e.category;
        cout << "Enter amount: ";
        cin >> e.amount;
        cin.ignore();
        cout << "Enter note: ";
        getline(cin, e.note);

        expenses.push_back(e);
        saveToFile();
        cout << "Expense added successfully!\n";
    }

    void viewExpenses() {
        if (expenses.empty()) {
            cout << "No expenses recorded.\n";
            return;
        }

        cout << "\n---- All Expenses ----\n";
        for (auto &e : expenses) {
            cout << "ID: " << e.id
                 << " | Date: " << e.date
                 << " | Category: " << e.category
                 << " | Amount: " << e.amount
                 << " | Note: " << e.note << "\n";
        }
    }

    void editExpense() {
        int id;
        cout << "Enter ID of expense to edit: ";
        cin >> id;
        for (auto &e : expenses) {
            if (e.id == id) {
                cout << "Editing Expense ID: " << id << "\n";
                cout << "Enter new date (YYYY-MM-DD): ";
                cin >> e.date;
                cout << "Enter new category: ";
                cin >> e.category;
                cout << "Enter new amount: ";
                cin >> e.amount;
                cin.ignore();
                cout << "Enter new note: ";
                getline(cin, e.note);

                saveToFile();
                cout << "Expense updated successfully!\n";
                return;
            }
        }
        cout << "Expense ID not found!\n";
    }

    void deleteExpense() {
        int id;
        cout << "Enter ID of expense to delete: ";
        cin >> id;
        auto it = remove_if(expenses.begin(), expenses.end(),
                            [id](const Expense &e) { return e.id == id; });

        if (it != expenses.end()) {
            expenses.erase(it, expenses.end());
            saveToFile();
            cout << "Expense deleted successfully!\n";
        } else {
            cout << "Expense ID not found!\n";
        }
    }

    void monthlyReport() {
        if (expenses.empty()) {
            cout << "No expenses recorded.\n";
            return;
        }

        string month;
        cout << "Enter month (YYYY-MM): ";
        cin >> month;

        double total = 0;
        map<string, double> categoryTotals;

        cout << "\n---- Monthly Report for " << month << " ----\n";
        for (auto &e : expenses) {
            if (e.date.find(month) == 0) { // Check if the date starts with the month
                cout << "ID: " << e.id << " | Date: " << e.date << " | Category: "
                     << e.category << " | Amount: " << e.amount << " | Note: " << e.note << "\n";
                total += e.amount;
                categoryTotals[e.category] += e.amount;
            }
        }

        cout << "\nTotal Expenses for " << month << ": " << total << "\n";
        cout << "Category-wise Breakdown:\n";
        for (auto &c : categoryTotals) {
            cout << "  " << c.first << ": " << c.second << "\n";
        }
    }

    void saveToFile() {
        ofstream out(filename);
        if (!out) return;
        for (auto &e : expenses) {
            out << e.id << "|" << e.date << "|" << e.category << "|"
                << e.amount << "|" << e.note << "\n";
        }
        out.close();
    }

    void loadFromFile() {
        ifstream in(filename);
        if (!in) return;

        expenses.clear();
        string line;
        while (getline(in, line)) {
            stringstream ss(line);
            Expense e;
            string amountStr;
            getline(ss, line, '|'); e.id = stoi(line);
            getline(ss, e.date, '|');
            getline(ss, e.category, '|');
            getline(ss, amountStr, '|'); e.amount = stod(amountStr);
            getline(ss, e.note);
            expenses.push_back(e);
            nextId = max(nextId, e.id + 1);
        }
        in.close();
    }
};

int main() {
    ExpenseManager manager;
    int choice;

    while (true) {
        cout << "\n--- Personal Expense Tracker ---\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Edit Expense\n";
        cout << "4. Delete Expense\n";
        cout << "5. Monthly Report\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: manager.addExpense(); break;
        case 2: manager.viewExpenses(); break;
        case 3: manager.editExpense(); break;
        case 4: manager.deleteExpense(); break;
        case 5: manager.monthlyReport(); break;
        case 0: exit(0);
        default: cout << "Invalid choice!\n";
        }
    }
}
