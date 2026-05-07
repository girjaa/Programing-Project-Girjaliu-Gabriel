#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct cards {
    char card_number[22];
    char cardholder_name[50];
    char expiration_date[10];
    int card_views;
} card[100];

int i = 0;

int main() {
    printf("How many cards do you want to add? ");
    scanf("%d", &i);
    getchar();

    for (int j = 0; j < i; j++) {
        printf("\n--- Card %d ---\n", j + 1);

        printf("Card number: ");
        fgets(card[j].card_number, sizeof(card[j].card_number), stdin);
        card[j].card_number[strcspn(card[j].card_number, "\n")] = 0;

        printf("Cardholder name: ");
        fgets(card[j].cardholder_name, sizeof(card[j].cardholder_name), stdin);
        card[j].cardholder_name[strcspn(card[j].cardholder_name, "\n")] = 0;

        printf("Expiration date: ");
        fgets(card[j].expiration_date, sizeof(card[j].expiration_date), stdin);
        card[j].expiration_date[strcspn(card[j].expiration_date, "\n")] = 0;

        card[j].card_views = 0;
    }

    FILE *out = fopen("cards.txt", "w");
    if (out == NULL) {
        perror("Unable to open cards.txt");
        return EXIT_FAILURE;
    }

    for (int j = 0; j < i; j++) {
        fprintf(out, "%s\n", card[j].card_number);
        fprintf(out, "%s\n", card[j].cardholder_name);
        fprintf(out, "%s\n", card[j].expiration_date);
        fprintf(out, "%d\n", card[j].card_views);
        fprintf(out, "\n");
    }

    fclose(out);
    printf("\n%d card(s) saved to cards.txt.\n", i);

    return 0;
}