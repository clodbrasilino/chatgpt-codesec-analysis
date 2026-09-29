#include <stdio.h>
#include <string.h>

void replace_chars(char *str, size_t str_size, const char *find, const char *replace);

void replace_chars(char *str, size_t str_size, const char *find, const char *replace)
{
    size_t find_len = strlen(find);
    size_t replace_len = strlen(replace);
    size_t str_len = strlen(str);
    char *pos = str;

    while (*pos != '\0') {
        if (strncmp(pos, find, find_len) == 0) {
            size_t pos_offset = (size_t)(pos - str);
            size_t remaining = str_len - pos_offset - find_len + 1;

            if (pos_offset + replace_len + remaining > str_size) {
                break;
            }

            memmove(pos + replace_len, pos + find_len, remaining);
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
    char text[100] = "hello world, hello universe";

    replace_chars(text, sizeof(text), "hello", "hi");
    printf("%s\n", text);

    replace_chars(text, sizeof(text), "hi", "goodbye");
    printf("%s\n", text);

    replace_chars(text, sizeof(text), " ", "_");
    printf("%s\n", text);

    return 0;
}