#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CHAR_SET_SIZE 256

char most_common_char(const char *str, size_t *count)
{
    size_t freq[CHAR_SET_SIZE] = {0};
    size_t i;
    size_t max_count;
    char result;

    if (str == NULL || count == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return '\0';
    }

    if (str[0] == '\0') {
        *count = 0;
        return '\0';
    }

    for (i = 0; str[i] != '\0'; i++) {
        freq[(unsigned char)str[i]]++;
    }

    max_count = 0;
    result = '\0';

    for (i = 0; i < CHAR_SET_SIZE; i++) {
        if (freq[i] > max_count) {
            max_count = freq[i];
            result = (char)i;
        }
    }

    *count = max_count;
    return result;
}

int main(void)
{
    const char *test_string = "hello world, this is a test string!";
    size_t count = 0;
    char most_common;

    most_common = most_common_char(test_string, &count);

    if (count > 0) {
        printf("String: %s\n", test_string);
        printf("Most common character: '%c' (occurred %zu times)\n",
               most_common, count);
    } else {
        printf("The string is empty or invalid.\n");
    }

    return EXIT_SUCCESS;
}