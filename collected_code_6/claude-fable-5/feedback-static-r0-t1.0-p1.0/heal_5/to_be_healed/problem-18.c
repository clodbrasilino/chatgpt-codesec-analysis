#include <stdio.h>
#include <string.h>
#include <limits.h>

#define BUF_SIZE 256

int remove_chars(char *str, const char *mask);
static int read_line(char *buf, size_t size, const char *prompt);

int remove_chars(char *str, const char *mask)
{
    int present[UCHAR_MAX + 1] = {0};
    size_t i;
    size_t j;

    if (str == NULL || mask == NULL) {
        return -1;
    }

    for (i = 0; mask[i] != '\0'; i++) {
        present[(unsigned char)mask[i]] = 1;
    }

    j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (!present[(unsigned char)str[i]]) {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';

    return 0;
}

static int read_line(char *buf, size_t size, const char *prompt)
{
    size_t len;

    if (buf == NULL || size == 0 || size > (size_t)INT_MAX || prompt == NULL) {
        return -1;
    }

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }

    buf[size - 1] = '\0';

    len = strcspn(buf, "\n");
    if (buf[len] == '\n') {
        buf[len] = '\0';
    } else {
        int c;
        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            c = getchar();
        } while (c != '\n' && c != EOF);
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char first[BUF_SIZE];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char second[BUF_SIZE];

    memset(first, 0, sizeof(first));
    memset(second, 0, sizeof(second));

    if (read_line(first, sizeof(first), "Enter first string: ") != 0) {
        fprintf(stderr, "Error reading first string\n");
        return 1;
    }

    if (read_line(second, sizeof(second), "Enter second string: ") != 0) {
        fprintf(stderr, "Error reading second string\n");
        return 1;
    }

    if (remove_chars(first, second) != 0) {
        fprintf(stderr, "Error processing strings\n");
        return 1;
    }

    printf("Result: %s\n", first);

    return 0;
}