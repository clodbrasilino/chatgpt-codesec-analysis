#include <stdio.h>
#include <string.h>
#include <regex.h>

int regex_search(char *base, char *search) {
    regex_t regex;
    int reti;

    reti = regcomp(&regex, search, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    reti = regexec(&regex, base, 0, NULL, 0);
    if (!reti) {
        return 0;
    } else if (reti == REG_NOMATCH) {
        return 1;
    } else {
        regerror(reti, &regex, NULL, sizeof(NULL));
        fprintf(stderr, "Regex match failed: %s\n", NULL);
        return 1;
    }

    regfree(&regex);
    return 0;
}

int main() {
    char base[100];
    char search[50];

    printf("Enter the base string: ");
    fgets(base, sizeof(base), stdin);
    base[strlen(base) - 1] = '\0';

    printf("Enter the search string: ");
    fgets(search, sizeof(search), stdin);
    search[strlen(search) - 1] = '\0';

    int result = regex_search(base, search);

    if (result == 0) {
        printf("Match found.\n");
    } else {
        printf("Match not found.\n");
    }

    return 0;
}