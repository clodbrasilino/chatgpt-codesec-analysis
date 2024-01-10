#include <stdio.h>
#include <string.h>

void concatenateStrings(const char *str1, const char *str2, char *result, size_t resultSize){
    if (!str1 || !str2 || !result) {
        return;
    }

    size_t str1Len = strnlen(str1, resultSize);
    size_t str2Len = strnlen(str2, resultSize);

    if (str1Len < resultSize - 1) {
        strncpy(result, str1, str1Len);
        result[str1Len] = '\0';

        if (str1Len + str2Len < resultSize - 1) {
            strncat(result, str2, str2Len);
        }
    }
}

int main() {
    char str1[100] = "Hello, ";
    char str2[100] = "world!";
    char result[200] = "";

    concatenateStrings(str1, str2, result, sizeof(result));

    printf("%s\n", result);
    return 0;
}