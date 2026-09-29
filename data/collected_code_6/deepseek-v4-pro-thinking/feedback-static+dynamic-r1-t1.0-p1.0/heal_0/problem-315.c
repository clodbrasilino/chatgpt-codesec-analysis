#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *find_first_max_even_word(const char *str)
{
    const char *max_start = NULL;
    const char *p;
    size_t max_len = 0;

    if (str == NULL) {
        return NULL;
    }

    p = str;
    while (*p != '\0') {
        while (isspace((unsigned char)*p)) {
            p++;
        }
        if (*p == '\0') {
            break;
        }

        const char *start = p;
        size_t len = 0;
        while (*p != '\0' && !isspace((unsigned char)*p)) {
            p++;
            len++;
        }

        if (len % 2 == 0 && len > max_len) {
            max_len = len;
            max_start = start;
        }
    }

    if (max_start == NULL) {
        return NULL;
    }

    char *result = (char *)malloc(max_len + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, max_start, max_len);
    result[max_len] = '\0';
    return result;
}

int main(void)
{
    const char text[] = "The quick brown fox jumps over the lazy dog";
    char *word = find_first_max_even_word(text);

    if (word != NULL) {
        printf("%s\n", word);
        free(word);
    } else {
        printf("No even word found\n");
    }

    return 0;
}