#include <stdio.h>
#include <string.h>
#include <stdlib.h> 


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

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
    printf("\nPress " BOLD "Enter" RESET " to return to menu...");
    getchar(); 
    getchar(); 
}

void sort() {
    for(int j = 0; j < i - 1; j++) {
        for(int k = 0; k < i - j - 1; k++) {
            if(card[k].card_views < card[k+1].card_views) {
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
    printf("    " BOLD "%s" RESET "\n", title);
    printf(CYAN "===============================\n" RESET);
}

void add() {
    header("ADD NEW CARD");
    if(i >= 100) {
        printf(RED "Wallet is full!\n" RESET);
        return;
    }

    getchar(); 


    printf("Input " BOLD "Card Number" RESET " (XXXX-XXXX-XXXX-XXXX): ");
    fgets(card[i].card_number, sizeof(card[i].card_number), stdin);
    card[i].card_number[strcspn(card[i].card_number, "\n")] = 0;

    printf("Input " BOLD "Cardholder Full Name" RESET ": ");
    fgets(card[i].cardholder_name, sizeof(card[i].cardholder_name), stdin);
    card[i].cardholder_name[strcspn(card[i].cardholder_name, "\n")] = 0;

    printf("Input " BOLD "Expiration Date" RESET " (MM/YY): ");
    fgets(card[i].expiration_date, sizeof(card[i].expiration_date), stdin);
    card[i].expiration_date[strcspn(card[i].expiration_date, "\n")] = 0;

    card[i].card_views = 0;
    i++;

    printf("\n" GREEN "✅ Card added successfully!" RESET "\n");
}

void display() {
    sort(); 

    header("WALLET CONTENTS (Sorted by Views)");
    if(i == 0) {
        printf(YELLOW "Wallet is empty!" RESET "\n");
        return;
    }

    for(int j = 0; j < i; j++) {
        printf("%d. " BLUE "%s" RESET " [" YELLOW "%d" RESET " views]\n", 
               j + 1, card[j].cardholder_name, card[j].card_views);
    }

    int view;
    printf("\nSelect a card number to view details (" BOLD "0 to go back" RESET "): ");
    if (scanf("%d", &view) != 1) {
        while(getchar() != '\n');
        return;
    }

    if(view > 0 && view <= i) {
        card[view-1].card_views++; 
        
        header("CARD DETAILS");
        printf("Card Number: " CYAN "%s" RESET "\n", card[view-1].card_number);
        printf("Cardholder:  " BOLD "%s" RESET "\n", card[view-1].cardholder_name);
        printf("Expiration:  " YELLOW "%s" RESET "\n", card[view-1].expiration_date);
        printf("Total Views: " GREEN "%d" RESET "\n", card[view-1].card_views);
    } else if (view != 0) {
        printf(RED "Invalid selection!" RESET "\n");
    }
}

void delete_card() {
    header("DELETE A CARD");
    if(i == 0) {
        printf(YELLOW "Wallet is empty!" RESET "\n");
        return;
    }

    int del;
    printf("Enter the " BOLD "list number" RESET " to delete: ");
    scanf("%d", &del);

    if(del > 0 && del <= i) {
        for(int j = del - 1; j < i - 1; j++) {
            card[j] = card[j + 1];
        }
        i--;
        printf(GREEN "Card deleted successfully!" RESET "\n");
    } else {
        printf(RED "Invalid selection!" RESET "\n");
    }
}

int main() {
    int option;

    do {
        clearScreen();
        printf(BLUE "============================\n" RESET);
        printf(BOLD "  ELECTRONIC WALLET SYSTEM\n" RESET);
        printf(BLUE "============================\n" RESET);
        printf(CYAN "1" RESET " - Add new card\n");
        printf(CYAN "2" RESET " - View cards\n");
        printf(CYAN "3" RESET " - Delete card\n");
        printf(RED "0" RESET " - Exit\n");
        printf("----------------------------\n");
        printf("Enter option: ");
        
        if (scanf("%d", &option) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        switch(option) {
            case 1: add(); pause(); break;
            case 2: display(); pause(); break;
            case 3: delete_card(); pause(); break;
            case 0: printf("Exiting program...\n"); break;
            default: 
                printf(RED "Invalid option!" RESET "\n"); 
                pause();
        }
    } while(option != 0);

    return 0;
}
