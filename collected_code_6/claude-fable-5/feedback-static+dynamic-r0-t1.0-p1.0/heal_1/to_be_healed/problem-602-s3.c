#include <stdio.h>
#include <string.h>
#include <limits.h>

int find_first_repeated_char(const char *str, char *result)
{
    int seen[UCHAR_MAX + 1] = {0};
    size_t i;
    size_t len;

    if (str == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

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
    char buffer[256];
    char repeated = '\0';
    int status;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    status = find_first_repeated_char(buffer, &repeated);

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