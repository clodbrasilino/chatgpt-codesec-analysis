#include <stdio.h>
#include <string.h>
#include <limits.h>

int most_common_chars(const char *text, size_t text_len, unsigned char *out_chars, unsigned long *out_counts, size_t max_out)
{
    if (text == NULL || out_chars == NULL || out_counts == NULL || max_out == 0)
        return -1;

    if (text_len == 0)
        return 0;

    unsigned long counts[UCHAR_MAX + 1] = {0};

    for (size_t i = 0; i < text_len; i++)
        counts[(unsigned char)text[i]]++;

    unsigned long max_count = 0;
    for (unsigned i = 0; i <= UCHAR_MAX; i++)
        if (counts[i] > max_count)
            max_count = counts[i];

    size_t result_count = 0;
    for (unsigned i = 0; i <= UCHAR_MAX && result_count < max_out; i++) {
        if (counts[i] == max_count) {
            out_chars[result_count] = (unsigned char)i;
            out_counts[result_count] = counts[i];
            result_count++;
        }
    }

    return (int)result_count;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char chars[UCHAR_MAX + 1];
    unsigned long counts[UCHAR_MAX + 1];

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(argv[1]);
    int result = most_common_chars(argv[1], len, chars, counts, UCHAR_MAX + 1);
    if (result < 0) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    if (result == 0) {
        printf("No characters found.\n");
        return 0;
    }

    printf("Most common character(s):\n");
    for (int i = 0; i < result; i++)
        printf("'%c' (0x%02x): %lu\n", chars[i], (unsigned int)chars[i], counts[i]);

    return 0;
}