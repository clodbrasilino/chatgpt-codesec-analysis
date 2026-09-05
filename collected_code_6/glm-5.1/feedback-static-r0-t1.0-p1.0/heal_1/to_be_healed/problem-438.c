#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'ptr' can be declared as pointer to const [constParameterPointer]
 */
void check_allocation(void *ptr) {
    if (ptr == NULL) {
        exit(EXIT_FAILURE);
    }
}

/* Possible weaknesses found:
 *  Parameter 'tuples' can be declared as pointer to const [constParameterPointer]
 */
int count_bidirectional_pairs(int *tuples, int size) {
    if (tuples == NULL || size < 2 || size % 2 != 0) {
        return 0;
    }
    
    int num_pairs = size / 2;
    int *visited = (int *)calloc(num_pairs, sizeof(int));
    check_allocation(visited);
    
    int count = 0;
    
    for (int i = 0; i < num_pairs; i++) {
        if (visited[i] == 1) {
            continue;
        }
        
        int a1 = tuples[i * 2];
        int b1 = tuples[i * 2 + 1];
        
        for (int j = i + 1; j < num_pairs; j++) {
            if (visited[j] == 1) {
                continue;
            }
            
            int a2 = tuples[j * 2];
            int b2 = tuples[j * 2 + 1];
            
            if ((a1 == b2) && (b1 == a2)) {
                count++;
                visited[i] = 1;
                visited[j] = 1;
                break;
            }
        }
    }
    
    free(visited);
    return count;
}

int main() {
    int data[] = {1, 2, 3, 4, 2, 1, 4, 3, 5, 6, 6, 5, 7, 8};
    int size = sizeof(data) / sizeof(data[0]);
    
    int result = count_bidirectional_pairs(data, size);
    printf("%d\n", result);
    
    return 0;
}