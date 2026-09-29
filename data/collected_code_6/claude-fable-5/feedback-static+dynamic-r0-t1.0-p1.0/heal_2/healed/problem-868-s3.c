#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096U

size_t length_of_last_word(const char *s)
{
    size_t len;
    size_t end;
    size_t count;

    if (s == NULL) {
        return 0U;
    }

    len = strnlen(s, MAX_INPUT_LEN);
    if (len == 0U) {
        return 0U;
    }

    end = len;
    while (end > 0U && isspace((unsigned char)s[end - 1U])) {
        end--;
    }

    count = 0U;
    while (end > 0U && !isspace((unsigned char)s[end - 1U])) {
        count++;
        end--;
    }

    return count;
}

int main(void)
{
    char buffer[MAX_INPUT_LEN];
    size_t result;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        buffer[0] = '\0';
    }

    result = length_of_last_word(buffer);

    if (printf("%zu\n", result) < 0) {
        return 1;
    }

    return 0;
}