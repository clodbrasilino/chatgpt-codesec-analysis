#include <ctype.h>
#include <stdio.h>
#include <string.h>

void string_to_lower(char *str) {
    if (str == NULL) {
        return;
    }
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int main(void) {
    char test1[] = "HELLO WORLD";
    char test2[] = "C Programming 123!";
    char test3[] = "Mixed CASE String";

    string_to_lower(test1);
    string_to_lower(test2);
    string_to_lower(test3);

    printf("%s\n", test1);
    printf("%s\n", test2);
    printf("%s\n", test3);

    return 0;
}