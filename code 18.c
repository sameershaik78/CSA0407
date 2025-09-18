#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    // Simple Bubble Sort
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int i, j, n, head, size, direction;
    int total_movement = 0;

    printf("Enter total number of disk requests: ");
    scanf("%d", &n);

    int request[n + 1];  // One extra for head
    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (e.g., 200): ");
    scanf("%d", &size);

    printf("Enter head movement direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    request[n] = head;  // Include head in the request queue
    n++;

    sort(request, n);

    // Find the position of head in sorted array
    int pos;
    for (i = 0; i < n; i++) {
        if (request[i] == head) {
            pos = i;
            break;
        }
    }

    printf("\nSequence of head movement:\n");

    if (direction == 1) {  // Move right
        for (i = pos; i < n - 1; i++) {
            printf("Head moves from %d to %d\n", request[i], request[i + 1]);
            total_movement += abs(request[i + 1] - request[i]);
        }
        // Move to end of disk
        printf("Head moves from %d to %d\n", request[n - 1], size - 1);
        total_movement += abs(size - 1 - request[n - 1]);

        // Reverse direction and move to the left
        for (i = pos - 1; i >= 0; i--) {
            if (i == pos - 1)
                printf("Head moves from %d to %d\n", size - 1, request[i]);
            else
                printf("Head moves from %d to %d\n", request[i + 1], request[i]);
            total_movement += abs(request[i + 1] - request[i]);
        }

    } else {  // Move left
        for (i = pos; i > 0; i--) {
            printf("Head moves from %d to %d\n", request[i], request[i - 1]);
            total_movement += abs(request[i] - request[i - 1]);
        }
        // Move to start of disk
        printf("Head moves from %d to 0\n", request[0]);
        total_movement += request[0];

        // Reverse direction and move to the right
        for (i = pos + 1; i < n; i++) {
            if (i == pos + 1)
                printf("Head moves from 0 to %d\n", request[i]);
            else
                printf("Head moves from %d to %d\n", request[i - 1], request[i]);
            total_movement += abs(request[i] - request[i - 1]);
        }
    }

    printf("\nTotal head movement = %d\n", total_movement);

    return 0;
}
