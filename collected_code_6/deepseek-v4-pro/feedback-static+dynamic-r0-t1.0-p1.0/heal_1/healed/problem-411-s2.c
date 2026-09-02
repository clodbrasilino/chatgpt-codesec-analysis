#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *snake_to_camel(const char *snake_str) {
    if (snake_str == NULL) {
        return NULL;
    }

    size_t len = strlen(snake_str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t src_pos = 0;
    size_t dst_pos = 0;
    
    while (src_pos < len) {
        if (snake_str[src_pos] == '_' && src_pos + 1 < len && 
            snake_str[src_pos + 1] >= 'a' && snake_str[src_pos + 1] <= 'z') {
            result[dst_pos++] = toupper((unsigned char)snake_str[src_pos + 1]);
            src_pos += 2;
        } else {
            result[dst_pos++] = snake_str[src_pos++];
        }
    }
    
    result[dst_pos] = '\0';
    return result;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", argv[0]);
        return 1;
    }

    char *camel_str = snake_to_camel(argv[1]);
    if (camel_str == NULL) {
        fprintf(stderr, "Error converting string\n");
        return 1;
    }

    printf("%s\n", camel_str);
    free(camel_str);
    return 0;
}