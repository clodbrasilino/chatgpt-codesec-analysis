#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isSubstringPresent(const char *substring, const char *strings[], int size) {
    for (int i = 0; i < size; i++) {
        if (strings[i] && strstr(strings[i], substring) != NULL) {
            return true;
        }
    }
    return false;
}

int main() {
    const char *substring = "substring";
    const char *strings[] = {"string1", "string2", "string3", NULL};

    if (isSubstringPresent(substring, strings, sizeof(strings) / sizeof(strings[0]) - 1)) {
        printf("Substring is present\n");
    } else {
        printf("Substring is not present\n");
    }

    return 0;
}