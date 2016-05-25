/*
Nome: Matteo
Cognome: Gruppi
Matricola: 243420
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>


#define N 512 /* Uso una variabile N per qualsiasi dimensione di stringa, pura comodità */

int main(int argc, char **argv,char **envp)
{
	int status; 
	pid_t pid;
	char buffer[N]; /* Stringa in cui avrò l'intero comando dato dall'utente */
	char kommand[N] = "/bin/";
	char *token;
	int i =0, k=0;
	int nread;  /* saranno l'effettiva dimensione della stringa letta sulla mini-shell */
	char *p;
	const char space[2] = " ";
	while(1)
	{
		char s[2];
		strcpy(s, "$:");
		write(1, s, strlen(s));
		nread = read(0, buffer, N);
		if(nread<0)
		{
			perror("Error reading command, please try again\n");
		}
		else
		{
			char *ftok[N];
			token = strtok(buffer, space);
			i=0;
			ftok[i] = token;
			while(token != NULL)
			{
				token = strtok(NULL, space);
				printf("%s\n", ftok[i]);
				i++;
				ftok[i] = token;
			}
			printf("%d\n", strlen(ftok[0]));
			//printf("%s\n", ftok[0]);
			/*
			if(!(strcmp(ftok[0], "exit")))
			{
				printf("Have a nice day, hope I could help you soon\n");
				exit(0);
			} else if (!(strcmp(ftok[0], "printenv")))
			{
				/* comando interno di stampa delle
				variabili d'ambiente  
				while(p = *envp)
				{
					printf("%s\n", p);
					envp += 1;
				}	
			}
			else */ if((pid=fork())<0)
			{
				perror("Fork error, try again later!\n");
				exit(-1);
			}
			else if(pid==0)
			{
				/* CODICE DEL FIGLIO
				PER LA GESTIONE DEI COMANDI DA 
				TERMINALE ESTERNI */
				strncat(kommand, ftok[0], strlen(ftok[0]));
				if((execv(kommand, ftok))==-1)
				{
					//perror("Command error, please check the syntax\n");
					exit(-1);
				}
			}
			
			else
			{
				wait(&status);
			}			
		}
	}
}