#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_multiple_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t str_len = strlen(str);
    char *result = malloc(str_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t read_pos = 0;
    size_t write_pos = 0;

    while (read_pos < str_len) {
        if (str[read_pos] == ' ') {
            result[write_pos++] = ' ';
            while (read_pos < str_len && str[read_pos] == ' ') {
                read_pos++;
            }
        } else {
            result[write_pos++] = str[read_pos++];
        }
    }

    result[write_pos] = '\0';

    char *shrunk = realloc(result, write_pos + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void) {
    const char *tests[] = {
        "Google    Assistant",
        "Quad    Core",
        "ChromeCast    Built-in",
        "Hello    world!  This   is a    test.",
        NULL
    };
    
    for (int i = 0; tests[i] != NULL; i++) {
        char *res = remove_multiple_spaces(tests[i]);
        if (res != NULL) {
            printf("%s\n", res);
            free(res);
        }
    }
    
    return 0;
}