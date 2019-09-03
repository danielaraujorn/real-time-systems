// UFRN-CT-DCA
// Disciplina: Sistemas Operacionais
// Programa matatdor.cpp
// Sinais sã eventos gerados pelo Unix em resposta a algumas condições, como:
//  erros, violação de memória, instrução ilegal, ...

#include <signal.h> // definição dos sinais de interrupções
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // system()



int  main()
{
  	// o processo que vai matar

  	int meu_pid;
  	int pid_vitima;
	int signal;
	meu_pid = getpid();
    
  	do{
		printf( "\nEu sou um programa gerenciador de programa, meu PID é %d\n", meu_pid );
		printf( "Digite o PID do processo que devo gerenciar: (digite 0 para sair) ");
		scanf( "%d", &pid_vitima);
		if(pid_vitima==0){
			printf( "\nAgora posso morrer tranquilo.\n");
			exit(0);
		}	

		printf( "Digite qual ação devo tomar: 1 para matar, 2 para parar, 3 para continuar ");
		scanf( "%d", &signal);

		if(signal==1){
			printf("\n Vou matar o processo %d \n", pid_vitima);
			kill(pid_vitima, SIGKILL);
		}else if(signal==2){
			printf("\n Vou parar o processo %d \n", pid_vitima);
			kill(pid_vitima, SIGSTOP);
		}else if(signal==3){
			printf("\n Vou continuar o processo %d \n", pid_vitima);
			kill(pid_vitima, SIGCONT);
		}

 	}while(true);

	
}






