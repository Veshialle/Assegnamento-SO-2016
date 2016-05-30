Assegnamento-SO-2016

Testo dell'esercizio:
Si realizzi un programma C che realizzi un min-shell con le seguenti caratteristiche:
	1. Presenti all'utente un prompt, ad es. "$".
	2. Recuperi dalla linea digitata dall'utente il comando e i suoi eventuali argomenti.
	3. Sia in grado di gestire direttamente due comandi interni:
		- printenv: visualizza tutte le variabili d'ambiente.
		- exit: fa terminare lo shell.
Si suggerisce l'utilizzo della funzione C strtok per estrarre comando ed argomenti dalla linea digitata dall'utente.

Essendo un progetto pubblico è a disposizione di chiunque voglia trarne ispirazione, essendo un assegnamento universitario VALUTATO il copia incolla non è gradito affatto.
Spero di essere stato di aiuto.


PS: Nota volante per una possibile risoluzione (parte di un esercizio di altro esame):
p.nome = (char *)malloc(strlen(stringa)+1); // p.nome è una variabile non ancora inizializzata, focalizzare l'attenzione sulla dimensione di allocamento all'interno di malloc(); con appunto solo (strlen(stringa)+1) e non (strlen(stringa)*sizeof(char)) (o ancor meglio ((strlen(stringa)+1)*sizeof(char));
HAVE A NICE DAY
