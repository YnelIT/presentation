#include <stdio.h>
#include <pthread.h>

// Function to be exuted by the thread
void* wehe(void* jobag) {
    printf("Thread is running. Argument passed: %d\n", *((int*)jobag));
    return NULL;
}

int main() {
    pthread_t thread;   // Declare a thread identifier
    int ilan = 10;       // Argument to pass to the thread

// Create the thread

    if (pthread_create(&thread, NULL, wehe, (void*)&ilan)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

// Wait for the thread to complete

    if (pthread_join(thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    printf("Process is finished\n");
    return 0;
}

Previous
Reply
 
Forward
 
Delete
