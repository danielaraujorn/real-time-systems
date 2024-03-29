//
//  threadTrem.cpp
//
//
//  Created by Affonso on 25/10/16.
//
//

// http: pubs.opengroup.org/onlinepubs/7908799/xsh/pthread_mutex_init.html

// Programa que sincroniza threads utilizando-se mutexes
// Para compilá-lo utilise: g++ -o threadTrem threadTrem.cpp -lpthread

//   Os trens circulam em sentido horário entre os trilhos

//   + - - - 1 - - - + - - - 2 - - - + - - - 3 - - - +
//   |               |               |               |
//   |               |               |               |
//   |               |               |               |
//   4     trem1     5     trem2     6     trem3     7
//   |               |               |               |
//   |               |               |               |
//   |               |               |               |
//   + - - - 8 - - - + - - - 9 - - - + - - - 10- - - +
//   |                                               |
//   |                                               |
//   |                                               |
//   11                    trem4                    12
//   |                                               |
//   |                                               |
//   |                                               |
//   + - - - - - - - - - - - 13- - - - - - - - - - - +

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

pthread_mutex_t t5;  /* proteção para o trilho 5 */
pthread_mutex_t t6;  /* proteção para o trilho 6 */
pthread_mutex_t t8;  /* proteção para o trilho 6 */
pthread_mutex_t t9;  /* proteção para o trilho 6 */
pthread_mutex_t t10; /* proteção para o trilho 6 */

void L(int trem, int trilho, int sleepTime)
{
  printf("trem %d no trilho %d\n", trem, trilho);
  sleep(sleepTime);
}

void *trem1(void *arg)
{
  int trem = 1;
  int sleepTime = 1;
  while (true)
  {
    L(trem, 1, sleepTime);
    pthread_mutex_lock(&t5);
    pthread_mutex_lock(&t8);
    L(trem, 5, sleepTime);
    pthread_mutex_unlock(&t5);
    L(trem, 8, sleepTime);
    pthread_mutex_unlock(&t8);
    L(trem, 4, sleepTime);
  }
  pthread_exit(0);
}

void *trem2(void *arg)
{
  int trem = 2;
  int sleepTime = 2;
  while (true)
  {
    L(trem, 2, sleepTime);
    pthread_mutex_lock(&t6);
    L(trem, 6, sleepTime);
    pthread_mutex_unlock(&t6);
    pthread_mutex_lock(&t9);
    L(trem, 9, sleepTime);
    pthread_mutex_unlock(&t9);
    pthread_mutex_lock(&t5);
    L(trem, 5, sleepTime);
    pthread_mutex_unlock(&t5);
  }
  pthread_exit(0);
}

void *trem3(void *arg)
{
  int trem = 3;
  int sleepTime = 4;
  while (true)
  {
    L(trem, 3, sleepTime);
    L(trem, 7, sleepTime);
    pthread_mutex_lock(&t10);
    pthread_mutex_lock(&t6);
    L(trem, 10, sleepTime);
    pthread_mutex_unlock(&t10);
    L(trem, 6, sleepTime);
    pthread_mutex_unlock(&t6);
  }
  pthread_exit(0);
}

void *trem4(void *arg)
{
  int trem = 4;
  int sleepTime = 8;
  while (true)
  {
    L(trem, 13, sleepTime);
    L(trem, 11, sleepTime);
    pthread_mutex_lock(&t8);
    L(trem, 8, sleepTime);
    pthread_mutex_unlock(&t8);
    pthread_mutex_lock(&t9);
    L(trem, 9, sleepTime);
    pthread_mutex_unlock(&t9);
    pthread_mutex_lock(&t10);
    L(trem, 10, sleepTime);
    pthread_mutex_unlock(&t10);
    L(trem, 12, sleepTime);
  }
  pthread_exit(0);
}

int main()
{
  srand(time(0));
  int res;
  pthread_t thread1, thread2, thread3, thread4;

  void *thread_result;

  // ------ criando multex t5 ------
  res = pthread_mutex_init(&t5, NULL);
  if (res != 0)
  {
    perror("Iniciação do Mutex t5 falhou");
    exit(EXIT_FAILURE);
  }

  // ------ criando multex t6 ------
  res = pthread_mutex_init(&t6, NULL);
  if (res != 0)
  {
    perror("Iniciação do Mutex t6 falhou");
    exit(EXIT_FAILURE);
  }

  // ------ criando multex t8 ------
  res = pthread_mutex_init(&t8, NULL);
  if (res != 0)
  {
    perror("Iniciação do Mutex t8 falhou");
    exit(EXIT_FAILURE);
  }

  // ------ criando multex t9 ------
  res = pthread_mutex_init(&t9, NULL);
  if (res != 0)
  {
    perror("Iniciação do Mutex t9 falhou");
    exit(EXIT_FAILURE);
  }

  // ------ criando multex t10 ------
  res = pthread_mutex_init(&t10, NULL);
  if (res != 0)
  {
    perror("Iniciação do Mutex t10 falhou");
    exit(EXIT_FAILURE);
  }

  //------ Thread 1 (executa a fn: trem 1) ------
  res = pthread_create(&thread1, NULL, trem1, NULL);
  if (res != 0)
  {
    perror("Criação da thread 1 falhou");
    exit(EXIT_FAILURE);
  }

  //------ Thread 2 (executa a fn: trem 2) ------
  res = pthread_create(&thread2, NULL, trem2, NULL);
  if (res != 0)
  {
    perror("Criação da thread 2 falhou");
    exit(EXIT_FAILURE);
  }

  //------ Thread 3 (executa a fn: trem 3) ------
  res = pthread_create(&thread3, NULL, trem3, NULL);
  if (res != 0)
  {
    perror("Criação da thread 3 falhou");
    exit(EXIT_FAILURE);
  }

  //------ Thread 4 (executa a fn: trem 3) ------
  res = pthread_create(&thread4, NULL, trem4, NULL);
  if (res != 0)
  {
    perror("Criação da thread 4 falhou");
    exit(EXIT_FAILURE);
  }

  // ----- Espera termino das threads
  res = pthread_join(thread1, &thread_result);
  if (res != 0)
  {
    perror("Juncao da Thread 1 falhou");
    exit(EXIT_FAILURE);
  }
  res = pthread_join(thread2, &thread_result);
  if (res != 0)
  {
    perror("Juncao da Thread 2 falhou");
    exit(EXIT_FAILURE);
  }
  res = pthread_join(thread3, &thread_result);
  if (res != 0)
  {
    perror("Juncao da Thread 3 falhou");
    exit(EXIT_FAILURE);
  }
  res = pthread_join(thread4, &thread_result);
  if (res != 0)
  {
    perror("Juncao da Thread 4 falhou");
    exit(EXIT_FAILURE);
  }

  printf("MAIN() --> Thread foi juntada com sucesso\n");

  //----- destruíndo mutex
  pthread_mutex_destroy(&t5);
  pthread_mutex_destroy(&t6);
  pthread_mutex_destroy(&t8);
  pthread_mutex_destroy(&t9);
  pthread_mutex_destroy(&t10);
  exit(EXIT_SUCCESS);
}
