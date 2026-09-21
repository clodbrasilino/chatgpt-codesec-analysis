#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

static int char_in_set(char c, const char *set) {
    while (*set) {
        if (c == *set)
            return 1;
        set++;
    }
    return 0;
}

void remove_chars(char *str, const char *remove_set) {
    if (!str || !remove_set)
        return;

    char *src = str;
    char *dst = str;

    while (*src) {
        if (!char_in_set(*src, remove_set)) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static int read_line(char *buffer, size_t size) {
    if (!fgets(buffer, size, stdin))
        return 0;

    size_t len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return 1;
    }

    if (len == size - 1 && buffer[len - 1] != '\n') {
        clear_input_buffer();
    }

    return 1;
}

int main(void) {
    char str1[BUFFER_SIZE + 1];
    char str2[BUFFER_SIZE + 1];

    printf("Enter first string: ");
    if (!read_line(str1, sizeof(str1)))
        return 1;

    printf("Enter second string: ");
    if (!read_line(str2, sizeof(str2)))
        return 1;

    remove_chars(str1, str2);

    printf("Result: %s\n", str1);

    return 0;
}