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
	const char space[] = " ";;
	while(1)
	{
		pid_t pid; /* Stringa in cui avrò l'intero comando dato dall'utente */
		char buffer[N];
		char *token;
		char kommand[N] = "/bin/";
		char s[2];
		char *p; // per le variabili d'ambiente
		int nread;  /* saranno l'effettiva dimensione della stringa letta sulla mini-shell */
		int status; 
		//scanf("%s", buffer);
		printf("$: ");
		//nread = fgets(0, buffer, N);
		// PROVARE CON FGETS
		fgets(buffer, N, stdin);
		if(buffer == NULL)
		{
			perror("Insert command, try again\n");
			break;
		}
		printf("La stringa appena scritta: %s, grande %d \n", buffer, strlen(buffer));
		char **ftok;
		char *savepoint;
		char *str1;
		ftok = (char **)malloc(1*sizeof(char *));
		int i=0, k;
		for(i=0, str1 = buffer; ; i++, str1 = NULL)
		{
			token = strtok_r(str1, space, &savepoint);
			if(token == NULL)
				break;
			ftok[i] = (char *)malloc(strlen(token)*sizeof(char));
			ftok[i] = token;
			printf("%s\n", token);
			ftok = (char **)realloc(ftok, (i+1)*sizeof(char *));
		}
			/*

			token = strtok_r(buffer, space, &savepoint);
			ftok[i] = (char *)malloc(strlen(token)*sizeof(char));
			ftok[i] = token;			
			while(token != NULL)
			{
				token = strtok_r(NULL, space, &savepoint);
				if((token == NULL))
					break;
				i++;
				ftok = (char **)realloc(ftok, i*sizeof(char *));
				ftok[i] = (char *)malloc(strlen(token)*sizeof(char));
				strcpy(ftok[i], token);
				write(1, ftok[i], strlen(ftok[i]));
			}

			if(i<1)
			{
				ftok = (char **)realloc(ftok, i*sizeof(char *));
				ftok[i] = (char *)malloc(sizeof(char));
				ftok[i] = '\0';
			}
			*/
		if(!(strcmp(ftok[0], "exit")))
		{
			printf("Have a nice day, hope I could help you soon\n");
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
		}
		else  if((pid=fork())<0)
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
		for(k=0; k<i;k++)
			free(ftok[i]);
		free(ftok);
		free(token);
	}
}
