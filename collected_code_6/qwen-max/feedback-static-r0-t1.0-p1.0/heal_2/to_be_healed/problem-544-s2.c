#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *flatten_tuple_list(const char *list[], int len) {
    if (len <= 0) return NULL;
    int total_len = 0;
    for (int i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_len += strlen(list[i]) + 2; // 2 for ", " or space
    }
    --total_len; // Remove the last extra comma or space
    char *result = (char *)malloc(total_len + 1); // +1 for null terminator
    if (result == NULL) return NULL;
    result[0] = '\0';
    for (int i = 0; i < len; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        int pos = strlen(result);
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(result + pos, list[i], total_len - pos);
        if (i < len - 1) {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. Risk is low because the source is a constant string. (risk 1, buffer)
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            strncat(result + pos + strlen(list[i]), ", ", total_len - pos - strlen(list[i]));
        }
    }
    return result;
}

int main() {
    const char *tuple_list[] = {"one", "two", "three"};
    int len = 3;
    char *flat_string = flatten_tuple_list(tuple_list, len);
    if (flat_string != NULL) {
        printf("%s\n", flat_string);
        free(flat_string);
    } else {
        printf("Failed to create flat string\n");
    }
    return 0;
}