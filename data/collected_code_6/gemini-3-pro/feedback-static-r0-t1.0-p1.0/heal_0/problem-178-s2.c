#include <stdio.h>
#include <string.h>

int search_literals(const char *text, const char *literals[], int count) {
    if (text == NULL || literals == NULL || count <= 0) {
        return -1;
    }

    int found_count = 0;
    for (int i = 0; i < count; ++i) {
        if (literals[i] != NULL) {
            if (strstr(text, literals[i]) != NULL) {
                found_count++;
            }
        }
    }

    return found_count;
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog.";
    const char *literals[] = {"quick", "fox", "cat", "dog"};
    int num_literals = sizeof(literals) / sizeof(literals[0]);

    int found = search_literals(text, literals, num_literals);

    printf("Found %d literals in the text.\n", found);

    return 0;
}