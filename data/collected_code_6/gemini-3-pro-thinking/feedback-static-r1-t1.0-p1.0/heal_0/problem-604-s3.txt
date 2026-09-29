#include <stdio.h>
#include <string.h>

void reverse_characters(char *start, char *end);
void reverse_words(char *str);

void reverse_characters(char *start, char *end) {
    if (start == NULL || end == NULL) {
        return;
    }

    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverse_words(char *str) {
    if (str == NULL || *str == '\0') {
        return;
    }

    size_t len = strlen(str);
    reverse_characters(str, str + len - 1);

    char *start = str;
    char *end = str;

    while (*end != '\0') {
        if (*end == ' ') {
            if (end > start) {
                reverse_characters(start, end - 1);
            }
            start = end + 1;
        }
        end++;
    }

    if (end > start) {
        reverse_characters(start, end - 1);
    }
}

int main(void) {
    char text[] = "Acting as an experienced C developer";

    reverse_words(text);
    printf("%s\n", text);

    return 0;
}