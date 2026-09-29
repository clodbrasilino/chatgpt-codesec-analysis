#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int abbreviate_road(const char *input, char *output, size_t out_size) {
    const char target[] = "road";
    const char replacement[] = "rd.";
    size_t target_len = sizeof(target) - 1;
    size_t replacement_len = sizeof(replacement) - 1;
    size_t i = 0;
    size_t j = 0;
    size_t k;

    if (input == NULL || output == NULL || out_size == 0) {
        return -1;
    }

    while (input[i] != '\0') {
        if (strncmp(&input[i], target, target_len) == 0) {
            if (j + replacement_len >= out_size) {
                return -1;
            }
            for (k = 0; k < replacement_len; k++) {
                output[j + k] = replacement[k];
            }
            j += replacement_len;
            i += target_len;
        } else {
            if (j + 1 >= out_size) {
                return -1;
            }
            output[j] = input[i];
            j++;
            i++;
        }
    }

    if (j >= out_size) {
        return -1;
    }

    output[j] = '\0';
    return 0;
}

int main(void) {
    const char *original_string = "The old road is a long road to travel.";
    size_t buffer_size = 256;
    char *result_string;
    int status;

    result_string = (char *)malloc(buffer_size);
    if (result_string == NULL) {
        return EXIT_FAILURE;
    }

    status = abbreviate_road(original_string, result_string, buffer_size);

    if (status == 0) {
        printf("%s\n", result_string);
    } else {
        free(result_string);
        return EXIT_FAILURE;
    }

    free(result_string);
    return EXIT_SUCCESS;
}