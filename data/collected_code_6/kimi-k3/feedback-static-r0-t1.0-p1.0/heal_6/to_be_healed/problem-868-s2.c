#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

int length_of_last_word(const char *s, size_t max_len)
{
    int length = 0;
    int last_length = 0;
    size_t i;
    size_t len = 0;

    if (s == NULL || max_len == 0) {
        return 0;
    }

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    for (i = 0; i < len; i++) {
        if (isalpha((unsigned char)s[i])) {
            if (length < INT32_MAX) {
                length++;
            }
        } else {
            if (length > 0) {
                last_length = length;
            }
            length = 0;
        }
    }

    if (length > 0) {
        last_length = length;
    }

    return last_length;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strcspn(buffer, "\n");
    if (len < sizeof(buffer)) {
        buffer[len] = '\0';
    } else {
        buffer[sizeof(buffer) - 1] = '\0';
    }

    printf("Length of last word: %d\n", length_of_last_word(buffer, sizeof(buffer)));

    return 0;
}