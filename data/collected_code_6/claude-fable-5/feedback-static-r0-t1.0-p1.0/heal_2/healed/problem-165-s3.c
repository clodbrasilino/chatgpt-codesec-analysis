#include <stdio.h>
#include <string.h>

#define MAX_INPUT_SIZE 256

int count_matching_positions(const char *str, size_t max_len)
{
    int count = 0;
    size_t len;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    len = strnlen(str, max_len);

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (c >= 'a' && c <= 'z') {
            if ((size_t)(c - 'a') == i) {
                count++;
            }
        } else if (c >= 'A' && c <= 'Z') {
            if ((size_t)(c - 'A') == i) {
                count++;
            }
        }
    }

    return count;
}

int main(void)
{
    char buffer[MAX_INPUT_SIZE];
    int result;

    memset(buffer, 0, sizeof(buffer));

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\n")] = '\0';

    result = count_matching_positions(buffer, sizeof(buffer));

    printf("Number of characters at same position as in alphabet: %d\n", result);

    return 0;
}