#include <stdio.h>
#include <stdlib.h>
#include "user_auth.h"
#include "tracker.h"
#include "goals_reminders.h"

int main() {
    int choice, loggedIn = 0;
    char username[50];
    struct Goal *goalHead = NULL;

    printf("=== SMART BUDGET & EXPENSE TRACKER ===\n");

    while (1) {
        printf("\n1. Signup\n2. Login\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: signup(); break;
            case 2:
                if (login()) {
                    printf("Enter your username again: ");
                    scanf("%s", username);
                    loadGoalsFromFile(&goalHead, username);
                    loggedIn = 1;
                }
                break;
            case 3: exit(0);
            default: printf("Invalid choice!\n");
        }

        while (loggedIn) {
            printf("\n--- MAIN MENU ---\n");
            printf("1. Add Transaction\n");
            printf("2. View Transactions\n");
            printf("3. Calculate Balance\n");
            printf("4. Manage Saving Goals\n");
            printf("5. View Goal Reminders\n");
            printf("6. View Give/Take Reminders\n");
            printf("7. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: addTransaction(username); break;
                case 2: viewTransactions(username); break;
                case 3: calculateBalance(username); break;

                case 4: {
                    int gch;
                    printf("\n--- SAVING GOAL SECTION ---\n");
                    printf("1. Add Goal\n2. Update Goal\n3. View Goals\n4. Back\nChoice: ");
                    scanf("%d", &gch);
                    if (gch == 1) {
                        addGoal(&goalHead);
                        // also create reminder
                        addGoalReminder(username, goalHead->name, goalHead->deadline);
                    } else if (gch == 2) updateGoal(goalHead);
                    else if (gch == 3) viewGoals(goalHead);
                    break;
                }

                case 5: viewGoalReminders(username); break;
                case 6: viewPaymentReminders(username); break;

                case 7:
                    saveGoalsToFile(goalHead, username);
                    loggedIn = 0;
                    break;

                default:
                    printf("Invalid choice!\n");
            }
        }
    }
    return 0;
}
