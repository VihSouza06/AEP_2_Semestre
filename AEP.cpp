#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>

void criptografia(char *senha){
	int i;
	for(i = 0; i < strlen(senha); i++){
		senha[i] = senha[i]+10;	
	}
}

void descriptografia(char *senha){
	int i;
	for(i = 0; i < strlen(senha); i++){
		senha[i] = senha[i]-10;
	}
}

void menu(){
	int opcao, tam = 0,i, y;
	char nome[50] [50], achanome[50], j[50], x[50], senha[50] [50], senhaDescriptografada[50] [50];
	char c;
 
	setlocale(LC_ALL,"Portuguese");
 
	FILE *arquivo;
 
	arquivo = fopen("teste-aep.txt", "r+");
	if(arquivo == NULL){
		arquivo = fopen("teste-aep.txt", "w+");
	}
 
	fseek(arquivo, 0, SEEK_SET);
 
	while(fscanf(arquivo, "%s", nome[tam]) != EOF){
		fscanf(arquivo, "%s", senha[tam++]);
	}
 
    do {
        printf("\n    MENU DE OPÇÕES:    \n");
        printf("1 -> Cadastrar Usuário \n");
        printf("2 -> Alterar Usuário \n");
        printf("3 -> Excluir Usuário \n");
        printf("4 -> Listar Usuários \n");
        printf("5 -> Voltar para o menu \n");
        printf("0 -> Sair \n");
        printf("\n Escolha uma opção: ");
        scanf("%d", &opcao);
        while ((c=getchar())!='\n'&&c!=EOF);
       
       system("cls");
       
        switch (opcao) {
            case 1:
               printf("Digite o nome do usuário: ");
    		   fgets(nome[tam], 50, stdin);
    		   fprintf(arquivo, "%-50s", nome[tam]);
    		   nome[tam][strcspn(nome[tam], "\n")] = '\0';
    		   
    		   printf("Digite a senha do usuário: ");
    		   fgets(senha[tam++], 50, stdin);
    		   
               criptografia(senha[tam-1]);
               fprintf(arquivo, "%-50s", senha[tam-1]);
               
			   printf("Usuário adicionado com sucesso! \n");
               break;
               
            case 2:
            	printf("Qual o nome do usuario que deseja alterar: ");
            	scanf("%s", achanome);
            	while ((c=getchar())!='\n'&&c!=EOF);
            	
            	for(i = 0; i < tam && strcmp(achanome, nome[i]) != 0; i++);
            	
				if(i != tam){
					printf("Digite o novo nome do usuário: ");
					fgets(nome[i], 50, stdin);
					printf("Digite a nova senha: ");
					fgets(senha[i], 50, stdin);
					criptografia(senha[i]);
					
					fseek(arquivo, 0, SEEK_SET);
					y = 0;
            	
            		while(fscanf(arquivo, "%s", x) != EOF){
    					fscanf(arquivo, "%s", j);
    	
    					if(strcmp(achanome, x) == 0){
    						fseek(arquivo, y, SEEK_SET);
    						fprintf(arquivo, "%-50s", nome[i]);
    						fprintf(arquivo, "%-50s", senha[i]);
    						fseek(arquivo, 0, SEEK_END);
    					} else {
    						y = ftell(arquivo);
						}
					}
				} else {
					printf("Usuario não encontrado!");
				}
				break;
                
            case 3:
            	printf("Digite o nome do usuario que deseja excluir: ");
				scanf("%s", achanome);
				while ((c=getchar())!='\n'&&c!=EOF);
				
				for(i = 0; i < tam && strcmp(achanome, nome[i]) != 0; i++);
				
				if(tam != i){
					for(y = i+1; y < tam; y++){
						strcpy(nome[y-1], nome[y]);
						strcpy(senha[y-1], senha[y]);
					}
					tam--;
					
					fclose(arquivo);
					remove("teste-aep.txt");
					arquivo = fopen("teste-aep.txt", "w+");
					
					for(i = 0; i < tam; i++){
						fprintf(arquivo, "%-50s", nome[i]);
						fprintf(arquivo, "%-50s", senha[i]);
					}
					
					printf("Usuário excluido com sucesso!\n");
				} else {
					printf("Usuario não encontrado!"); 
				}
                break;
                
            case 4:
     	  		if (tam == 0) {
    				printf("\n Nenhum usuário encontrado! \n");
				} else {
					printf("\n    LISTA DE USUÁRIOS:    \n");
					for (int i = 0; i < tam; i++) {
						strcpy(x, senha[i]);
						descriptografia(x);
    		    		printf("\nNome: %s\n", nome[i]);
    					printf("Senha: %s\n", x);
    				}
			    }
                break;
                
            case 5:
                menu();
                break; 
				   
            case 0:  
            	fclose(arquivo);
                printf(" PROGRAMA FINALIZADO \n");
                break;
        }
    } while (opcao != 0);
}

int main() {
    
	menu();

	return 0;
}
