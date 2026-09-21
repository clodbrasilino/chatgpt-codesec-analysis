#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* abbreviate_road(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    const char target[] = "road";
    const char replacement[] = "rd.";
    size_t target_len = sizeof(target) - 1;
    size_t replacement_len = sizeof(replacement) - 1;

    size_t input_len = 0;
    const char* ptr = input;
    while (*ptr != '\0') {
        input_len++;
        ptr++;
    }

    int count = 0;
    const char* tmp = input;
    while ((tmp = strstr(tmp, target)) != NULL) {
        count++;
        tmp += target_len;
    }

    size_t new_size = input_len + count * (replacement_len - target_len) + 1;
    char* result = (char*)malloc(new_size);
    if (result == NULL) {
        return NULL;
    }

    char* dest = result;
    const char* src = input;
    size_t remaining = new_size;

    while ((tmp = strstr(src, target)) != NULL) {
        size_t len = tmp - src;
        
        for (size_t i = 0; i < len; i++) {
            *dest++ = src[i];
        }
        remaining -= len;

        for (size_t i = 0; i < replacement_len; i++) {
            *dest++ = replacement[i];
        }
        remaining -= replacement_len;
        
        src = tmp + target_len;
    }

    snprintf(dest, remaining, "%s", src);

    return result;
}

int main(void) {
    const char* test_str = "The road to the road is a long road.";
    char* abbreviated = abbreviate_road(test_str);

    if (abbreviated != NULL) {
        printf("Original: %s\n", test_str);
        printf("Abbreviated: %s\n", abbreviated);
        free(abbreviated);
    } else {
        fprintf(stderr, "Memory allocation failed or input was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}