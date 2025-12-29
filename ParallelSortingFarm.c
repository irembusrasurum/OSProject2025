#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_SIZE 1000
#define NUM_THREADS 4

int arr[ARRAY_SIZE];
int total_swaps = 0;              // Ortak sayaç (mutex gerektiren yer)
pthread_mutex_t mutex;            // Mutex tanımı

// Diziyi rastgele doldur
void fill_array() {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % 10000;
    }
}

// Dizinin belli bir kısmını sıralar
void bubble_sort(int start, int end) {
    for (int i = start; i < end; i++) {
        for (int j = start; j < end; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                // KRİTİK BÖLGE
                pthread_mutex_lock(&mutex);
                total_swaps++;
                pthread_mutex_unlock(&mutex);
            }
        }
    }
}

// Thread fonksiyonu
void* thread_sort(void* arg) {
    int thread_id = *(int*)arg;

    int chunk_size = ARRAY_SIZE / NUM_THREADS;
    int start = thread_id * chunk_size;
    int end = (thread_id == NUM_THREADS - 1)
                ? ARRAY_SIZE - 1
                : start + chunk_size - 1;

    bubble_sort(start, end);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    srand(time(NULL));
    fill_array();

    pthread_mutex_init(&mutex, NULL);   //  Mutex başlat

    clock_t start_time = clock();

    // Threadleri oluştur
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_sort, &thread_ids[i]);
    }

    // Threadlerin bitmesini bekle
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Parallel sorting time: %f seconds\n", time_spent);
    printf("Total swaps: %d\n", total_swaps);

    pthread_mutex_destroy(&mutex); //  Mutex kapat
    return 0;
}
