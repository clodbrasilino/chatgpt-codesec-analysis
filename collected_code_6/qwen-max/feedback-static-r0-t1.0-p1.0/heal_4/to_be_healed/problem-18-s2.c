#include <stdio.h>
#include <string.h>

void remove_chars(char *str1, const char *str2, size_t len1) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char result[100] = "";
    int j;
    for (int i = 0; i < len1 && str1[i] != '\0'; i++) {
        for (j = 0; str2[j] != '\0' && str1[i] != str2[j]; j++);
        if (str2[j] == '\0') {
            /* Possible weaknesses found:
             * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
             */
            strncat(result, &str1[i], 1);
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(str1, result, len1);
    str1[len1 - 1] = '\0';
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[100] = "hello world";
    const char *str2 = "lo";
    remove_chars(str1, str2, sizeof(str1));
    printf("%s\n", str1);
    return 0;
}