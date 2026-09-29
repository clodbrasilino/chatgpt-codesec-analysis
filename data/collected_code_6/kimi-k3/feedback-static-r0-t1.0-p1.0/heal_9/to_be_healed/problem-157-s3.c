#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char value;
    int count;
} RLEPair;

size_t rle_encode(const char *input, size_t input_len, RLEPair **output) {
    size_t i;
    size_t pair_count;
    RLEPair *pairs;

    if (input == NULL || output == NULL) {
        return 0;
    }

    if (input_len == 0) {
        *output = NULL;
        return 0;
    }

    pairs = (RLEPair *)malloc(input_len * sizeof(RLEPair));
    if (pairs == NULL) {
        *output = NULL;
        return 0;
    }

    pair_count = 0;
    pairs[0].value = input[0];
    pairs[0].count = 1;

    for (i = 1; i < input_len; i++) {
        if (input[i] == pairs[pair_count].value) {
            pairs[pair_count].count++;
        } else {
            pair_count++;
            pairs[pair_count].value = input[i];
            pairs[pair_count].count = 1;
        }
    }

    pair_count++;

    *output = pairs;
    return pair_count;
}

/* Possible weaknesses found:
 *  to match this '{'
 */
int main(void) {
    /* Possible weaknesses found:
     *  missing terminating " character
     *  No pair for character ("). Can't process file. File is either invalid or unicode, which is currently not supported. [syntaxError]
     *  expected '}'
     *  expected expression at end of input
     *  expected declaration or statement at end of input
     *  expected expression
     *  expected ';' at end of declaration
     */
    const char *test_string = "AAABBBCCDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD