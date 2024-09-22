#include <stdio.h>
#include <pthread.h>

void* wehe(void* jobag) {
    printf("Thread is running. Argument passed: %d\n", *((int*)jobag));
    return NULL;
}

int main() {
    pthread_t thread;   
    int ilan = 10;       

    if (pthread_create(&thread, NULL, wehe, (void*)&ilan)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    if (pthread_join(thread, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        return 2;
    }

    printf("Process is finished\n");
    return 0;
}