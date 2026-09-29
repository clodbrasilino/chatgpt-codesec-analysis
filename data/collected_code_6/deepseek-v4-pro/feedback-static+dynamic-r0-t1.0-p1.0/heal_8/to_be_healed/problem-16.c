#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENCE_LENGTH 256
#define MAX_SEQUENCES 100

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int find_sequences(const char *input, char (*sequences)[MAX_SEQUENCE_LENGTH], int max_sequences) {
    if (input == NULL || sequences == NULL || max_sequences <= 0) {
        return -1;
    }

    int count = 0;
    size_t i = 0;
    size_t input_len = safe_strlen(input, MAX_SEQUENCE_LENGTH * MAX_SEQUENCES);

    while (i < input_len && count < max_sequences) {
        if (islower((unsigned char)input[i])) {
            size_t low_start = i;
            while (i < input_len && islower((unsigned char)input[i])) {
                i++;
            }
            if (i < input_len && input[i] == '_') {
                size_t underscore_pos = i;
                i++;
                if (i < input_len && islower((unsigned char)input[i])) {
                    size_t second_start = i;
                    while (i < input_len && islower((unsigned char)input[i])) {
                        i++;
                    }
                    size_t total_len = (underscore_pos - low_start) + 1 + (i - second_start);
                    if (total_len >= MAX_SEQUENCE_LENGTH) {
                        total_len = MAX_SEQUENCE_LENGTH - 1;
                    }
                    size_t copy_len = total_len;
                    if (low_start + copy_len > input_len) {
                        copy_len = input_len - low_start;
                    }
                    if (copy_len >= MAX_SEQUENCE_LENGTH) {
                        copy_len = MAX_SEQUENCE_LENGTH - 1;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(sequences[count], input + low_start, copy_len);
                    sequences[count][copy_len] = '\0';
                    count++;
                } else {
                    i = underscore_pos + 1;
                }
            }
        } else {
            i++;
        }
    }

    return count;
}

int main(void) {
    const char *text = "hello_world test example_foo bar_baz_qux abc_def_ghi";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char (*sequences)[MAX_SEQUENCE_LENGTH] = malloc(MAX_SEQUENCES * sizeof(*sequences));
    int num_sequences;
    size_t text_len;
    size_t max_safe_len = (size_t)MAX_SEQUENCE_LENGTH * (size_t)MAX_SEQUENCES;

    if (sequences == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    text_len = safe_strlen(text, max_safe_len);
    if (text_len >= max_safe_len) {
        fprintf(stderr, "Error: Input string too long\n");
        free(sequences);
        return EXIT_FAILURE;
    }

    num_sequences = find_sequences(text, sequences, MAX_SEQUENCES);

    if (num_sequences < 0) {
        fprintf(stderr, "Error: Invalid input parameters\n");
        free(sequences);
        return EXIT_FAILURE;
    }

    printf("Found %d sequences:\n", num_sequences);
    for (int i = 0; i < num_sequences; i++) {
        printf("%s\n", sequences[i]);
    }

    free(sequences);
    return EXIT_SUCCESS;
}