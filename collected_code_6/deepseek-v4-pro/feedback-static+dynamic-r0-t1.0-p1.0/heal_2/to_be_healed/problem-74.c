#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool check_sequence(const int patterns[][2], int pattern_count, const int *sequence, int sequence_length) {
    if (pattern_count <= 0 || sequence_length <= 0 || patterns == NULL || sequence == NULL) {
        return false;
    }

    int pattern_index = 0;
    int sequence_index = 0;

    while (pattern_index < pattern_count && sequence_index < sequence_length) {
        int target = patterns[pattern_index][0];
        int count = patterns[pattern_index][1];

        if (count <= 0) {
            pattern_index++;
            continue;
        }

        int current_count = 0;
        while (sequence_index + current_count < sequence_length && 
               sequence[sequence_index + current_count] == target &&
               current_count < count) {
            current_count++;
        }

        if (current_count != count) {
            return false;
        }

        sequence_index += current_count;
        pattern_index++;
    }

    return pattern_index == pattern_count && sequence_index == sequence_length;
}

int main(void) {
    int patterns1[][2] = {{1, 2}, {3, 1}, {2, 3}};
    /* Possible weaknesses found:
     *  Variable 'sequence1' can be declared as const array [constVariable]
     */
    int sequence1[] = {1, 1, 3, 2, 2, 2};
    
    if (check_sequence(patterns1, 3, sequence1, 6)) {
        printf("Sequence 1 matches\n");
    } else {
        printf("Sequence 1 does not match\n");
    }

    int patterns2[][2] = {{1, 1}, {2, 2}};
    /* Possible weaknesses found:
     *  Variable 'sequence2' can be declared as const array [constVariable]
     */
    int sequence2[] = {1, 2, 2};
    
    if (check_sequence(patterns2, 2, sequence2, 3)) {
        printf("Sequence 2 matches\n");
    } else {
        printf("Sequence 2 does not match\n");
    }

    int patterns3[][2] = {{5, 3}, {4, 2}};
    /* Possible weaknesses found:
     *  Variable 'sequence3' can be declared as const array [constVariable]
     */
    int sequence3[] = {5, 5, 5, 4, 4};
    
    if (check_sequence(patterns3, 2, sequence3, 5)) {
        printf("Sequence 3 matches\n");
    } else {
        printf("Sequence 3 does not match\n");
    }

    int patterns4[][2] = {{2, 1}, {3, 2}, {4, 1}};
    /* Possible weaknesses found:
     *  Variable 'sequence4' can be declared as const array [constVariable]
     */
    int sequence4[] = {2, 3, 3, 4, 5};
    
    if (check_sequence(patterns4, 3, sequence4, 5)) {
        printf("Sequence 4 matches\n");
    } else {
        printf("Sequence 4 does not match\n");
    }

    int patterns5[][2] = {{1, 2}, {1, 1}};
    /* Possible weaknesses found:
     *  Variable 'sequence5' can be declared as const array [constVariable]
     */
    int sequence5[] = {1, 1, 1};
    
    if (check_sequence(patterns5, 2, sequence5, 3)) {
        printf("Sequence 5 matches\n");
    } else {
        printf("Sequence 5 does not match\n");
    }

    return 0;
}