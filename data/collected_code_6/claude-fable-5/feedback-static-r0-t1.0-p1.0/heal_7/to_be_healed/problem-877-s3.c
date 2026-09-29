#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256U

static int compare_chars(const void *a, const void *b)
{
    unsigned char ca = *(const unsigned char *)a;
    unsigned char cb = *(const unsigned char *)b;

    if (ca < cb) {
        return -1;
    }
    if (ca > cb) {
        return 1;
    }
    return 0;
}

static int sort_string(char *str, size_t max_len)
{
    size_t len;

    if ((str == NULL) || (max_len == 0U)) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        return -1;
    }

    if (len > 1U) {
        qsort(str, len, sizeof(char), compare_chars);
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if ((len > 0U) && (buffer[len - 1U] == '\n')) {
        buffer[len - 1U] = '\0';
    }

    if (sort_string(buffer, sizeof(buffer)) != 0) {
        fprintf(stderr, "Error sorting string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}