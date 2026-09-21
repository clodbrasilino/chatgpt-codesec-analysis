#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int find_first_max_even_word(const char *sentence, char *result, size_t result_size)
{
    size_t i = 0;
    size_t best_start = 0;
    size_t best_len = 0;
    int found = 0;

    if (sentence == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    while (sentence[i] != '\0') {
        while (sentence[i] != '\0' && isspace((unsigned char)sentence[i])) {
            i++;
        }
        if (sentence[i] == '\0') {
            break;
        }
        {
            size_t start = i;
            size_t len = 0;
            while (sentence[i] != '\0' && !isspace((unsigned char)sentence[i])) {
                i++;
                len++;
            }
            if ((len % 2U) == 0U && len > best_len) {
                best_len = len;
                best_start = start;
                found = 1;
            }
        }
    }

    if (found == 0) {
        return -1;
    }

    if (best_len >= result_size) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, &sentence[best_start], best_len);
    result[best_len] = '\0';
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[256];
    int status;

    printf("Enter a sentence: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Input error\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    status = find_first_max_even_word(buffer, result, sizeof(result));
    if (status != 0) {
        printf("No even-length word found\n");
        return EXIT_SUCCESS;
    }

    printf("First maximum length even word: %s\n", result);
    return EXIT_SUCCESS;
}