#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

static size_t safe_strlen(const char *s) {
    if (s == NULL) return 0;
    size_t len = 0;
    while (len < MAX_STRING_LENGTH && s[len] != '\0') {
        ++len;
    }
    return len;
}

static void reverse_string(char *s) {
    if (s == NULL) {
        return;
    }

    size_t len = safe_strlen(s);
    if (len < 2) {
        return;
    }

    for (size_t i = 0; i < len / 2; ++i) {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        reverse_string(strings[i]);
    }
}

int main(void) {
    char s1[] = "hello";
    char s2[] = "world";
    char s3[] = "";

    char *strings[] = { s1, s2, s3 };
    size_t count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings(strings, count);

    for (size_t i = 0; i < count; ++i) {
        printf("%s\n", strings[i]);
    }

    return 0;
}