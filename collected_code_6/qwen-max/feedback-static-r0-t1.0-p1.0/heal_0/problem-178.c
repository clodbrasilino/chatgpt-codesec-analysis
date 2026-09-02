#include <stdio.h>
#include <string.h>

int contains_any(const char *str, const char **search_terms, int n) {
    for (int i = 0; i < n; i++) {
        if (strstr(str, search_terms[i]) != NULL) {
            return 1;
        }
    }
    return 0;
}

int main() {
    const char *haystack = "This is a test string to check for literals.";
    const char *needles[] = {"test", "string", "example"};
    int num_needles = sizeof(needles) / sizeof(needles[0]);

    if (contains_any(haystack, needles, num_needles)) {
        printf("Found one of the search terms in the string.\n");
    } else {
        printf("None of the search terms were found in the string.\n");
    }

    return 0;
}