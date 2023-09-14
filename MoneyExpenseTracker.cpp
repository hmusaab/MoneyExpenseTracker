#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <ios>
#include <fstream>

using namespace std;

struct MonthlyExpenses {
    double entertainmentEx;
    double medicalEx;
    double foodEx;
    double HouseBillsEx;
    double insuranceEx;
    double utilitiesEx;
    double clothesEx;
    double GasBillsEx;
    double Money_For_CarEx;
    double PersonalEx;
};

struct MonthlyBudget {
    double entertainment;
    double medical;
    double food;
    double HouseBills;
    double insurance;
    double utilities;
    double clothes;
    double GasBills;
    double Money_For_Car;
    double Personal;
};

//prototypes declared outside of main so main function logic isn't distorted
void DescribesProgram();
void GetMonth(int& months);
void GetMonthlyExpenses(fstream& ExpenseFile, int months);
void GetMonthlyBudget(fstream& BudgetFile, int months);
void GetMonthlyReport(fstream& ExpenseFile, fstream& BudgetFile, int months);



void DescribesProgram() {
    cout << "Welcome to Musaabs Monthly Expense Tracker, this program will calculate how much you spend with 7 options" << endl;
    cout << "Hopefully, it's accurate enough. This program will be used with stuff I've learned, like fstream, etc." << endl;
    cout << "So hopefully this program runs well, and thanks for checking it out and don't judge. Ty." << endl;
}

void GetMonth(int& months) {
    cout << endl; 
    cout << "How many months would you like to review?: ";
    cin >> months;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter a valid input: ";
        cin >> months;
    }
}

void GetMonthlyExpenses(fstream& ExpenseFile, int months) {
    MonthlyExpenses mE;
    int count = 1;

    ExpenseFile.open("expense.bin", ios::app | ios::binary);
    if (ExpenseFile.fail()) {
        cout << "Couldn't open the expense.bin" << endl;
        system("read");
        
    }


    try {
        do {
            cout << "Enter your entertainment expenses for month " << count << ": ";
            cin >> mE.entertainmentEx;

            cout << "Enter your medical expenses for month " << count << ": ";
            cin >> mE.medicalEx;

            cout << "Enter your food expenses for month " << count << ": ";
            cin >> mE.foodEx;

            cout << "Enter your house expenses for month " << count << ": ";
            cin >> mE.HouseBillsEx;

            cout << "Enter your insurance expenses for month " << count << ": ";
            cin >> mE.insuranceEx;

            cout << "Enter your utilities expenses for month " << count << ": ";
            cin >> mE.utilitiesEx;

            cout << "Enter your clothes expenses for month " << count << ": ";
            cin >> mE.clothesEx;

            cout << "Enter your Gas expenses for month " << count << ": ";
            cin >> mE.GasBillsEx;

            cout << "Enter your Car expenses for month " << count << ": ";
            cin >> mE.Money_For_CarEx;

            cout << "Enter your personal expenses for month " << count << ": ";
            cin >> mE.PersonalEx;

            ExpenseFile.write(reinterpret_cast<char*>(&mE), sizeof(mE));
            count++;
            months--;

        } while (months != 0);
    }
    catch (...) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid error type input.";
    }

    ExpenseFile.close();
}

void GetMonthlyBudget(fstream& BudgetFile, int months) {
    MonthlyBudget mB;
    int count = 1;

    BudgetFile.open("budget.bin", ios::app | ios::binary);
    if (BudgetFile.fail()) {
        cout << "Couldn't open the budget.bin" << endl;
        system("read");
        
    }

    try {
        do {
            cout << "Enter your entertainment budget for month " << count << ": ";
            cin >> mB.entertainment;

            cout << "Enter your medical budget for month " << count << ": ";
            cin >> mB.medical;

            cout << "Enter your food budget for month " << count << ": ";
            cin >> mB.food;

            cout << "Enter your house budget for month " << count << ": ";
            cin >> mB.HouseBills;

            cout << "Enter your insurance budget for month " << count << ": ";
            cin >> mB.insurance;

            cout << "Enter your utilities budget for month " << count << ": ";
            cin >> mB.utilities;

            cout << "Enter your clothes budget for month " << count << ": ";
            cin >> mB.clothes;

            cout << "Enter your Gas budget for month " << count << ": ";
            cin >> mB.GasBills;

            cout << "Enter your Car budget for month " << count << ": ";
            cin >> mB.Money_For_Car;

            cout << "Enter your personal budget for month " << count << ": ";
            cin >> mB.Personal;

            BudgetFile.write(reinterpret_cast<char*>(&mB), sizeof(mB));
            count++;
            months--;

        } while (months != 0);
    }
    catch (...) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid error type input.";
    }

    BudgetFile.close();
}

void GetMonthlyReport(fstream& ExpenseFile, fstream& BudgetFile, int months) {
    MonthlyExpenses mE;
    MonthlyBudget mB;
    ofstream toFile; 

    ExpenseFile.open("expense.bin", ios::in | ios::binary);
    BudgetFile.open("budget.bin", ios::in | ios::binary);

    if (ExpenseFile.fail() || BudgetFile.fail()) {
        cout << "Couldn't open the files" << endl;
        system("read");
       
    }

    ExpenseFile.read(reinterpret_cast<char*>(&mE), sizeof(mE));
    BudgetFile.read(reinterpret_cast<char*>(&mB), sizeof(mB));

    while (!ExpenseFile.eof() && !BudgetFile.eof()) {



        cout << fixed << showpoint << setprecision(2);
        cout << "-------------------------------------------------------------------------------------\n";
        cout << left << setw(14) << "Category";
        cout << right << setw(11) << "Expenses";
        cout << right << setw(14) << "Budget";
        cout << right << setw(14) << "   Over(-) and under\n";
        cout << "-------------------------------------------------------------------------------------\n";

        // Displaying expenses and budget for each category
        cout << left << setw(14) << "Entertainment";
        cout << right << setw(11) << mE.entertainmentEx;
        cout << right << setw(14) << mB.entertainment;
        cout << right << setw(14) << (mE.entertainmentEx - mB.entertainment) << "\n";

        cout << left << setw(14) << "Medical";
        cout << right << setw(11) << mE.medicalEx;
        cout << right << setw(14) << mB.medical;
        cout << right << setw(14) << (mE.medicalEx - mB.medical) << "\n";

        cout << left << setw(14) << "Food";
        cout << right << setw(11) << mE.foodEx;
        cout << right << setw(14) << mB.food;
        cout << right << setw(14) << (mE.foodEx - mB.food) << "\n";

        cout << left << setw(14) << "House";
        cout << right << setw(11) << mE.HouseBillsEx;
        cout << right << setw(14) << mB.HouseBills;
        cout << right << setw(14) << (mE.HouseBillsEx - mB.HouseBills) << "\n";

        cout << left << setw(14) << "Insurance";
        cout << right << setw(11) << mE.insuranceEx;
        cout << right << setw(14) << mB.insurance;
        cout << right << setw(14) << (mE.insuranceEx - mB.insurance) << "\n";

        cout << left << setw(14) << "Utilities";
        cout << right << setw(11) << mE.utilitiesEx;
        cout << right << setw(14) << mB.utilities;
        cout << right << setw(14) << (mE.utilitiesEx - mB.utilities) << "\n";

        cout << left << setw(14) << "Clothes";
        cout << right << setw(11) << mE.clothesEx;
        cout << right << setw(14) << mB.clothes;
        cout << right << setw(14) << (mE.clothesEx - mB.clothes) << "\n";

        cout << left << setw(14) << "Gas";
        cout << right << setw(11) << mE.GasBillsEx;
        cout << right << setw(14) << mB.GasBills;
        cout << right << setw(14) << (mE.GasBillsEx - mB.GasBills) << "\n";

        cout << left << setw(14) << "Car";
        cout << right << setw(11) << mE.Money_For_CarEx;
        cout << right << setw(14) << mB.Money_For_Car;
        cout << right << setw(14) << (mE.Money_For_CarEx - mB.Money_For_Car) << "\n";

        cout << left << setw(14) << "Personal";
        cout << right << setw(11) << mE.PersonalEx;
        cout << right << setw(14) << mB.Personal;
        cout << right << setw(14) << (mE.PersonalEx - mB.Personal) << ":\n";


        cout << "For the month you are over budget by $" << (mE.entertainmentEx + mE.medicalEx + mE.foodEx + mE.HouseBillsEx + mE.insuranceEx + mE.utilitiesEx + mE.clothesEx + mE.GasBillsEx + mE.Money_For_CarEx + mE.PersonalEx) - (mB.entertainment + mB.medical + mB.food + mB.HouseBills + mB.insurance + mB.utilities + mB.clothes + mB.GasBills + mB.Money_For_Car + mB.Personal) << "\n";
        
        
        toFile.open("results.txt", ios::app);
        toFile << fixed << showpoint << setprecision(2);
        toFile << left << setw(14) << "Category";
        toFile << right << setw(11) << "Expenses";
        toFile << right << setw(14) << "Budget";
        toFile << right << setw(19) << "   Over(-) and under\n";
        toFile << "-------------------------------------------------------------------------------------\n";
        toFile << left << setw(14) << "Entertainment";
        toFile << right << setw(11) << mE.entertainmentEx;
        toFile << right << setw(14) << mB.entertainment;
        toFile << right << setw(14) << (mE.entertainmentEx - mB.entertainment) << "\n";

        toFile << left << setw(14) << "Medical";
        toFile << right << setw(11) << mE.medicalEx;
        toFile << right << setw(14) << mB.medical;
        toFile << right << setw(14) << (mE.medicalEx - mB.medical) << "\n";

        toFile << left << setw(14) << "Food";
        toFile << right << setw(11) << mE.foodEx;
        toFile << right << setw(14) << mB.food;
        toFile << right << setw(14) << (mE.foodEx - mB.food) << "\n";

        toFile << left << setw(14) << "House";
        toFile << right << setw(11) << mE.HouseBillsEx;
        toFile << right << setw(14) << mB.HouseBills;
        toFile << right << setw(14) << (mE.HouseBillsEx - mB.HouseBills) << "\n";

        toFile << left << setw(14) << "Insurance";
        toFile << right << setw(11) << mE.insuranceEx;
        toFile << right << setw(14) << mB.insurance;
        toFile << right << setw(14) << (mE.insuranceEx - mB.insurance) << "\n";

        toFile << left << setw(14) << "Utilities";
        toFile << right << setw(11) << mE.utilitiesEx;
        toFile << right << setw(14) << mB.utilities;
        toFile << right << setw(14) << (mE.utilitiesEx - mB.utilities) << "\n";

        toFile << left << setw(14) << "Clothes";
        toFile << right << setw(11) << mE.clothesEx;
        toFile << right << setw(14) << mB.clothes;
        toFile << right << setw(14) << (mE.clothesEx - mB.clothes) << "\n";

        toFile << left << setw(14) << "Gas";
        toFile << right << setw(11) << mE.GasBillsEx;
        toFile << right << setw(14) << mB.GasBills;
        toFile << right << setw(14) << (mE.GasBillsEx - mB.GasBills) << "\n";

        toFile << left << setw(14) << "Car";
        toFile << right << setw(11) << mE.Money_For_CarEx;
        toFile << right << setw(14) << mB.Money_For_Car;
        toFile << right << setw(14) << (mE.Money_For_CarEx - mB.Money_For_Car) << "\n";

        toFile << left << setw(14) << "Personal";
        toFile << right << setw(11) << mE.PersonalEx;
        toFile << right << setw(14) << mB.Personal;
        toFile << right << setw(14) << (mE.PersonalEx - mB.Personal) << ":\n";

        toFile << "For the month you are over budget by $" << (mE.entertainmentEx + mE.medicalEx + mE.foodEx + mE.HouseBillsEx + mE.insuranceEx + mE.utilitiesEx + mE.clothesEx + mE.GasBillsEx + mE.Money_For_CarEx + mE.PersonalEx) - (mB.entertainment + mB.medical + mB.food + mB.HouseBills + mB.insurance + mB.utilities + mB.clothes + mB.GasBills + mB.Money_For_Car + mB.Personal) << "\n";

        ExpenseFile.read(reinterpret_cast<char*>(&mE), sizeof(mE));
        BudgetFile.read(reinterpret_cast<char*>(&mB), sizeof(mB));
    }

    ExpenseFile.close();
    BudgetFile.close();
}


int main() {
    int months = 1;
    fstream ExpenseFile, BudgetFile;
    DescribesProgram();
    GetMonth(months);
    GetMonthlyExpenses(ExpenseFile, months);
    GetMonthlyBudget(BudgetFile, months);
    GetMonthlyReport(ExpenseFile, BudgetFile, months);

    return 0;
}
