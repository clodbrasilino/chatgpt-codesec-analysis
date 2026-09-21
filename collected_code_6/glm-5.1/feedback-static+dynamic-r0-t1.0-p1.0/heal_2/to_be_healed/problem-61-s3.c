#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 6, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  *  test case 2 failed: expected 12, got <no output>
  */

int count_substrings(const char *str, size_t len) {
    int total = 0;

    if (len == 0) {
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        int sum = 0;
        for (size_t j = i; j < len; j++) {
            sum += str[j] - '0';
            int sub_len = j - i + 1;
            if (sum == sub_len) {
                total++;
            }
        }
    }

    return total;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    size_t input_len = 0;

    while (input[input_len] != '\0') {
        if (input[input_len] < '0' || input[input_len] > '9') {
            fprintf(stderr, "Error: Input string must contain only digits.\n");
            return EXIT_FAILURE;
        }
        input_len++;
    }

    int result = count_substrings(input, input_len);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}