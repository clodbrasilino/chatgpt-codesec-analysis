#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<string.h>' or provide a declaration of 'strcmp'
  */

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

static int is_duplicate(const char *words[], int count, const char *word) {
    for (int i = 0; i < count; i++) {
        /* Possible weaknesses found:
         *  call to undeclared library function 'strcmp' with type 'int (const char *, const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
         *  include the header <string.h> or explicitly provide a declaration for 'strcmp'
         *  implicit declaration of function 'strcmp' [-Wimplicit-function-declaration]
         */
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int remove_duplicate_words(char *input[], int input_count, char *output[], int output_max) {
    int output_count = 0;
    for (int i = 0; i < input_count; i++) {
        if (input[i] == NULL) {
            continue;
        }
        if (output_count >= output_max) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        if (!is_duplicate((const char **)output, output_count, input[i])) {
            output[output_count] = input[i];
            output_count++;
        }
    }
    return output_count;
}

int main(void) {
    char *input[] = {"apple", "banana", "apple", "cherry", "banana", "date", "apple"};
    int input_count = sizeof(input) / sizeof(input[0]);
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *output[MAX_WORDS];

    int output_max = MAX_WORDS;
    int output_count = remove_duplicate_words(input, input_count, output, output_max);

    for (int i = 0; i < output_count; i++) {
        printf("%s\n", output[i]);
    }

    return 0;
}