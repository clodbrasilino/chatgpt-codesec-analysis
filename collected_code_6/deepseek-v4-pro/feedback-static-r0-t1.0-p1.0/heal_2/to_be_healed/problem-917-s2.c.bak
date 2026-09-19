#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *sequence;
    int start;
    int length;
} Sequence;

/* Possible weaknesses found:
 *  'find_sequences' declared here
 */
Sequence *find_sequences(const char *str, int *count) {
    int len = strlen(str);
    Sequence *sequences = NULL;
    *count = 0;

    for (int i = 0; i < len - 1; i++) {
        if (isupper((unsigned char)str[i]) && islower((unsigned char)str[i + 1])) {
            int j = i + 1;
            while (j < len && islower((unsigned char)str[j])) {
                j++;
            }

            Sequence *temp = (Sequence *)realloc(sequences, (*count + 1) * sizeof(Sequence));
            if (temp == NULL) {
                /* Possible weaknesses found:
                 *  implicit declaration of function 'free_sequences'; did you mean 'find_sequences'? [-Wimplicit-function-declaration]
                 *  call to undeclared function 'free_sequences'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 *  previous implicit declaration is here
                 *  did you mean 'find_sequences'?
                 */
                free_sequences(sequences, *count);
                *count = 0;
                return NULL;
            }
            sequences = temp;

            int length = j - i;
            sequences[*count].sequence = (char *)malloc((length + 1) * sizeof(char));
            if (sequences[*count].sequence == NULL) {
                /* Possible weaknesses found:
                 *  call to undeclared function 'free_sequences'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
                 */
                free_sequences(sequences, *count);
                *count = 0;
                return NULL;
            }

            strncpy(sequences[*count].sequence, &str[i], length);
            sequences[*count].sequence[length] = '\0';
            sequences[*count].start = i;
            sequences[*count].length = length;
            (*count)++;
            i = j - 1;
        }
    }

    return sequences;
}

/* Possible weaknesses found:
 *  conflicting types for 'free_sequences'
 */
void free_sequences(Sequence *sequences, int count) {
    if (sequences != NULL) {
        for (int i = 0; i < count; i++) {
            free(sequences[i].sequence);
        }
        free(sequences);
    }
}

int main(void) {
    const char *text = "Hello World This Is A Test Example";
    int count = 0;
    Sequence *result = find_sequences(text, &count);

    if (result == NULL && count > 0) {
        return 1;
    }

    if (result != NULL) {
        printf("Found %d sequences:\n", count);
        for (int i = 0; i < count; i++) {
            printf("Sequence: \"%s\" at position %d, length %d\n",
                   result[i].sequence, result[i].start, result[i].length);
        }
    } else {
        printf("No sequences found or memory allocation failed.\n");
    }

    free_sequences(result, count);
    return 0;
}