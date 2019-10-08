#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void *thread_function(void *arg);
pthread_mutex_t work_mutex; /* proteção para: work_area e time_to_exit */

void L(int trem,int trilho){
	//pthread_mutex_lock(&work_mutex);
    //pthread_mutex_unlock(&work_mutex);
    //pthread_exit(0);
}

int main() {
    int res;
    pthread_t thread_trem1, thread_trem2;
	void *trem1,*trem2;
    void *thread_result;
    res = pthread_mutex_init(&work_mutex, NULL);
    if (res != 0) {
        perror("Iniciação do Mutex falhou");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&thread_trem1, NULL, trem1, NULL);
    if (res != 0) {
        perror("Criação da Thread do trem1 falhou");
        exit(EXIT_FAILURE);
    }
    res = pthread_create(&thread_trem2, NULL, trem2, NULL);
    if (res != 0) {
        perror("Criação da Thread do trem2 falhou");
        exit(EXIT_FAILURE);
    }
	
}
