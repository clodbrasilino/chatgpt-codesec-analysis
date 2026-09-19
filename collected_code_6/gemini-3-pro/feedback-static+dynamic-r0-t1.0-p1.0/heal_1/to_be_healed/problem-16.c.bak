#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void find_lowercase_underscore_sequences(const char* input) {
    if (input == NULL) {
        return;
    }

    size_t len = strlen(input);
    bool in_sequence = false;
    size_t seq_start = 0;

    for (size_t i = 0; i <= len; ++i) {
        if (input[i] != '\0' && (islower((unsigned char)input[i]) || input[i] == '_')) {
            if (!in_sequence) {
                in_sequence = true;
                seq_start = i;
            }
        } else {
            if (in_sequence) {
                /* Possible weaknesses found:
                 *  Value stored to 'seq_len' during its initialization is never read [deadcode.DeadStores]
                 *  Variable 'seq_len' is assigned a value that is never used. [unreadVariable]
                 */
                size_t seq_len = i - seq_start;
                bool has_lower = false;
                bool has_underscore = false;
                bool valid = true;

                if (input[seq_start] == '_' || input[i - 1] == '_') {
                    valid = false;
                }

                if (valid) {
                    for (size_t j = seq_start; j < i; ++j) {
                        if (islower((unsigned char)input[j])) {
                            has_lower = true;
                        } else if (input[j] == '_') {
                            has_underscore = true;
                            if (j > seq_start && input[j - 1] == '_') {
                                valid = false;
                                break;
                            }
                        }
                    }
                }

                if (valid && has_lower && has_underscore) {
                    for (size_t j = seq_start; j < i; ++j) {
                        putchar(input[j]);
                    }
                    putchar('\n');
                }
                in_sequence = false;
            }
        }
    }
}

int main(void) {
    const char* test_strings[] = {
        "hello_world",
        "Hello_world",
        "hello_World",
        "a_b",
        "a__b",
        "_",
        "_a",
        "a_",
        "this_is_a_test",
        "ignoreTHIS_part",
        "foo_bar_baz",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; ++i) {
        printf("Testing: %s\n", test_strings[i]);
        find_lowercase_underscore_sequences(test_strings[i]);
        printf("-----\n");
    }

    return EXIT_SUCCESS;
}