#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *add_spaces(const char *input)
{
    if (input == NULL) {
        return NULL;
    }

    const char *p = input;
    size_t space_cnt = 0;

    while (*p) {
        if (isupper((unsigned char)*p) && p != input) {
            space_cnt++;
        }
        p++;
    }

    size_t len = (size_t)(p - input);

    if (len > (size_t)-1 - space_cnt) {
        return NULL;
    }

    size_t total = len + space_cnt;
    char *result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (input[i] != '\0') {
        if (isupper((unsigned char)input[i]) && i != 0) {
            if (j + 1 >= total) {
                free(result);
                return NULL;
            }
            result[j++] = ' ';
        }
        result[j++] = input[i++];
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *input = "HelloWorldThisIsATest";
    char *spaced = add_spaces(input);

    if (spaced == NULL) {
        fprintf(stderr, "Error processing input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", spaced);
    free(spaced);
    return EXIT_SUCCESS;
}