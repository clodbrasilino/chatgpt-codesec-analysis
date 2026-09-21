#include <stdio.h>
#include <string.h>

void replace_chars(char *str, size_t str_size, const char *find, const char *replace);

void replace_chars(char *str, size_t str_size, const char *find, const char *replace)
{
    if (str == NULL || find == NULL || replace == NULL || str_size == 0) {
        return;
    }

    size_t find_len = strnlen(find, str_size);
    size_t replace_len = strnlen(replace, str_size);
    size_t str_len = strnlen(str, str_size);

    if (find_len == 0 || find_len > str_len) {
        return;
    }

    char *pos = str;

    while (*pos != '\0' && (size_t)(pos - str) < str_size) {
        size_t pos_offset = (size_t)(pos - str);

        if (pos_offset + find_len > str_len) {
            break;
        }

        if (strncmp(pos, find, find_len) == 0) {
            size_t remaining = str_len - pos_offset - find_len;

            if (replace_len > find_len) {
                if (pos_offset + replace_len + remaining >= str_size) {
                    break;
                }
                memmove(pos + replace_len, pos + find_len, remaining + 1);
            } else if (replace_len < find_len) {
                memmove(pos + replace_len, pos + find_len, remaining + 1);
            } else {
                if (replace_len > 0) {
                    memmove(pos + replace_len, pos + find_len, remaining + 1);
                }
            }

            if (replace_len > 0 && pos_offset + replace_len < str_size) {
                if (replace_len <= str_size - pos_offset) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(pos, replace, replace_len);
                }
            }

            pos += replace_len;
            str_len = str_len - find_len + replace_len;
            if (str_len < str_size) {
                str[str_len] = '\0';
            } else {
                str[str_size - 1] = '\0';
            }
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