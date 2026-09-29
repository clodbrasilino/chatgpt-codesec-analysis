#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define BUFFER_SIZE 256

static void reverse_segment(char *start, char *end)
{
    if (start == NULL || end == NULL || start >= end) {
        return;
    }
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

static int reverse_words(char *str, size_t max_len)
{
    if (str == NULL || max_len == 0) {
        return -1;
    }

    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }

    if (len >= max_len) {
        return -1;
    }

    reverse_segment(str, str + len - 1);

    char *word_start = str;
    char *current = str;
    const char *str_end = str + len;

    while (current < str_end && *current != '\0') {
        if (*current == ' ') {
            if (current > word_start) {
                reverse_segment(word_start, current - 1);
            }
            word_start = current + 1;
        }
        current++;
    }
    
    if (current > word_start) {
        reverse_segment(word_start, current - 1);
    }

    return 0;
}

static bool read_input(char *buffer, size_t buffer_size)
{
    if (buffer == NULL || buffer_size == 0 || buffer_size > INT_MAX) {
        return false;
    }

    if (fgets(buffer, buffer_size, stdin) == NULL) {
        return false;
    }

    size_t len = strnlen(buffer, buffer_size);
    
    if (len == 0) {
        return false;
    }

    if (buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else if (len == buffer_size - 1) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return false;
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE + 1];

    printf("Enter a string: ");
    
    if (!read_input(buffer, sizeof(buffer))) {
        fprintf(stderr, "Error reading input or input too long\n");
        return EXIT_FAILURE;
    }

    if (reverse_words(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Reversed words: %s\n", buffer);

    return EXIT_SUCCESS;
}