#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

static void reverse_range(char *str, size_t start, size_t end)
{
    while (start < end) {
        char tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
        start++;
        end--;
    }
}

static int reverse_words(char *str, size_t max_len)
{
    size_t len;
    size_t i;

    if (str == NULL || max_len == 0) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == max_len) {
        return -1;
    }
    if (len == 0) {
        return 0;
    }

    reverse_range(str, 0, len - 1);

    i = 0;
    while (i < len) {
        while (i < len && str[i] == ' ') {
            i++;
        }
        if (i >= len) {
            break;
        }
        {
            size_t word_start = i;
            while (i < len && str[i] != ' ') {
                i++;
            }
            reverse_range(str, word_start, i - 1);
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char *newline;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    if (reverse_words(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Failed to reverse words\n");
        return EXIT_FAILURE;
    }

    printf("Reversed: %s\n", buffer);

    return EXIT_SUCCESS;
}