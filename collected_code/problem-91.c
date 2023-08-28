#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isSubstringPresent(char *substring, char *strings[], int size) {
    for (int i = 0; i < size; i++) {
        if (strstr(strings[i], substring) != NULL) {
            return true;
        }
    }
    return false;
}

int main() {
    char *substring = "substring";
    char *strings[] = {"string1", "string2", "string3"};

    if (isSubstringPresent(substring, strings, sizeof(strings) / sizeof(strings[0]))) {
        printf("Substring is present\n");
    } else {
        printf("Substring is not present\n");
    }

    return 0;
}