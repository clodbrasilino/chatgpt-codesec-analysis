#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_WORD_LEN 256

bool is_length_odd(const char *word)
{
    size_t len;

    if (word == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(word);
    return (len % 2U) != 0U;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LEN];
    size_t len;

    printf("Enter a word: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(buffer);
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "No word entered\n");
        return EXIT_FAILURE;
    }

    if (is_length_odd(buffer)) {
        printf("The word \"%s\" has an odd length.\n", buffer);
    } else {
        printf("The word \"%s\" has an even length.\n", buffer);
    }

    return EXIT_SUCCESS;
}