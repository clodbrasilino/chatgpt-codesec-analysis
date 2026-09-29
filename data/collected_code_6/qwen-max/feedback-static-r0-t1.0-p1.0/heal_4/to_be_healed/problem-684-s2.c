#include <stdio.h>
#include <string.h>

int count_character_in_repeated_string(const char *s, int n, char c) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = (s != NULL && s[0] != '\0') ? strlen(s) : 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (i < len && s[i] == c) {
            count++;
        } else if (i >= len && s[i % len] == c) {
            count++;
        }
    }
    return count;
}

int main() {
    const char *s = "abc";
    int n = 10;
    char c = 'a';
    int result = count_character_in_repeated_string(s, n, c);
    printf("Character '%c' appears %d times in the repeated string.\n", c, result);
    return 0;
}