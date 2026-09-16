#include <stdio.h>
#include <string.h>

int count_matching_positions(const char *str)
{
    int count = 0;
    size_t len;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    len = strlen(str);

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
    char buffer[256];
    int result;

    printf("Enter a string: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = count_matching_positions(buffer);

    printf("Number of characters at same position as in alphabet: %d\n", result);

    return 0;
}