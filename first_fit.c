/*
 * Online Examination Memory Allocator - First Fit
 *
 * Each student session (process) is placed in the FIRST memory block
 * that is large enough. The block's free space shrinks by the size
 * of the process. Processes that fit nowhere are reported.
 */
#include <stdio.h>

#define MAX 50

int main(void) {
    int nb, np;
    int blockSize[MAX], original[MAX];
    int procSize[MAX], allocation[MAX], leftAfter[MAX];

    printf("Enter number of memory blocks: ");
    if (scanf("%d", &nb) != 1 || nb < 1 || nb > MAX) {
        printf("Invalid number of blocks (1-%d).\n", MAX);
        return 1;
    }
    for (int i = 0; i < nb; i++) {
        printf("  Size of block %d: ", i + 1);
        if (scanf("%d", &blockSize[i]) != 1 || blockSize[i] < 0) {
            printf("Invalid size.\n");
            return 1;
        }
        original[i] = blockSize[i];
    }

    printf("Enter number of processes (student sessions): ");
    if (scanf("%d", &np) != 1 || np < 1 || np > MAX) {
        printf("Invalid number of processes (1-%d).\n", MAX);
        return 1;
    }
    for (int i = 0; i < np; i++) {
        printf("  Memory required by process %d: ", i + 1);
        if (scanf("%d", &procSize[i]) != 1 || procSize[i] < 0) {
            printf("Invalid size.\n");
            return 1;
        }
        allocation[i] = -1;   /* -1 means not allocated */
        leftAfter[i] = 0;
    }

    /* First Fit: scan blocks from the start, take the first that fits */
    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nb; j++) {
            if (blockSize[j] >= procSize[i]) {
                allocation[i] = j;
                blockSize[j] -= procSize[i];
                leftAfter[i] = blockSize[j];
                break;
            }
        }
    }

    /* Allocation details */
    printf("\n=== Process Allocation Details ===\n");
    printf("%-10s %-14s %-10s %-18s\n",
           "Process", "Size", "Block", "Block Left After");
    for (int i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("P%-9d %-14d B%-9d %-18d\n",
                   i + 1, procSize[i], allocation[i] + 1, leftAfter[i]);
        else
            printf("P%-9d %-14d %-10s %-18s\n",
                   i + 1, procSize[i], "-", "Not allocated");
    }

    /* Remaining memory in each block */
    printf("\n=== Remaining Memory in Each Block ===\n");
    printf("%-8s %-14s %-12s\n", "Block", "Original", "Remaining");
    int totalFree = 0;
    for (int j = 0; j < nb; j++) {
        printf("B%-7d %-14d %-12d\n", j + 1, original[j], blockSize[j]);
        totalFree += blockSize[j];
    }
    printf("Total remaining memory: %d\n", totalFree);

    /* Unallocated processes */
    printf("\n=== Unallocated Processes ===\n");
    int any = 0;
    for (int i = 0; i < np; i++) {
        if (allocation[i] == -1) {
            printf("P%d (needs %d)\n", i + 1, procSize[i]);
            any = 1;
        }
    }
    if (!any)
        printf("None. All processes were allocated.\n");

    return 0;
}
