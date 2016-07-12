#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

/*
Per i comandi gestiti internamente (come verrebbero gestiti anche "esternamente"), non ho controllato 
l'effettiva quantità di argomenti che l'utente mi passa, andando semplicemente a visionare quelli necessari
*/

#define N 512 /* Uso una variabile N per qualsiasi dimensione di stringa, pura comodità */

int main(int argc, char **argv,char **envp)
{
	const char space[1] = " ";
	while(1)
	{
		pid_t pid; /* Stringa in cui avrò l'intero comando dato dall'utente */
		char buffer[N];
		char *token;
		char kommand[N] = "/bin/";
		char *p; /* per le variabili d'ambiente */
		int status, cdcheck; 
		printf("$: ");
		fgets(buffer, N, stdin);
		if(buffer == NULL)
		{
			perror("Insert command, try again\n");
			break;
		}
		char **ftok;
		char *str1;
		ftok = (char **)malloc((N/2)*sizeof(char *));
		/*
		precarico una quantità fissata di puntatori a puntatori 
		per non avere problemi in fase di reallocazione della memoria
		*/
		int i, k;
		for(i=0, str1 = buffer; ; i++, str1 = NULL)
		{
			token = strtok(str1, space);
			if(token == NULL)
			{	
				break;
			}			
			ftok[i] = (char *)malloc(sizeof(token)+sizeof(char));
			strcpy(ftok[i], token);
		}
		ftok[i-1][strlen(ftok[i-1])-1] = '\0'; /*pare che la funzione ftok aggiunga, all'ultimo token, il carattere \n */
		ftok[i] = (char *)malloc(sizeof(char));
		ftok[i]= (char *)0;
		
		if(!(strcmp(ftok[0], "exit")))
		{
			/* gestisco direttamente l'uscita dal programma */
			printf("Have a nice day, hope I could help you soon\n");						
			for(k=0; k<i;k++)
				free(ftok[k]);
			free(ftok);
			free(token);
			exit(0);
		} 
		else if (!(strcmp(ftok[0], "printenv")))
		{
			/* comando interno di stampa delle
			variabili d'ambiente  */
			while(p = *envp)
			{
				strcat(p, "\n");
				write(1, p, strlen(p));
				envp += 1;
			}				
			for(k=0; k<i;k++)
				free(ftok[k]);
			free(ftok);
			free(token);
		}
		else if(!(strcmp(ftok[0], "cd")))
		{
			if(i == 1)
			{
				printf("%s: Insert directory, try \"man %s\"\n", ftok[0], ftok[0]);
			}
			else
			{	
				cdcheck = chdir(ftok[1]);			
				for(k=0; k<i;k++)
					free(ftok[k]);
				free(ftok);
				free(token);
				if(cdcheck)
				{
					perror("cd");
				}
			}
		}
		else if((pid=fork())<0) /* il figlio mi gestirà invece i comandi esterni */
		{
			perror("Fork error, try again later \n");
		}
		
		else if(pid==0)
		{
			/* CODICE DEL FIGLIO
			PER LA GESTIONE DEI COMANDI DA 
			TERMINALE ESTERNI */
			strncat(kommand, ftok[0], strlen(ftok[0]));
			if((execv(kommand, ftok))==-1)
			{
				perror("Error");
				exit(-1);
			}
		}
		else
		{
			wait(&status);
			for(k=0; k<i;k++)
				free(ftok[k]);
			free(ftok);
			free(token);
		}
	}
}
