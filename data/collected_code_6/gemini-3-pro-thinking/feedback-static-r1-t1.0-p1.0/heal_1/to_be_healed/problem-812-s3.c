#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int abbreviate_road(const char *input, char *output, size_t out_size) {
    const char *target = "road";
    const char *replacement = "rd.";
    size_t target_len;
    size_t replacement_len;
    size_t input_len;
    size_t i = 0;
    size_t j = 0;

    if (input == NULL || output == NULL || out_size == 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    target_len = strlen(target);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    replacement_len = strlen(replacement);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);

    while (i < input_len) {
        if (strncmp(&input[i], target, target_len) == 0) {
            if (j + replacement_len >= out_size) {
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(&output[j], replacement, replacement_len);
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
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = abbreviate_road(original_string, result_string, buffer_size);

    if (status == 0) {
        printf("%s\n", result_string);
    } else {
        fprintf(stderr, "String processing failed\n");
        free(result_string);
        return EXIT_FAILURE;
    }

    free(result_string);
    return EXIT_SUCCESS;
}