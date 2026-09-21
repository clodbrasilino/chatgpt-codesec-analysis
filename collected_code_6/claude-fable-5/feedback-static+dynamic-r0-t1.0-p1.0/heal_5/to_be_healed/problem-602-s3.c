#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_INPUT_LEN 256

static size_t bounded_strlen(const char *str, size_t maxlen)
{
    size_t i;

    for (i = 0; i < maxlen; i++) {
        if (str[i] == '\0') {
            break;
        }
    }

    return i;
}

int find_first_repeated_char(const char *str, size_t maxlen, char *result)
{
    int seen[UCHAR_MAX + 1] = {0};
    size_t i;
    size_t len;

    if (str == NULL || result == NULL || maxlen == 0) {
        return -1;
    }

    len = bounded_strlen(str, maxlen);

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c] != 0) {
            *result = str[i];
            return 0;
        }
        seen[c] = 1;
    }

    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_INPUT_LEN];
    char repeated = '\0';
    int status;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    status = find_first_repeated_char(buffer, sizeof(buffer), &repeated);

    if (status < 0) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }

    if (status == 0) {
        if (printf("First repeated character: %c\n", repeated) < 0) {
            return 1;
        }
    } else {
        if (printf("No repeated character found\n") < 0) {
            return 1;
        }
    }

    return 0;
}