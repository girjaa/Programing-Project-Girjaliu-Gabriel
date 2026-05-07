#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

struct cards {
    char card_number[22];
    char cardholder_name[50];
    char expiration_date[10];
    int card_views;
} card[100];

int i = 0;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    printf("\n" YELLOW "Press Enter to return to menu..." RESET);
    getchar();
    getchar();
}

void sort() {
    for (int j = 0; j < i - 1; j++) {
        for (int k = 0; k < i - j - 1; k++) {
            if (card[k].card_views < card[k+1].card_views) {
                struct cards temp = card[k];
                card[k] = card[k+1];
                card[k+1] = temp;
            }
        }
    }
}

void header(char *title) {
    clearScreen();
    printf(CYAN "===============================\n" RESET);
    printf(CYAN "   %s\n" RESET, title);
    printf(CYAN "===============================\n" RESET);
}

void add() {
    header("ADD NEW CARD");
    if (i >= 100) {
        printf(RED "Wallet is full!\n" RESET);
        return;
    }
    getchar();
    printf(WHITE "Input card number: " RESET);
    fgets(card[i].card_number, sizeof(card[i].card_number), stdin);
    card[i].card_number[strcspn(card[i].card_number, "\n")] = 0;

    printf(WHITE "Input cardholder name: " RESET);
    fgets(card[i].cardholder_name, sizeof(card[i].cardholder_name), stdin);
    card[i].cardholder_name[strcspn(card[i].cardholder_name, "\n")] = 0;

    printf(WHITE "Input expiration date: " RESET);
    fgets(card[i].expiration_date, sizeof(card[i].expiration_date), stdin);
    card[i].expiration_date[strcspn(card[i].expiration_date, "\n")] = 0;

    card[i].card_views = 0;
    i++;
    printf(GREEN "\nCard added successfully!\n" RESET);
}

void display() {
    sort();
    header("WALLET CONTENTS (Sorted by Views)");
    if (i == 0) {
        printf(RED "Wallet is empty!\n" RESET);
        return;
    }
    for (int j = 0; j < i; j++) {
        printf(WHITE "%d. " RESET CYAN "%s " RESET YELLOW "[%d views]\n" RESET,
               j + 1, card[j].cardholder_name, card[j].card_views);
    }

    int view;
    printf(WHITE "\nSelect a card number to view details (0 to go back): " RESET);
    scanf("%d", &view);

    if (view > 0 && view <= i) {
        card[view-1].card_views++;

        header("CARD DETAILS");
        printf(WHITE "Card Number: " RESET GREEN "%s\n" RESET, card[view-1].card_number);
        printf(WHITE "Cardholder:  " RESET GREEN "%s\n" RESET, card[view-1].cardholder_name);
        printf(WHITE "Expiration:  " RESET GREEN "%s\n" RESET, card[view-1].expiration_date);
        printf(WHITE "Total Views: " RESET GREEN "%d\n" RESET, card[view-1].card_views);
    } else if (view != 0) {
        printf(RED "Invalid selection!\n" RESET);
    }
}

void delete_card() {
    header("DELETE A CARD");
    if (i == 0) {
        printf(RED "Wallet is empty!\n" RESET);
        return;
    }
    int del;
    printf(WHITE "Enter the list number to delete: " RESET);
    scanf("%d", &del);

    if (del > 0 && del <= i) {
        for (int j = del - 1; j < i - 1; j++) {
            card[j] = card[j + 1];
        }
        i--;
        printf(GREEN "Card deleted successfully!\n" RESET);
    } else {
        printf(RED "Invalid selection!\n" RESET);
    }
}

int main() {
    FILE *file = fopen("cards.txt", "r");
    if (file == NULL) {
        printf(RED "Unable to open cards.txt\n" RESET);
        return EXIT_FAILURE;
    }

    char line[100];
    while (i < 100) {
        if (fgets(line, sizeof(line), file) == NULL) break;
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) continue;
        strncpy(card[i].card_number, line, sizeof(card[i].card_number) - 1);

        if (fgets(line, sizeof(line), file) == NULL) break;
        line[strcspn(line, "\n")] = 0;
        strncpy(card[i].cardholder_name, line, sizeof(card[i].cardholder_name) - 1);

        if (fgets(line, sizeof(line), file) == NULL) break;
        line[strcspn(line, "\n")] = 0;
        strncpy(card[i].expiration_date, line, sizeof(card[i].expiration_date) - 1);

        if (fgets(line, sizeof(line), file) == NULL) break;
        card[i].card_views = atoi(line);

        i++;
        fgets(line, sizeof(line), file);
    }

    fclose(file);
    printf(GREEN "Loaded %d card(s) from cards.txt.\n" RESET, i);
    pause();

    int option;
    do {
        clearScreen();
        printf(CYAN "\nELECTRONIC WALLET SYSTEM\n" RESET);
        printf(CYAN "-----------------------\n" RESET);
        printf(GREEN "1" RESET WHITE " - Add new card\n" RESET);
        printf(GREEN "2" RESET WHITE " - View cards\n" RESET);
        printf(GREEN "3" RESET WHITE " - Delete card\n" RESET);
        printf(RED   "0" RESET WHITE " - Exit\n" RESET);
        printf(CYAN "-----------------------\n" RESET);
        printf(YELLOW "Enter option: " RESET);

        if (scanf("%d", &option) != 1) {
            while(getchar() != '\n');
            continue;
        }

        switch(option) {
            case 1: add();         break;
            case 2: display();     break;
            case 3: delete_card(); break;
            case 0: printf(RED "Exiting program...\n" RESET); break;
            default:
                printf(RED "Invalid option!\n" RESET);
        }

        if (option >= 1 && option <= 3) {
            FILE *out = fopen("cards.txt", "w");
            if (out == NULL) {
                printf(RED "Unable to save cards.txt\n" RESET);
            } else {
                for (int j = 0; j < i; j++) {
                    fprintf(out, "%s\n", card[j].card_number);
                    fprintf(out, "%s\n", card[j].cardholder_name);
                    fprintf(out, "%s\n", card[j].expiration_date);
                    fprintf(out, "%d\n", card[j].card_views);
                    fprintf(out, "\n");
                }
                fclose(out);
                printf(GREEN "\nData saved to cards.txt.\n" RESET);
            }
            pause();
        }

    } while(option != 0);

    return 0;
}