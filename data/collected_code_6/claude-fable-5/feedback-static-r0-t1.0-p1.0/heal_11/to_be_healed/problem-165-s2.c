#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

size_t count_position_matches(const char *str, size_t max_len)
{
    size_t count = 0;
    size_t len;
    size_t i;

    if (str == NULL || max_len == 0) {
        return 0;
    }

    len = strnlen(str, max_len);

    for (i = 0; i < len && i < 26; i++) {
        if (str[i] == (char)('a' + i) || str[i] == (char)('A' + i)) {
            count++;
        }
    }

    return count;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t result;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");
    fflush(stdout);

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    result = count_position_matches(buffer, sizeof(buffer));

    printf("Characters at same position as in alphabet: %zu\n", result);

    return EXIT_SUCCESS;
}