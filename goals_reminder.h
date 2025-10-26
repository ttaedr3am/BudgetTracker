#ifndef GOALS_REMINDERS_H
#define GOALS_REMINDERS_H

// ==== STRUCTURES ====

// structure for saving goals
struct Goal {
    char name[50];
    float target;
    float saved;
    char deadline[15];  // e.g., "30/11/2025"
    struct Goal *next;
};

// structure for reminders
struct Reminder {
    char message[100];
    char date[15];
    struct Reminder *next;
};

// ==== FUNCTION DECLARATIONS ====
void addGoal(struct Goal **head);
void updateGoal(struct Goal *head);
void viewGoals(struct Goal *head);
void saveGoalsToFile(struct Goal *head, const char *username);
void loadGoalsFromFile(struct Goal **head, const char *username);

void addReminder(struct Reminder **head);
void viewReminders(struct Reminder *head);
void checkReminders(struct Reminder *head, const char *todayDate);
void saveRemindersToFile(struct Reminder *head, const char *username);
void loadRemindersFromFile(struct Reminder **head, const char *username);

#endif
