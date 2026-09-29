#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BUFFER_SIZE 256

static unsigned long long count_char_in_repeated(const char *str, size_t max_len, char target, unsigned long long total_length)
{
    size_t base_length;
    unsigned long long count_in_base = 0ULL;
    unsigned long long full_repeats;
    unsigned long long remainder;
    unsigned long long total;
    size_t i;

    if (str == NULL) {
        return 0ULL;
    }

    base_length = strnlen(str, max_len);
    if (base_length == 0U || base_length >= max_len || total_length == 0ULL) {
        return 0ULL;
    }

    for (i = 0U; i < base_length; i++) {
        if (str[i] == target) {
            count_in_base++;
        }
    }

    full_repeats = total_length / (unsigned long long)base_length;
    remainder = total_length % (unsigned long long)base_length;

    if (count_in_base != 0ULL && full_repeats > ULLONG_MAX / count_in_base) {
        return 0ULL;
    }

    total = full_repeats * count_in_base;

    for (i = 0U; i < (size_t)remainder; i++) {
        if (str[i] == target) {
            if (total == ULLONG_MAX) {
                return 0ULL;
            }
            total++;
        }
    }

    return total;
}

static void discard_remaining_input(void)
{
    int ch;
    unsigned long guard = 0UL;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        guard++;
        if (guard > 1000000UL) {
            break;
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char target;
    unsigned long long total_length;
    unsigned long long result;
    size_t len;
    int ch;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter the string: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading string input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    } else if (len == sizeof(buffer) - 1U) {
        discard_remaining_input();
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

    if (ch != '\n') {
        discard_remaining_input();
    }

    printf("Enter the total length of the repeated string: ");
    if (scanf("%llu", &total_length) != 1) {
        fprintf(stderr, "Error reading length input\n");
        return EXIT_FAILURE;
    }

    result = count_char_in_repeated(buffer, sizeof(buffer), target, total_length);
    printf("The character '%c' occurs %llu times in the first %llu characters of the repeated string.\n",
           target, result, total_length);

    return EXIT_SUCCESS;
}