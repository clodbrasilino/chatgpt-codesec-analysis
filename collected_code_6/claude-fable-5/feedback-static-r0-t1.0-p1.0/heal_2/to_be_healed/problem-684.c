#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1024

unsigned long long count_char_in_repeated_string(const char *str, char target, unsigned long long total_length)
{
    size_t str_len;
    unsigned long long count_in_one;
    unsigned long long full_repeats;
    unsigned long long remainder;
    unsigned long long total_count;
    size_t i;

    if (str == NULL) {
        return 0ULL;
    }

    str_len = strnlen(str, (size_t)MAX_INPUT);
    if (str_len == 0U || total_length == 0ULL) {
        return 0ULL;
    }

    count_in_one = 0ULL;
    for (i = 0U; i < str_len; i++) {
        if (str[i] == target) {
            count_in_one++;
        }
    }

    full_repeats = total_length / (unsigned long long)str_len;
    remainder = total_length % (unsigned long long)str_len;

    if (count_in_one != 0ULL && full_repeats > (~0ULL) / count_in_one) {
        return ~0ULL;
    }

    total_count = full_repeats * count_in_one;

    for (i = 0U; i < (size_t)remainder && i < str_len; i++) {
        if (str[i] == target) {
            total_count++;
        }
    }

    return total_count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT];
    char target;
    unsigned long long total_length;
    unsigned long long result;
    size_t len;
    int ch;

    printf("Enter the string: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading string input\n");
        return EXIT_FAILURE;
    }
    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
        len--;
    }

    if (len == 0U) {
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

    result = count_char_in_repeated_string(buffer, target, total_length);

    printf("The character '%c' occurs %llu times in the first %llu characters\n",
           target, result, total_length);

    return EXIT_SUCCESS;
}