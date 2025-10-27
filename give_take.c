#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "give_take.h"

void saveTransactions(struct Transaction *head, char username[50]) {
    char filename[60];
    sprintf(filename, "%s_transactions.txt", username);
    FILE *fp = fopen(filename, "w");
    struct Transaction *temp = head;

    while (temp) {
        fprintf(fp, "%s %s %.2f %s\n", temp->type, temp->person, temp->amount, temp->deadline);
        temp = temp->next;
    }
    fclose(fp);
}

void viewTransactions(struct Transaction *head) {
    if (!head) {
        printf("No transactions yet.\n");
        return;
    }
    struct Transaction *temp = head;
    while (temp) {
        printf("%s -> %s : %.2f (till %s)\n", temp->type, temp->person, temp->amount, temp->deadline);
        temp = temp->next;
    }
}

void addTransaction(struct Transaction **head) {
    struct Transaction *newNode = malloc(sizeof(struct Transaction));
    printf("Is this a Give or Take? ");
    scanf("%s", newNode->type);

    if (strcmp(newNode->type, "Give") == 0) {
        printf("Whom to give: ");
        scanf("%s", newNode->person);
        printf("How much to give: ");
        scanf("%f", &newNode->amount);
        printf("Till when to give (DD/MM/YYYY): ");
        scanf("%s", newNode->deadline);
    } else {
        printf("From whom to take: ");
        scanf("%s", newNode->person);
        printf("How much to take: ");
        scanf("%f", &newNode->amount);
        printf("Till when to take (DD/MM/YYYY): ");
        scanf("%s", newNode->deadline);
    }

    newNode->next = *head;
    *head = newNode;
}

void giveTakeMenu(char username[50]) {
    struct Transaction *head = NULL;
    int choice;

    while (1) {
        printf("\n1. Add Give/Take\n2. View Give/Take\n3. Back to Main Menu\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTransaction(&head);
                saveTransactions(head, username);
                break;
            case 2:
                viewTransactions(head);
                break;
            case 3:
                saveTransactions(head, username);
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}
