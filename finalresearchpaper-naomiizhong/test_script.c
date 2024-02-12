#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avltree.h"


int main() {
    t_node* root = NULL;
    int numNodes = 20000000;  // Adjust this value as needed


    clock_t start, end;
    double cpu_time_used;

    // Measure the time taken for insertion
    start = clock();
    for (int i = 0; i < numNodes; i++) {
        root = insert(root, rand());  // Insert random keys
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for %d insertions: %f seconds\n", numNodes, cpu_time_used);

    /*
   // Count the total number of swaps during insertions
    int totalSwaps = 0;
    for (int i = 0; i < numNodes; i++) {
        int key = rand() % 100;  // Generate random keys (0 to 99)
        totalSwaps += countSwaps(root, key);
    }

    printf("Total number of swaps during insertions: %d\n", totalSwaps);

    **/

    // Measure the time taken for search (assuming all keys exist in the tree)
    start = clock();
    for (int i = 0; i < numNodes; i++) {
        t_node* temp = search(root, rand());
        if (temp == NULL) {
            printf("Key not found in the tree!\n");
            break;
        }
    }
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for %d searches: %f seconds\n", numNodes, cpu_time_used);

    // Free the allocated memory
    freeTree(root);

    return 0;
}