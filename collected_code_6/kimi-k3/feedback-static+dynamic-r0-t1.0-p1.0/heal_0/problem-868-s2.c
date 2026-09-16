#include <stdio.h>
#include <string.h>
#include <ctype.h>

int length_of_last_word(const char *s)
{
    int length = 0;
    int last_length = 0;
    size_t i;
    size_t len;

    if (s == NULL) {
        return 0;
    }

    len = strlen(s);

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

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    printf("Length of last word: %d\n", length_of_last_word(buffer));

    return 0;
}