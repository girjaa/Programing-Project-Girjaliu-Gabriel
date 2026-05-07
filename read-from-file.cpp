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
    FILE *file = fopen("cards.txt", "r");
    if (file == NULL) {
        perror("Unable to open cards.txt");
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

    printf("Loaded %d card(s) from cards.txt:\n\n", i);
    for (int j = 0; j < i; j++) {
        printf("Card %d:\n", j + 1);
        printf("  Number:     %s\n", card[j].card_number);
        printf("  Cardholder: %s\n", card[j].cardholder_name);
        printf("  Expiration: %s\n", card[j].expiration_date);
        printf("  Views:      %d\n\n", card[j].card_views);
    }

    return 0;
}