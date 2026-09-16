#include <stdio.h>
#include <stddef.h>

size_t length_of_last_word(const char *s)
{
    size_t len = 0;
    size_t i = 0;
    size_t end = 0;

    if (s == NULL) {
        return 0;
    }

    while (s[i] != '\0') {
        i++;
    }

    if (i == 0) {
        return 0;
    }

    end = i;
    while (end > 0 && s[end - 1] == ' ') {
        end--;
    }

    while (end > 0 && s[end - 1] != ' ') {
        len++;
        end--;
    }

    return len;
}

int main(void)
{
    const char *test1 = "Hello World";
    const char *test2 = "   fly me   to   the moon  ";
    const char *test3 = "luffy is still joyboy";
    const char *test4 = "";
    const char *test5 = "   ";

    printf("%zu\n", length_of_last_word(test1));
    printf("%zu\n", length_of_last_word(test2));
    printf("%zu\n", length_of_last_word(test3));
    printf("%zu\n", length_of_last_word(test4));
    printf("%zu\n", length_of_last_word(test5));
    printf("%zu\n", length_of_last_word(NULL));

    return 0;
}