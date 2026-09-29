#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEQUENCE_LENGTH 256
#define MAX_SEQUENCES 100

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    /* Possible weaknesses found:
     *  Either the condition 'len<max_len' is redundant or the array 'str[53]' is accessed at index 25600, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Assuming that condition 'len<max_len' is not redundant
     *  Array index out of bounds
     */
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

    /* Possible weaknesses found:
     *  Assuming that condition 'i<input_len' is not redundant
     */
    while (i < input_len && count < max_sequences) {
        if (islower((unsigned char)input[i])) {
            /* Possible weaknesses found:
             *  low_start is assigned 'i' here.
             */
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
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(sequences[count], input + low_start, copy_len);
                    sequences[count][copy_len] = '\0';
                    count++;
                } else {
                    i = underscore_pos + 1;
                }
            /* Possible weaknesses found:
             *  Assuming that condition 'i==input_len' is not redundant
             *  Condition 'low_start<i' is always false
             *  Condition 'low_start<i' is always false [knownConditionTrueFalse]
             */
            } else if (i == input_len && low_start < i) {
                size_t total_len = i - low_start;
                if (total_len >= MAX_SEQUENCE_LENGTH) {
                    total_len = MAX_SEQUENCE_LENGTH - 1;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(sequences[count], input + low_start, total_len);
                sequences[count][total_len] = '\0';
                count++;
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
    /* Possible weaknesses found:
     *  Assignment 'max_safe_len=(unsigned long)256*(unsigned long)100', assigned value is 25600
     */
    size_t max_safe_len = (size_t)MAX_SEQUENCE_LENGTH * (size_t)MAX_SEQUENCES;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (sequences == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Calling function 'safe_strlen', 2nd argument 'max_safe_len+1' value is 25601
     */
    text_len = safe_strlen(text, max_safe_len + 1);
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