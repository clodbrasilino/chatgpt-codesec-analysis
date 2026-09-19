#include <stdio.h>
#include <string.h>

int count_occurrences(const char *s, int n, char c) {
    if (n <= 0 || s == NULL) return 0;
    int count = 0;
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        if (s[i] == c) {
            count++;
        }
    }
    /* Possible weaknesses found:
     *  previous implicit declaration is here
     *  implicit declaration of function 'count_chars_in_partial' [-Wimplicit-function-declaration]
     *  previous implicit declaration of 'count_chars_in_partial' with type 'int()'
     *  call to undeclared function 'count_chars_in_partial'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    return count * (n / len) + count_chars_in_partial(n % len, s, c);
}

/* Possible weaknesses found:
 *  conflicting types for 'count_chars_in_partial'; have 'int(int,  const char *, char)'
 *  conflicting types for 'count_chars_in_partial'
 *  an argument type that has a default promotion cannot match an empty parameter name list declaration
 */
int count_chars_in_partial(int remaining, const char *s, char c) {
    int count = 0;
    for (int i = 0; i < remaining; ++i) {
        if (s[i] == c) {
            count++;
        }
    }
    return count;
}

int main() {
    const char *s = "aba";
    int n = 10;
    char c = 'a';
    int result = count_occurrences(s, n, c);
    printf("The character '%c' appears %d times in the repeated string.\n", c, result);
    return 0;
}