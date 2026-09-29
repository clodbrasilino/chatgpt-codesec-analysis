#include <stdio.h>
#include <string.h>
#include <ctype.h>

void capitalizeFirstLast(char *str, size_t strSize) {
    if (str == NULL || strSize == 0) return;
    /* Possible weaknesses found:
     *  Assuming that condition 'i<strSize' is not redundant
     */
    for (size_t i = 0, wordStart = 0; i < strSize; i++) {
        /* Possible weaknesses found:
         *  Condition 'i<strSize' is always true [knownConditionTrueFalse]
         *  Condition 'i<strSize' is always true
         */
        if (i == 0 || (i < strSize && str[i-1] == ' ')) {
            wordStart = i;
            str[i] = toupper((unsigned char)str[i]);
        } else if (str[i] == ' ' || (i == strSize - 1)) {
            if (wordStart < i - 1) {
                str[i-1] = toupper((unsigned char)str[i-1]);
            }
        }
    }
}

int main() {
    char str[] = "hello world this is a test";
    capitalizeFirstLast(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}