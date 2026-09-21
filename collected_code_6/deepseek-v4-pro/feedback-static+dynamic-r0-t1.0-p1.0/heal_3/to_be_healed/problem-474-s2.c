#include <stdio.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len)
{
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

void replace_chars(char *str, size_t str_size, const char *find, const char *replace)
{
    if (str == NULL || find == NULL || replace == NULL || str_size == 0) {
        return;
    }

    size_t find_len = safe_strlen(find, str_size);
    size_t replace_len = safe_strlen(replace, str_size);

    if (find_len == 0) {
        return;
    }

    size_t str_len = safe_strlen(str, str_size);
    char *pos = str;
    size_t pos_index = 0;

    while (pos_index < str_len && *pos != '\0') {
        if (pos_index + find_len <= str_len && strncmp(pos, find, find_len) == 0) {
            size_t remaining_len = safe_strlen(pos + find_len, str_size - (pos_index + find_len));

            if (pos_index + replace_len + remaining_len >= str_size) {
                break;
            }

            if (replace_len != find_len) {
                memmove(pos + replace_len, pos + find_len, remaining_len + 1);
            }

            if (pos_index + replace_len < str_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(pos, replace, replace_len);
            }

            pos += replace_len;
            pos_index += replace_len;
            str_len = safe_strlen(str, str_size);
        } else {
            pos++;
            pos_index++;
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