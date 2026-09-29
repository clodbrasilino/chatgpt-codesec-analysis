#include <stdio.h>
#include <string.h>

int count_character_in_repeated_string(const char *s, int n, char c) {
    int len = strlen(s);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (s[i % len] == c) {
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