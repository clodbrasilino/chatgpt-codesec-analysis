#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int length_of_last_word(const char *s, size_t max_len)
{
    int length = 0;
    int last_length = 0;
    size_t i;
    size_t len;

    if (s == NULL || max_len == 0) {
        return 0;
    }

    len = strnlen(s, max_len);

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
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t nread;

    printf("Enter a string: ");
    nread = getline(&buffer, &buffer_size, stdin);
    
    if (nread == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    if (nread > 0 && buffer[nread - 1] == '\n') {
        buffer[nread - 1] = '\0';
        nread--;
    }

    printf("Length of last word: %d\n", length_of_last_word(buffer, (size_t)nread));

    free(buffer);
    return 0;
}