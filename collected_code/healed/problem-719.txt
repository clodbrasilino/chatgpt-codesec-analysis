#include <stdbool.h>
#include <stdio.h>

bool matchString(const char *str) {
    if (str == NULL) {
        return false;
    }

    if (str[0] == 'a') {
        int i = 1;
        while (str[i] == 'b') {
            i++;
        }
        return true;
    }
    return false;
}

int main(void) {
    // Test case 1
    char str1[] = "abbb";
    bool match1 = matchString(str1);
    printf("%s: %s\n", str1, match1 ? "match" : "no match");

    // Test case 2
    char str2[] = "cdef";
    bool match2 = matchString(str2);
    printf("%s: %s\n", str2, match2 ? "match" : "no match");

    return 0;
}