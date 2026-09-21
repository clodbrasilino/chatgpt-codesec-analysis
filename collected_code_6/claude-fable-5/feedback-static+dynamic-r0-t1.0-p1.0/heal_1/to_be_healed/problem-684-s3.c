#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long long count_char_in_repeated(const char *str, char target, unsigned long long total_length)
{
    size_t base_length;
    unsigned long long count_in_base = 0ULL;
    unsigned long long full_repeats;
    unsigned long long remainder;
    unsigned long long total = 0ULL;
    size_t i;

    if (str == NULL) {
        return 0ULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    base_length = strlen(str);
    if (base_length == 0U || total_length == 0ULL) {
        return 0ULL;
    }

    for (i = 0U; i < base_length; i++) {
        if (str[i] == target) {
            count_in_base++;
        }
    }

    full_repeats = total_length / (unsigned long long)base_length;
    remainder = total_length % (unsigned long long)base_length;

    total = full_repeats * count_in_base;

    for (i = 0U; i < (size_t)remainder; i++) {
        if (str[i] == target) {
            total++;
        }
    }

    return total;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char target;
    unsigned long long total_length;
    unsigned long long result;
    size_t len;
    int ch;

    printf("Enter the string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading string input\n");
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
        fprintf(stderr, "Empty string is not allowed\n");
        return EXIT_FAILURE;
    }

    printf("Enter the character to count: ");
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    ch = getchar();
    if (ch == EOF) {
        fprintf(stderr, "Error reading character input\n");
        return EXIT_FAILURE;
    }
    target = (char)ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    printf("Enter the total length of the repeated string: ");
    if (scanf("%llu", &total_length) != 1) {
        fprintf(stderr, "Error reading length input\n");
        return EXIT_FAILURE;
    }

    result = count_char_in_repeated(buffer, target, total_length);
    printf("The character '%c' occurs %llu times in the first %llu characters of the repeated string.\n",
           target, result, total_length);

    return EXIT_SUCCESS;
}