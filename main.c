#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Thread function
void *thread_function(void *arg) {
    int thread_id = *((int *)arg);
    printf("Thread %d: I'm running in process %d\n", thread_id, getpid());
    return NULL;
}

// Function to create multiple threads in a process
void create_threads(int num_threads) {
    pthread_t threads[num_threads];
    int thread_ids[num_threads];

    for (int i = 0; i < num_threads; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
            perror("Failed to create thread");
        }
    }

    // Join threads
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main() {
    int num_processes = 2;
    int num_threads_per_process = 3;

    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();

        if (pid == 0) { // Child process
            printf("Process %d created by parent %d\n", getpid(), getppid());
            create_threads(num_threads_per_process);
            exit(0); // Exit the child process
        } else if (pid > 0) { // Parent process
            // Continue to the next iteration to fork another child
        } else {
            perror("Failed to fork process");
            exit(1);
        }
    }

    // Wait for all child processes to finish
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    printf("All processes and threads have finished execution.\n");

    return 0;
}