#ifndef EXPENSES_H
#define EXPENSES_H

#define MAX_EXPENSES 100

struct Expense {
    char category[20];
    float amount;
    char description[50];
    char date[15]; // DD/MM/YYYY
};

void addExpense(struct Expense expenses[], int *count);
void viewExpenses(struct Expense expenses[], int count);
void monthlySummary(struct Expense expenses[], int count);
void saveExpenses(struct Expense expenses[], int count, char username[]);
void loadExpenses(struct Expense expenses[], int *count, char username[]);

#endif
