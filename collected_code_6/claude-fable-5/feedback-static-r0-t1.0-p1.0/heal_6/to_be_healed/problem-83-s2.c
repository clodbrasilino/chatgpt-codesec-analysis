#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256U

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t i;

    for (i = 0U; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
    }
    return i;
}

static int get_added_char(const char *str, size_t max_len, char *result)
{
    unsigned long sum;
    size_t i;
    size_t len;

    if (str == NULL || result == NULL || max_len == 0U) {
        return -1;
    }

    len = bounded_strlen(str, max_len);
    if (len == 0U || len == max_len) {
        return -1;
    }

    sum = 0UL;
    for (i = 0U; i < len; i++) {
        sum += (unsigned long)(unsigned char)str[i];
    }

    *result = (char)((sum % 26UL) + (unsigned long)'a');
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    char result;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = bounded_strlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    }

    if (get_added_char(buffer, sizeof(buffer), &result) != 0) {
        fprintf(stderr, "Invalid or empty input.\n");
        return EXIT_FAILURE;
    }

    printf("Resulting character: %c\n", result);
    return EXIT_SUCCESS;
}