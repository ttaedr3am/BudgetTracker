#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_auth.h"
#include "give_take.h"
#include "summary.h"
#include "goals_reminders.h"

// MAIN STARTS
int main() {
    int choice, loggedIn = 0;
    char username[50];
    struct Goal *goalHead = NULL;

    printf("=== SMART BUDGET & EXPENSE TRACKER ===\n");

    while (1) {
        printf("\n1. Signup\n2. Login\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signup();
                break;

            case 2:
                if (login()) {
                    printf("Enter your username again: ");
                    scanf("%s", username);
                    loadGoalsFromFile(&goalHead, username);
                    loggedIn = 1;
                    setBudget(); // Nakshatra’s budget setup
                }
                break;

            case 3:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }

        while (loggedIn) {
            printf("\n--- MAIN MENU ---\n");
            printf("1. Add Expense\n"); //sayali
            printf("2. View Expenses\n"); //sayali
            printf("3. Show Pie Chart Summary\n"); //nakshatra
            printf("4. Show Budget Notification\n"); //nakshatra
            printf("5. Manage Saving Goals\n"); //toral
            printf("6. View Goal Reminders\n"); //toral
            printf("7. Give/Take Money Tracker\n"); //sayali
            printf("8. Logout\n"); //sayali
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addExpense();
                    break;

                case 2:
                    viewExpenses();
                    break;

                case 3:
                    showPieChart();
                    break;

                case 4:
                    showNotification(calculateTotal());
                    break;

                case 5: {
                    int gch;
                    printf("\n--- SAVING GOAL SECTION ---\n");
                    printf("1. Add Goal\n2. Update Goal\n3. View Goals\n4. Back\nChoice: ");
                    scanf("%d", &gch);

                    if (gch == 1) {
                        addGoal(&goalHead);
                        addGoalReminder(username, goalHead->name, goalHead->deadline);
                    } else if (gch == 2)
                        updateGoal(goalHead);
                    else if (gch == 3)
                        viewGoals(goalHead);

                    break;
                }

                case 6:
                    viewGoalReminders(username);
                    break;

                case 7: {
                    printf("\n--- GIVE/TAKE MONEY TRACKER ---\n");
                    giveTakeMenu(username);
                    break;
                }

                case 8:
                    saveGoalsToFile(goalHead, username);
                    loggedIn = 0;
                    printf("Logged out successfully.\n");
                    break;

                default:
                    printf("Invalid choice!\n");
            }
        }
    }

    return 0;
}
