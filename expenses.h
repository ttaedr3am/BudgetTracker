#ifndef EXPENSES_H
#define EXPENSES_H

#define MAX_EXPENSES 100

struct Expense {
    char category[20];
    float amount;
};

void monthlySummary(struct Expense expenses[], int count);

#endif
