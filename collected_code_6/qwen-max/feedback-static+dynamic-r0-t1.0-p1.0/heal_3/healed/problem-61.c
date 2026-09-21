#include <stdio.h>
#include <string.h>

int count_matching_substrings(const char *str, size_t length) {
    int counter = 0;
    for (int i = 0; i < length; i++) {
        int sum = 0;
        for (int len = 1; i + len <= length; len++) {
            sum += str[i + len - 1] - '0';
            if (sum == len) {
                counter++;
            }
        }
    }
    return counter;
}

int main() {
    const char input[] = "1112223";
    size_t input_length = sizeof(input) / sizeof(input[0]) - 1;
    int result = count_matching_substrings(input, input_length);
    printf("Number of substrings: %d\n", result);
    return 0;
}