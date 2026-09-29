#include <stdio.h>
#include <string.h>

void replace_chars(char *str, const char *find, const char *replace);

void replace_chars(char *str, const char *find, const char *replace)
{
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t find_len = strlen(find);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t replace_len = strlen(replace);
    char *pos = str;

    while (*pos != '\0') {
        if (strncmp(pos, find, find_len) == 0) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            memmove(pos + replace_len, pos + find_len, strlen(pos + find_len) + 1);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(pos, replace, replace_len);
            pos += replace_len;
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
    replace_chars(text, "hello", "hi");
    printf("%s\n", text);

    replace_chars(text, "hi", "goodbye");
    printf("%s\n", text);

    replace_chars(text, " ", "_");
    printf("%s\n", text);

    return 0;
}