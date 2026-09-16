#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

float *convert_to_floats(const char **list, size_t list_len, size_t *out_len) {
    if (list == NULL || out_len == NULL) {
        return NULL;
    }

    float *result = (float *)malloc(list_len * sizeof(float));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < list_len; i++) {
        if (list[i] == NULL || list[i][0] == '\0') {
            continue;
        }

        char *endptr = NULL;
        errno = 0;
        float val = strtof(list[i], &endptr);

        if (errno == 0 && endptr != list[i] && *endptr == '\0') {
            result[count] = val;
            count++;
        }
    }

    *out_len = count;
    return result;
}

int main(void) {
    const char *list[] = {"3.14", "invalid", "2.718", "1.0e2", "", "99", "1.2.3", "-5.5", "0"};
    size_t len = sizeof(list) / sizeof(list[0]);
    size_t out_len = 0;

    float *floats = convert_to_floats(list, len, &out_len);

    if (floats != NULL) {
        for (size_t i = 0; i < out_len; i++) {
            printf("%f\n", floats[i]);
        }
        free(floats);
    }

    return 0;
}