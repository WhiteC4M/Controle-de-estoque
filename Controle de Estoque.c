#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>

int adicionar_item();
void editar_item();
void imprimir();
int remover_item();
void atualizar();
int ler_estoque();

typedef struct{
	char nome_do_item[50];
	int quantidade;
	int id;
}itens;

int main(void)
{	
	itens *item[100];
	int numero_da_operacao = 1, quant = 0, tam = 100;
	char arquivo[] = {"estoque.txt"};
	setlocale(LC_ALL, "Portuguese");
	
	quant += ler_estoque(item,arquivo);
	
	while(numero_da_operacao)
	{
		system("cls");
		printf("[0] - Encerrar\t\t[1] - Adicionar Item\n[2] - Editar Item\t[3] - Imprimir\n[4] - Remover Item\t[5] - Atualizar/Salvar\n[6] - Resetar estoque\n\n");
		
		printf("Digite o numero da operação desejada: ");
		scanf("%d", &numero_da_operacao);
		scanf("%c");
		
		switch(numero_da_operacao)
		{
			case 1:
				quant += adicionar_item(quant, item, tam);
			break;
			
			case 2:
				editar_item(quant, item, tam);
			break;
			
			case 3:
				imprimir(quant, item);
				system("pause");
			break;
			
			case 4:
			
				imprimir(quant, item);
				quant -= remover_item(quant,tam,item);
			break;
			
			case 5:
					atualizar(arquivo,quant,item);
			break;
			
			case 6:
				quant = 0;
			break;
		}
		
	}
	
}

int adicionar_item(int quant, itens **item, int tam)
{
	system("cls");
	if(quant < tam)
	{
		itens *novo = malloc(sizeof(itens));
		
		printf("Digite o nome do produto: ");
		fgets(novo->nome_do_item,50,stdin);
		
		printf("Digite a quantidade dele em estoque: ");
		scanf("%d", &novo->quantidade);
		
		novo->id = quant;
		
		item[quant] = novo;
		getchar();
		return 1;
	}
	else
	{
		printf("Não foi possivel encontrar ou criar o arquivo");
	}
}

void editar_item(int quant, itens **item, int tam)
{
	int escolha_de_id = 1, escolha_de_opcoes, saida_do_loop = 1;
	
	while(saida_do_loop)
	{
		system("cls");
		imprimir(quant, item);
		
		printf("Digite o ID do item que deseja editar: ");
		scanf("%d", &escolha_de_id);
		escolha_de_id -= 1;
		
		if(escolha_de_id <= quant && quant <= tam)
		{
			do
			{
					system("cls");
				printf("Item escolhido: %sQuantidade disponivel: %d\n\n", item[escolha_de_id]->nome_do_item, item[escolha_de_id]->quantidade);
				printf("------------Opções-----------\n");
				printf("[0] - Encerrar\t [1] - Apenas o nome\n[2] - Apenas a quantidade\t [3] - TUDO\n\n");
				printf("Digite o numero da operação desejada: ");
				scanf("%d", &escolha_de_opcoes);
				getchar();
				
				switch(escolha_de_opcoes)
				{
					case 0:
						saida_do_loop = 0;
					break;
					
					case 1:
						printf("Digite o novo nome do item: ");
						fgets(item[escolha_de_id]->nome_do_item, 50, stdin);
						
						printf("\nAlteração concluida!\n");
						printf("[%d] %sQuantidade: %d", item[escolha_de_id]->id+1, item[escolha_de_id]->nome_do_item, item[escolha_de_id]->quantidade);
						printf("\n\n");
						system("pause");
					break;
					
					case 2:
						printf("Digite a nova quantidade do item: ");
						scanf("%d", &item[escolha_de_id]->quantidade);
						
						printf("\nAlteração concluida!\n");
						printf("[%d] %sQuantidade: %d", item[escolha_de_id]->id+1, item[escolha_de_id]->nome_do_item, item[escolha_de_id]->quantidade);
						printf("\n\n");
						system("pause");
					break;
					
					case 3:
						printf("Digite o novo nome do item: ");
						fgets(item[escolha_de_id]->nome_do_item, 50, stdin);
						
						printf("Digite a nova quantidade do item: ");
						scanf("%d", &item[escolha_de_id]->quantidade);
						
						printf("\nAlteração concluida!\n");
						printf("[%d] %sQuantidade: %d", item[escolha_de_id]->id+1, item[escolha_de_id]->nome_do_item, item[escolha_de_id]->quantidade);
						printf("\n\n");
						system("pause");
					break;
				}
			}while(escolha_de_opcoes);
			
		}

	}
		
}

void imprimir(int quant, itens **item)
{
	int i;
	system("cls");
	printf("-----------ITENS EM ESTOQUE-----------\n");
	printf("ID	Nome\n\n");
	
	for(i = 0; i < quant; i++)
	{
		printf("[%d] \t%sQuantidade: %d", i+1 ,item[i]->nome_do_item, item[i]->quantidade);
		printf("\n-----------\n");
	}
	
	printf("\n\n");

}

int remover_item(int quant, int tam, itens **item)
{
	int escolha_de_id, i;
	
	printf("Digite o ID do item que deseja editar: ");
	scanf("%d", &escolha_de_id);
	escolha_de_id -= 1;
	
	if(escolha_de_id <= quant && quant <= tam) 
	{
		i = escolha_de_id;
		for(i = escolha_de_id; i < quant-1; i++)
		{
			strcpy(item[i]->nome_do_item, item[i+1]->nome_do_item);
			item[i]->id = item[i+1]->id;
			item[i]->quantidade = item[i+1]->quantidade;
		}
		return 1;
	}
	else
	{
		printf("nao foi possivel encontrar o ID");
	}
}

void atualizar(char arquivo[], int quant, itens **item)
{
	FILE *file = fopen(arquivo,"w");
	int i;
	
	if(file)
	{
		fprintf(file, "quantidade de itens: %d\n", quant);
		for(i = 0; i < quant; i++)
		{
			fputc('\n', file);
			fprintf(file,"[%d] ", i+1);
			fputs(item[i]->nome_do_item,file);
			
			fprintf(file,"quantidade disponivel: %d\n",item[i]->quantidade);
		}
		fclose(file);
	}
	else
	{
		printf("Não foi possivel encontrar ou acessar o arquivo");
	}
}

int ler_estoque(itens **item, char arquivo[])
{
	FILE *file = fopen(arquivo, "r");
	int quant = 0, i;
	
	itens *novo = malloc(sizeof(itens));
	
	if(file)
	{
		fscanf(file, "quantidade de itens: %d\n", &quant);
		
		if(quant)
		{
			for(i = 0; i < quant; i++)
			{
				fscanf(file,"[%d] ", &novo->id);
				fgets(novo->nome_do_item,50,file);
				fscanf(file,"quantidade disponivel: %d\n", &novo->quantidade);
				
				item[i] = novo;
				
				novo = malloc(sizeof(itens));
			}
		}
	}
	else
	{
		return 0;
	}
	fclose(file);
				
	return quant;
}
