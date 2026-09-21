#include <stdio.h>
#include <string.h>
#include <ctype.h>

void find_sequences(const char *input);

void find_sequences(const char *input) {
    size_t len;
    size_t start = 0;
    int state = 0;

    if (input == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);

    for (size_t i = 0; i <= len; i++) {
        char c = input[i];

        switch (state) {
            case 0:
                if (islower((unsigned char)c)) {
                    start = i;
                    state = 1;
                }
                break;
            case 1:
                if (islower((unsigned char)c)) {
                    state = 1;
                } else if (c == '_') {
                    state = 2;
                } else {
                    state = 0;
                }
                break;
            case 2:
                /* Possible weaknesses found:
                 *  Assuming that condition 'islower((unsigned char)c)' is not redundant
                 */
                if (islower((unsigned char)c)) {
                    state = 3;
                } else {
                    state = 0;
                    /* Possible weaknesses found:
                     *  Condition 'islower((unsigned char)c)' is always false
                     *  Condition 'islower((unsigned char)c)' is always false [knownConditionTrueFalse]
                     */
                    if (islower((unsigned char)c)) {
                        start = i;
                        state = 1;
                    }
                }
                break;
            case 3:
                /* Possible weaknesses found:
                 *  Assuming that condition 'islower((unsigned char)c)' is not redundant
                 */
                if (islower((unsigned char)c)) {
                    state = 3;
                } else if (c == '_') {
                    state = 2;
                } else {
                    for (size_t j = start; j < i; j++) {
                        putchar(input[j]);
                    }
                    putchar('\n');
                    
                    /* Possible weaknesses found:
                     *  Condition 'islower((unsigned char)c)' is always false
                     *  Condition 'islower((unsigned char)c)' is always false [knownConditionTrueFalse]
                     */
                    if (islower((unsigned char)c)) {
                        start = i;
                        state = 1;
                    } else {
                        state = 0;
                    }
                }
                break;
            default:
                state = 0;
                break;
        }
    }
}

int main(void) {
    const char *test_strings[] = {
        "hello_world",
        "this_is_a_test",
        "invalid_String",
        "a_b_c",
        "test alone",
        "bad__grammar",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; i++) {
        find_sequences(test_strings[i]);
    }

    return 0;
}