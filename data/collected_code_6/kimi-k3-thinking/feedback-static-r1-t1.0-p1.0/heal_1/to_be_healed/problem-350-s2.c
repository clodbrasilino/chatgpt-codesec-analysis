#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_SET_SIZE 256

static char find_most_frequent_char(const char *str)
{
    size_t freq[CHAR_SET_SIZE] = {0};
    char most_frequent = str[0];
    size_t max_count = 0;
    size_t i;

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        freq[c]++;
        if (freq[c] > max_count) {
            max_count = freq[c];
            most_frequent = (char)c;
        }
    }
    return most_frequent;
}

char *minimize_string(const char *str)
{
    char *result;
    char target;
    size_t len;
    size_t i;
    size_t j = 0;

    if (str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (len == 0) {
        result[0] = '\0';
        return result;
    }

    target = find_most_frequent_char(str);

    for (i = 0; i < len; i++) {
        if (str[i] != target) {
            result[j] = str[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    char *minimized;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (buffer[0] == '\0') {
        fprintf(stderr, "Empty string provided\n");
        return EXIT_FAILURE;
    }

    minimized = minimize_string(buffer);
    if (minimized == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Minimized string: %s\n", minimized);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("Original length: %zu\n", strlen(buffer));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("Minimized length: %zu\n", strlen(minimized));

    free(minimized);
    minimized = NULL;

    return EXIT_SUCCESS;
}