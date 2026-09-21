#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'STRG', got <no output>
  *  test case 1 failed: expected 'FID', got <no output>
  *  test case 0 failed: expected 'PYTH', got <no output>
  */

char *remove_lowercase(const char *input)
{
    size_t len;
    size_t i;
    size_t j;
    char *result;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);

    result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    j = 0;
    for (i = 0; i < len; i++) {
        if (!islower((unsigned char)input[i])) {
            result[j] = input[i];
            j++;
        }
    }
    result[j] = '\0';

    return result;
}

int main(void)
{
    const char *test1 = "HelloWorldABC";
    const char *test2 = "KDeoALOklOOHserfLoAJSIskdsf";
    char *output1;
    char *output2;

    output1 = remove_lowercase(test1);
    if (output1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    output2 = remove_lowercase(test2);
    if (output2 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(output1);
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test1);
    printf("Result:   %s\n", output1);
    printf("Original: %s\n", test2);
    printf("Result:   %s\n", output2);

    free(output1);
    free(output2);

    return EXIT_SUCCESS;
}