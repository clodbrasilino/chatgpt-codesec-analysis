#include <stdio.h>
#include <string.h>

int match_string(const char *str) {
    if (str == NULL) return 0;
    if (strlen(str) < 4) return 0;
    return str[0] == 'a' && str[1] == 'b' && str[2] == 'b' && str[3] == 'b';
}

int main() {
    const char *test1 = "abbb";
    const char *test2 = "abc";
    const char *test3 = "abbbc";
    const char *test4 = "a";

    printf("%s: %s\n", test1, match_string(test1) ? "Match" : "No Match");
    printf("%s: %s\n", test2, match_string(test2) ? "Match" : "No Match");
    printf("%s: %s\n", test3, match_string(test3) ? "Match" : "No Match");
    printf("%s: %s\n", test4, match_string(test4) ? "Match" : "No Match");

    return 0;
}