#include <stdio.h>
#include <string.h>

char *find_last_occurrence(const char *str, int c) {
    if (str == NULL) {
        return NULL;
    }

    char *last = NULL;
    size_t len = strlen(str);
    size_t i = 0;

    while (i < len) {
        if (str[i] == (char)c) {
            last = (char *)&str[i];
        }
        i++;
    }

    if (c == '\0') {
        return (char *)&str[len];
    }

    return last;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return 1;
    }

    const char *str = argv[1];
    char c = argv[2][0];

    /* Possible weaknesses found:
     *  Variable 'result' can be declared as pointer to const [constVariablePointer]
     */
    char *result = find_last_occurrence(str, c);

    if (result != NULL) {
        printf("Found at position: %ld\n", (long)(result - str));
    } else {
        printf("Not found\n");
    }

    return 0;
}