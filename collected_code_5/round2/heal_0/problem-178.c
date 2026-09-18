#include <stdio.h>
#include <string.h>

int search_string(char *haystack, char **needles, int n) {
    if (!haystack || !needles || n <= 0) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        if (!needles[i]) {
            continue;
        }
        if (strstr(haystack, needles[i]) != NULL) {
            return i;
        }
    }
    return -1;
}

int main() {
    char *haystack = "Hello, World!";
    char *needles[] = {
        "Goodbye",
        "World",
        "Hello"
    };
    int n = 3;
    int result = search_string(haystack, needles, n);
    if (result == -1) {
        printf("No match found\n");
    } else {
        printf("Match found: %s\n", needles[result]);
    }

    return 0;
}