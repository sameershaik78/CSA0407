#include <stdio.h>

int main() {
    int i, j, num_blocks, num_processes;

    printf("Enter number of memory blocks: ");
    scanf("%d", &num_blocks);
    int block_size[num_blocks];
    int block_allocated[num_blocks]; // 0 = free, 1 = allocated

    printf("Enter sizes of %d memory blocks:\n", num_blocks);
    for (i = 0; i < num_blocks; i++) {
        scanf("%d", &block_size[i]);
        block_allocated[i] = 0;
    }

    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    int process_size[num_processes];
    int allocation[num_processes]; // Store block index for each process

    printf("Enter sizes of %d processes:\n", num_processes);
    for (i = 0; i < num_processes; i++) {
        scanf("%d", &process_size[i]);
        allocation[i] = -1; // Initially, no block allocated
    }

    // First Fit Allocation
    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_blocks; j++) {
            if (!block_allocated[j] && block_size[j] >= process_size[i]) {
                allocation[i] = j;
                block_allocated[j] = 1; // Mark block as allocated
                break;
            }
        }
    }

    // Output
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (i = 0; i < num_processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, process_size[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1); // Block numbering starts from 1
        else
            printf("Not Allocated\n");
    }

    return 0;
}
