#include <stdio.h>
#include <string.h>

static int char_in_set(char c, const char *set) {
    while (*set) {
        if (c == *set)
            return 1;
        set++;
    }
    return 0;
}

void remove_chars(char *str, size_t str_size, const char *remove_set) {
    if (!str || !remove_set || str_size == 0)
        return;

    char *src = str;
    char *dst = str;
    size_t dst_index = 0;

    while (*src && dst_index < str_size - 1) {
        if (!char_in_set(*src, remove_set)) {
            *dst = *src;
            dst++;
            dst_index++;
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

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return 1;
    }

    if (len >= size - 1) {
        clear_input_buffer();
    }

    return 1;
}

int main(void) {
    char str1[256];
    char str2[256];

    printf("Enter first string: ");
    if (!read_line(str1, sizeof(str1)))
        return 1;

    printf("Enter second string: ");
    if (!read_line(str2, sizeof(str2)))
        return 1;

    remove_chars(str1, sizeof(str1), str2);

    printf("Result: %s\n", str1);

    return 0;
}