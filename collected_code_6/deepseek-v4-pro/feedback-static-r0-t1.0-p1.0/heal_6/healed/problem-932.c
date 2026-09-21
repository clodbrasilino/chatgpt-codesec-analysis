#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 100

static int is_duplicate(const char *words[], int count, const char *word) {
    if (words == NULL || word == NULL) {
        return 0;
    }
    for (int i = 0; i < count; i++) {
        if (words[i] != NULL && strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int remove_duplicate_words(char *input[], int input_count, char *output[], int output_max) {
    int output_count = 0;
    if (output == NULL || input == NULL || output_max <= 0 || input_count < 0) {
        return 0;
    }
    if (output_max > MAX_WORDS) {
        output_max = MAX_WORDS;
    }
    for (int i = 0; i < input_count && output_count < output_max; i++) {
        if (input[i] == NULL) {
            continue;
        }
        size_t len = strnlen(input[i], MAX_WORD_LEN);
        if (len >= MAX_WORD_LEN) {
            continue;
        }
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
    char *output[MAX_WORDS] = { NULL };
    int output_max = MAX_WORDS;
    int output_count = remove_duplicate_words(input, input_count, output, output_max);

    for (int i = 0; i < output_count && i < MAX_WORDS; i++) {
        if (output[i] != NULL) {
            printf("%s\n", output[i]);
        }
    }

    return 0;
}