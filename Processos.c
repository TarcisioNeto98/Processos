#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //possibilta usar o comando fork()
#include <sys/types.h>//posibilita usar o tipo pid_t armazena o id do processo
#define MEMORIA 1000

int conta_string(char *string){
	int i;
	for(i = 1; string[i] != '\0'; i++){
		i++;
	}
	return i;
}

int main() {
  pid_t processoFilho;
  char string[MEMORIA];
  int v[2];

  if((pipe(v)) == -1){
  	printf("Erro de criacao do pipe\n");
  	return -1;
  }

  processoFilho = fork(); //A funcao fork() usada para criar processos filhos
  if(processoFilho == -1){//retorna -1 em caso de erro ao criar o novo processo
    printf("processo nao foi criado");
    return -1;
  }

  if(processoFilho == 0){//retorna 0 o id do processo filho. esse é o codigo que sera executado pelo processo filho.
  	close(v[0]);
  	printf("Digite alguma coisa:\n");
  	scanf("%s", string);
  	write(v[1], &string, conta_string(string)+1);
  	close(v[1]);
  }

  else{//codigo executado pelo processo pai
  	int i = 0;
  	char stringRecebida[MEMORIA];
    FILE *arquivo;

    read(v[0], &stringRecebida, sizeof(stringRecebida));
    close(v[0]);
    if((arquivo = fopen("texto.txt", "w")) == NULL){
    	printf("erro a o abrir o arquivo\n");
    	return -1;
    }
    else{
    	char letra;
    	letra = stringRecebida[i];
    	while(letra != '\0'){
    		fputc(letra, arquivo);
    		i++;
    		letra = stringRecebida[i];
    	}

    	if((fclose(arquivo)) == 0){
      		printf("fechamento feito\n");
    	}
    	else{
      		printf("fechamento nao concluido\n");
    	}
	}

	}
	return 0;
}
