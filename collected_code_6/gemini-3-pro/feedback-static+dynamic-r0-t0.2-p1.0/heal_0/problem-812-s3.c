#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    const char* target = "road";
    const char* replacement = "rd.";
    size_t target_len = strlen(target);
    size_t replacement_len = strlen(replacement);
    size_t input_len = strlen(input);

    size_t count = 0;
    const char* tmp = input;
    while ((tmp = strstr(tmp, target)) != NULL) {
        count++;
        tmp += target_len;
    }

    size_t new_len = input_len - (count * target_len) + (count * replacement_len);
    char* result = (char*)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    const char* current = input;
    char* dest = result;
    while ((tmp = strstr(current, target)) != NULL) {
        size_t len = tmp - current;
        strncpy(dest, current, len);
        dest += len;
        strcpy(dest, replacement);
        dest += replacement_len;
        current = tmp + target_len;
    }
    strcpy(dest, current);

    return result;
}

int main(void) {
    const char* original = "The long road leads to another road.";
    char* abbreviated = abbreviate_road(original);

    if (abbreviated != NULL) {
        printf("Original: %s\n", original);
        printf("Abbreviated: %s\n", abbreviated);
        free(abbreviated);
    } else {
        fprintf(stderr, "Memory allocation failed or input was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}