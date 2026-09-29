#include <stdio.h>
#include <string.h>

size_t safe_strlen(const char *str, size_t max_len)
{
    size_t len = 0;
    if (str == NULL || max_len == 0) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int replace_chars(char *str, size_t str_size, const char *find, const char *replace)
{
    if (str == NULL || find == NULL || replace == NULL || str_size == 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t find_len = strlen(find);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t replace_len = strlen(replace);

    if (find_len == 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
    if (str_len >= str_size) {
        return -1;
    }

    char *pos = str;
    size_t pos_index = 0;

    while (pos_index < str_len && *pos != '\0') {
        if (pos_index + find_len <= str_len && strncmp(pos, find, find_len) == 0) {
            size_t remaining_len = str_len - (pos_index + find_len);

            if (pos_index + replace_len + remaining_len >= str_size) {
                return -1;
            }

            if (replace_len != find_len) {
                memmove(pos + replace_len, pos + find_len, remaining_len + 1);
                str_len = pos_index + replace_len + remaining_len;
            }

            if (replace_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(pos, replace, replace_len);
            }

            pos += replace_len;
            pos_index += replace_len;
        } else {
            pos++;
            pos_index++;
        }
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char text[256] = "hello world, hello universe";

    if (replace_chars(text, sizeof(text), "hello", "hi") == 0) {
        printf("%s\n", text);
    } else {
        printf("Error: replacement failed\n");
    }

    if (replace_chars(text, sizeof(text), "hi", "goodbye") == 0) {
        printf("%s\n", text);
    } else {
        printf("Error: replacement failed\n");
    }

    if (replace_chars(text, sizeof(text), " ", "_") == 0) {
        printf("%s\n", text);
    } else {
        printf("Error: replacement failed\n");
    }

    return 0;
}