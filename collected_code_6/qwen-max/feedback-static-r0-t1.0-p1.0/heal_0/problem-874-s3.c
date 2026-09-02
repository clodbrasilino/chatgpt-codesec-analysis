#include <stdio.h>
#include <string.h>

int is_concatenated(const char *str, const char *substr) {
    size_t len = strlen(substr);
    if (len == 0 || len > strlen(str)) return 0;

    for (const char *p = str; *p; p++) {
        if (strncmp(p, substr, len) == 0) {
            if (p[len] == '\0' || p[len - 1] == '\0') return 1;
            p += len - 1;
        }
    }
    return 0;
}

int main() {
    const char *str = "ababab";
    const char *substr = "ab";
    if (is_concatenated(str, substr)) {
        printf("The string is a concatenation of the substring.\n");
    } else {
        printf("The string is not a concatenation of the substring.\n");
    }
    return 0;
}