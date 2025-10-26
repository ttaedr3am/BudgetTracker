#include <stdio.h>
#include <stdlib.h>
#include "user_auth.h"
#include "tracker.h"

int main() {
    int choice, loggedIn = 0;
    char username[50];

    printf("=== SMART BUDGET & EXPENSE TRACKER ===\n");
    while (1) {
        printf("\n1. Signup\n2. Login\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: signup(); break;
            case 2:
                if (login()) {
                    printf("Enter your username again to continue: ");
                    scanf("%s", username);
                    loggedIn = 1;
                }
                break;
            case 3: exit(0);
            default: printf("Invalid choice!\n");
        }

        while (loggedIn) {
            printf("\n--- MENU ---\n");
            printf("1. Add Transaction\n2. View Transactions\n3. Calculate Balance\n4. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: addTransaction(username); break;
                case 2: viewTransactions(username); break;
                case 3: calculateBalance(username); break;
                case 4: loggedIn = 0; break;
                default: printf("Invalid choice!\n");
            }
        }
    }
    return 0;
}
