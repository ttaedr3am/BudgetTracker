#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "goals_reminders.h"

// ================= GOAL MANAGEMENT =================

// Add a new goal
void addGoal(struct Goal **head) {
    struct Goal *newGoal = (struct Goal *)malloc(sizeof(struct Goal));
    printf("Enter goal name: ");
    scanf(" %[^\n]", newGoal->name);
    printf("Enter target amount: ");
    scanf("%f", &newGoal->target);
    printf("Enter deadline (DD/MM/YYYY): ");
    scanf("%s", newGoal->deadline);
    newGoal->saved = 0;
    newGoal->next = *head;
    *head = newGoal;
    printf("✅ Goal '%s' added successfully!\n", newGoal->name);
}

// Update progress on an existing goal
void updateGoal(struct Goal *head) {
    if (!head) {
        printf("No goals available.\n");
        return;
    }

    char name[50];
    printf("Enter goal name to update: ");
    scanf(" %[^\n]", name);

    struct Goal *temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            float add;
            printf("Enter amount to add to your goal savings: ");
            scanf("%f", &add);
            temp->saved += add;

            if (temp->saved >= temp->target) {
                printf("🎉 Congratulations! Goal '%s' achieved!\n", temp->name);
            } else {
                printf("Progress updated. %.2f remaining to reach target.\n",
                       temp->target - temp->saved);
            }
            return;
        }
        temp = temp->next;
    }
    printf("Goal not found.\n");
}

// Display all goals
void viewGoals(struct Goal *head) {
    if (!head) {
        printf("No goals set.\n");
        return;
    }

    printf("\n==== Your Saving Goals ====\n");
    while (head) {
        printf("Goal: %s\n", head->name);
        printf("Target: ₹%.2f | Saved: ₹%.2f | Remaining: ₹%.2f\n",
               head->target, head->saved, head->target - head->saved);
        printf("Deadline: %s\n", head->deadline);
        printf("----------------------------\n");
        head = head->next;
    }
}

// Save goals to file
void saveGoalsToFile(struct Goal *head, const char *username) {
    char filename[50];
    sprintf(filename, "data/goals_%s.txt", username);
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    while (head) {
        fprintf(fp, "%s %.2f %.2f %s\n",
                head->name, head->target, head->saved, head->deadline);
        head = head->next;
    }
    fclose(fp);
}

// Load goals from file
void loadGoalsFromFile(struct Goal **head, const char *username) {
    char filename[50];
    sprintf(filename, "data/goals_%s.txt", username);
    FILE *fp = fopen(filename, "r");
    if (!fp) return;

    struct Goal temp;
    while (fscanf(fp, "%s %f %f %s",
                  temp.name, &temp.target, &temp.saved, temp.deadline) != EOF) {
        struct Goal *newGoal = (struct Goal *)malloc(sizeof(struct Goal));
        *newGoal = temp;
        newGoal->next = *head;
        *head = newGoal;
    }
    fclose(fp);
}

// ================= REMINDERS =================

// Add a new reminder
void addReminder(struct Reminder **head) {
    struct Reminder *newR = (struct Reminder *)malloc(sizeof(struct Reminder));
    printf("Enter reminder message: ");
    scanf(" %[^\n]", newR->message);
    printf("Enter reminder date (DD/MM/YYYY): ");
    scanf("%s", newR->date);
    newR->next = *head;
    *head = newR;
    printf("✅ Reminder added successfully!\n");
}

// View all reminders
void viewReminders(struct Reminder *head) {
    if (!head) {
        printf("No reminders available.\n");
        return;
    }

    printf("\n==== Your Reminders ====\n");
    while (head) {
        printf("%s  ->  %s\n", head->date, head->message);
        head = head->next;
    }
}

// Check reminders for a specific date
void checkReminders(struct Reminder *head, const char *todayDate) {
    int found = 0;
    while (head) {
        if (strcmp(head->date, todayDate) == 0) {
            printf("🔔 Reminder for today: %s\n", head->message);
            found = 1;
        }
        head = head->next;
    }
    if (!found) printf("No reminders for today.\n");
}

// Save reminders to file
void saveRemindersToFile(struct Reminder *head, const char *username) {
    char filename[50];
    sprintf(filename, "data/reminders_%s.txt", username);
    FILE *fp = fopen(filename, "w");
    if (!fp) return;
    while (head) {
        fprintf(fp, "%s|%s\n", head->date, head->message);
        head = head->next;
    }
    fclose(fp);
}

// Load reminders from file
void loadRemindersFromFile(struct Reminder **head, const char *username) {
    char filename[50];
    sprintf(filename, "data/reminders_%s.txt", username);
    FILE *fp = fopen(filename, "r");
    if (!fp) return;

    struct Reminder temp;
    char line[150];
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^\n]", temp.date, temp.message);
        struct Reminder *newR = (struct Reminder *)malloc(sizeof(struct Reminder));
        *newR = temp;
        newR->next = *head;
        *head = newR;
    }
    fclose(fp);
}
