#include <stdio.h>
#include <ctype.h>
#include <string.h>

int findPattern(const char *str, int *start, int *end) {
    int i = 0;
    while (str[i] != '\0') {
        if (isupper((unsigned char)str[i])) {
            *start = i;
            i++;
            while (str[i] != '\0' && islower((unsigned char)str[i])) {
                i++;
            }
            *end = i - 1;
            return 1;
        } else {
            i++;
        }
    }
    return 0;
}

int main() {
    const char *input = "Hello There This Is A Test";
    int start, end;

    for (int found = findPattern(input, &start, &end); found; found = findPattern(input + end + 1, &start, &end)) {
        printf("Found: %.*s\n", end - start + 1, input + start);
    }

    return 0;
}