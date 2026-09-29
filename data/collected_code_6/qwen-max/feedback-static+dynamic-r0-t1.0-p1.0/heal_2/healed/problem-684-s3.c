#include <stdio.h>
#include <string.h>

int count_chars_in_partial(int remaining, const char *s, int slen, char c) {
    int count = 0;
    for (int i = 0; i < remaining; ++i) {
        if (s[i] == c) {
            count++;
        }
    }
    return count;
}

int count_occurrences(const char *s, int n, char c) {
    if (n <= 0 || s == NULL) return 0;
    int count = 0;
    int len = 0;
    while (s[len] != '\0' && (len < n)) {
        if (s[len] == c) {
            count++;
        }
        len++;
    }
    return count * (n / len) + count_chars_in_partial(n % len, s, len, c);
}

int main() {
    const char *s = "aba";
    int n = 10;
    char c = 'a';
    int result = count_occurrences(s, n, c);
    printf("The character '%c' appears %d times in the repeated string.\n", c, result);
    return 0;
}