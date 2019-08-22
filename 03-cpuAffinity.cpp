// mudando de CPU a cada 5 segundos
// UFRN-CT-DCA
// Disciplina: Sistemas de Tempo Real

#include <iostream>
#include <sys/time.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>   // para: time()
using namespace std;

int main() {
	cpu_set_t my_set;
	CPU_ZERO(&my_set);
	bool cpuBit=false;
	CPU_SET((int)cpuBit, &my_set);
	sched_setaffinity(getpid(), sizeof(cpu_set_t), &my_set);

    int i, j;
    struct timeval tempo_inicial, tempo_final;
    int tmili;
	time_t tempo;
	tempo = time( (time_t *) 0);

    gettimeofday(&tempo_inicial, NULL);  // inicio é uma struct com dois campos:tv_sec e tv_usec.
    
     /* Substitua o for a seguir pelo trecho de código
       cujo tempo de execução deverá ser medido. */
    int changed=false;
    for (j = 0; j < 10; j ++){
        for (i = 0; i < 1387634340; i ++){
			int segundos = time( (time_t *) 0) - tempo;
			//cout<<segundos<<endl;
			if(segundos%5==0){
				if(!changed){
					CPU_ZERO(&my_set);
					cpuBit=!cpuBit;
					cout<<(int)cpuBit<<endl;
					CPU_SET((int)cpuBit, &my_set);
					sched_setaffinity(getpid(), sizeof(cpu_set_t), &my_set);
					changed=true;
				}
			}
			else
				changed=false;
		}
	}
    
    gettimeofday(&tempo_final, NULL);
    tmili = (int) (1000 * (tempo_final.tv_sec - tempo_inicial.tv_sec) + (tempo_final.tv_usec - tempo_inicial.tv_usec) / 1000); // para transformar em milissegundos

    printf("tempo decorrido: %d milissegundos\n", tmili);
    return (0);
}
