#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void find_words_starting_with_a_or_e(const char *input, const char *result[]) {
    const char *delimiter = " ,.!?;:\n\t";
    char *token, *copy;
    int i = 0;

    if (!input) return;

    copy = strdup(input);
    if (!copy) return;

    token = strtok(copy, delimiter);
    while (token) {
        if (tolower(token[0]) == 'a' || tolower(token[0]) == 'e') {
            result[i++] = token;
        }
        token = strtok(NULL, delimiter);
    }

    free(copy);
}

int main() {
    const char *input = "An example: An apple a day keeps the doctor away. Except every eagle is eager.";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *result[20];
    for (int i = 0; i < 20; i++) {
        result[i] = NULL;
    }

    find_words_starting_with_a_or_e(input, result);

    for (int i = 0; i < 20; i++) {
        if (result[i]) {
            printf("%s\n", result[i]);
        }
    }

    return 0;
}