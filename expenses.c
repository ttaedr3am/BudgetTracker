#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expenses.h"

void addExpense(struct Expense expenses[], int *count) {
    if (*count >= MAX_EXPENSES) {
        printf("Expense limit reached!\n");
        return;
    }

    printf("Enter category (Food/Travel/Rent/Others): ");
    scanf("%s", expenses[*count].category);
    printf("Enter amount: ");
    scanf("%f", &expenses[*count].amount);
    printf("Enter description: ");
    scanf(" %[^\n]", expenses[*count].description);
    printf("Enter date (DD/MM/YYYY): ");
    scanf("%s", expenses[*count].date);

    (*count)++;
    printf("Expense added successfully!\n");
}

void viewExpenses(struct Expense expenses[], int count) {
    if (count == 0) {
        printf("No expenses recorded yet.\n");
        return;
    }

    printf("\n%-15s %-10s %-20s %-12s\n", "CATEGORY", "AMOUNT", "DESCRIPTION", "DATE");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-15s %-10.2f %-20s %-12s\n",
               expenses[i].category, expenses[i].amount,
               expenses[i].description, expenses[i].date);
    }
}

void saveExpenses(struct Expense expenses[], int count, char username[]) {
    char filename[50];
    sprintf(filename, "expenses_%s.txt", username);

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error saving expenses!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        // write as: category amount description date (description has no newline)
        fprintf(fp, "%s %.2f %s %s\n",
                expenses[i].category, expenses[i].amount,
                expenses[i].description, expenses[i].date);
    }

    fclose(fp);
}

void loadExpenses(struct Expense expenses[], int *count, char username[]) {
    char filename[50];
    sprintf(filename, "expenses_%s.txt", username);

    FILE *fp = fopen(filename, "r");
    if (!fp) return;

    while (fscanf(fp, "%s %f %[^\n] %s",
                  expenses[*count].category,
                  &expenses[*count].amount,
                  expenses[*count].description,
                  expenses[*count].date) != EOF) {
        (*count)++;
        if (*count >= MAX_EXPENSES) break;
    }
    fclose(fp);
}

void monthlySummary(struct Expense expenses[], int count) {
    float food = 0, travel = 0, rent = 0, others = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(expenses[i].category, "Food") == 0)
            food += expenses[i].amount;
        else if (strcmp(expenses[i].category, "Travel") == 0)
            travel += expenses[i].amount;
        else if (strcmp(expenses[i].category, "Rent") == 0)
            rent += expenses[i].amount;
        else
            others += expenses[i].amount;
    }

    float total = food + travel + rent + others;
    printf("\n---- Monthly Summary ----\n");
    printf("Food   : %.2f\n", food);
    printf("Travel : %.2f\n", travel);
    printf("Rent   : %.2f\n", rent);
    printf("Others : %.2f\n", others);
    printf("Total  : %.2f\n", total);

    // optional: export summary for Sayali
    FILE *fp = fopen("monthly_summary.txt", "w");
    if (fp) {
        fprintf(fp, "Food %.2f\nTravel %.2f\nRent %.2f\nOthers %.2f\nTotal %.2f\n",
                food, travel, rent, others, total);
        fclose(fp);
    }
}
