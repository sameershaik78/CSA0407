#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, head, total_movement = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int request[n];
    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nSequence of head movement:\n");
    for (i = 0; i < n; i++) {
        printf("Head moves from %d to %d with movement = %d\n", head, request[i], abs(request[i] - head));
        total_movement += abs(request[i] - head);
        head = request[i];
    }

    printf("\nTotal head movement = %d\n", total_movement);
    return 0;
}
