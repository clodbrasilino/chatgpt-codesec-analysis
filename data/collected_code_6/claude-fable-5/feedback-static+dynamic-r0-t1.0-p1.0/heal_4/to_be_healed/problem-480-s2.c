#include <stdio.h>
#include <string.h>
#include <limits.h>

int max_occurring_char(const char *str, char *result)
{
    size_t counts[UCHAR_MAX + 1] = {0};
    size_t max_count = 0;
    size_t i;
    unsigned char best = 0;
    int found = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        counts[c]++;
        if (counts[c] > max_count) {
            max_count = counts[c];
            best = c;
            found = 1;
        }
    }

    if (!found) {
        return -1;
    }

    *result = (char)best;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char result;

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (max_occurring_char(buffer, &result) != 0) {
        fprintf(stderr, "No characters found in input\n");
        return 1;
    }

    printf("Maximum occurring character: %c\n", result);
    return 0;
}