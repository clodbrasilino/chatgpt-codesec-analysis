#include <stdio.h>
#include <string.h>
#include <stddef.h>

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
    while ((end > 0U) && (s[end - 1U] == ' ')) {
        end--;
    }

    count = 0U;
    while ((end > 0U) && (s[end - 1U] != ' ')) {
        count++;
        end--;
    }

    return count;
}

int main(void)
{
    const char *test1 = "Hello World";
    const char *test2 = "   fly me   to   the moon  ";
    const char *test3 = "luffy is still joyboy";
    const char *test4 = "";
    const char *test5 = "     ";

    printf("Length of last word in \"%s\": %zu\n", test1, length_of_last_word(test1));
    printf("Length of last word in \"%s\": %zu\n", test2, length_of_last_word(test2));
    printf("Length of last word in \"%s\": %zu\n", test3, length_of_last_word(test3));
    printf("Length of last word in \"%s\": %zu\n", test4, length_of_last_word(test4));
    printf("Length of last word in \"%s\": %zu\n", test5, length_of_last_word(test5));

    return 0;
}