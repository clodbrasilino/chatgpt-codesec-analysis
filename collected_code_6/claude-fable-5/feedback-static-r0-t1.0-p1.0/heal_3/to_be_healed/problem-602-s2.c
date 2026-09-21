#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int find_first_repeated(const char *str, size_t max_len, char *result)
{
    int seen[256] = {0};
    size_t i;
    size_t len;

    if (str == NULL || result == NULL) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len == max_len) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
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
    char buffer[BUFFER_SIZE];
    char repeated;
    int status;
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    status = find_first_repeated(buffer, sizeof(buffer), &repeated);
    if (status == 0) {
        printf("First repeated character: %c\n", repeated);
    } else if (status == 1) {
        printf("No repeated character found\n");
    } else {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    return 0;
}