#include <stdio.h>
#include <string.h>

void replace_chars(char *str, size_t str_size, const char *find, const char *replace);

void replace_chars(char *str, size_t str_size, const char *find, const char *replace)
{
    size_t find_len = strnlen(find, str_size);
    size_t replace_len = strnlen(replace, str_size);
    size_t str_len = strnlen(str, str_size);
    char *pos = str;

    while (*pos != '\0') {
        if (strncmp(pos, find, find_len) == 0) {
            size_t remaining = strnlen(pos + find_len, str_size - (pos + find_len - str)) + 1;

            if ((pos - str) + replace_len + remaining > str_size) {
                break;
            }

            memmove(pos + replace_len, pos + find_len, remaining);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(pos, replace, replace_len);
            pos += replace_len;
            str_len = str_len - find_len + replace_len;
        } else {
            pos++;
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char text[100] = "hello world, hello universe";

    replace_chars(text, sizeof(text), "hello", "hi");
    printf("%s\n", text);

    replace_chars(text, sizeof(text), "hi", "goodbye");
    printf("%s\n", text);

    replace_chars(text, sizeof(text), " ", "_");
    printf("%s\n", text);

    return 0;
}