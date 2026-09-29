#include <stdio.h>
#include <string.h>
#include <ctype.h>

int length_of_last_word(const char *s, size_t max_len)
{
    int length = 0;
    int last_length = 0;
    size_t i;
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }

    while (len < max_len && s[len] != '\0') {
        len++;
    }

    for (i = 0; i < len; i++) {
        if (isalpha((unsigned char)s[i])) {
            length++;
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
    char buffer[1024];
    size_t len;

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    len = strcspn(buffer, "\n");
    buffer[len] = '\0';

    printf("Length of last word: %d\n", length_of_last_word(buffer, sizeof(buffer)));

    return 0;
}