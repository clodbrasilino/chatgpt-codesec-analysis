#include <stdio.h>
#include <string.h>

int match_words(char *list[], int size, char start_letter) {
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (list[i][0] == start_letter && list[i][strlen(list[i]) - 1] == '\0') {
            for (int j = i + 1; j < size; j++) {
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                if (list[j][0] == start_letter && list[j][strlen(list[j]) - 1] == '\0' && strcmp(list[i], list[j]) != 0) {
                    printf("Match: %s and %s\n", list[i], list[j]);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    char *words[] = {"apple", "banana", "peach", "pear", "plum", "orange"};
    int count = sizeof(words) / sizeof(words[0]);

    if (match_words(words, count, 'p')) {
        printf("Words matching the criteria found.\n");
    } else {
        printf("No words matching the criteria found.\n");
    }

    return 0;
}