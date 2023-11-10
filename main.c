#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int pontuacao = 0;
pthread_mutex_t lock;
char nomeJogador[20];

typedef struct Node
{
  int num;
  struct Node *next;
} Node;

void menu();
void creditos();
void sair();
void inicializar();
void jogar();
void gerarLista(int num, int dificuldade, Node **head);
void gerarResultado(Node **head);
void *atualizaPontuacao(void *vargp);
void verHallDaFama();
void inserirHallDaFama(char nome[20], int pontuacao);

int compararResultado(Node *head, int qtd);
int pontuacaoCount = 1;

void insert(Node **head, int num)
{
  Node *new = (Node *)malloc(sizeof(Node));
  new->num = num;
  new->next = *head;
  *head = new;
}

void imprimir(Node *head)
{
  Node *aux = head;
  while (aux != NULL)
  {
    printf("%d ", aux->num);
    aux = aux->next;
  }
  printf("\n");
}

void freeList(Node **head)
{
  Node *aux = *head;
  while (aux != NULL)
  {
    Node *temp = aux;
    aux = aux->next;
    free(temp);
  }
  *head = NULL;
}

int main()
{
  srand(time(NULL));
  while (1)
  {
    menu();
  }
  return 0;
}

void menu()
{
  system("clear");
  printf("[1] - Jogar\n");
  printf("[2] - Hall da Fama\n");
  printf("[3] - Como Jogar\n");
  printf("[4] - Creditos\n");
  printf("[5] - Sair\n");
  int opcao;
  scanf("%d", &opcao);
  while (opcao > 5 || opcao < 1)
  { 
    printf("Opção inválida. Por favor, escolha um número entre 1 e 5:\n");
    scanf("%d", &opcao);
  }

  switch (opcao)
  {
  case 1:
    jogar();
    break;
  case 2:
    verHallDaFama();
    break;
  case 3:
    /* code */
    break;
  case 4:
    creditos();
    break;
  case 5:
    sair();
    break;
  }
}

void creditos()
{
  system("clear");
  printf("Feito por:\n");
  sleep(2);
  printf("Luís Otávio Mingati e Pedro Henrique Andriotti\n");
  sleep(2);
  printf("Turma 3A de CC\n");
  printf("Cesar School\n");
  sleep(3);
}

void sair()
{
  printf("Obrigado por jogar! :)\n");
  printf("Saindo");
  for (int i = 0; i < 3; i++)
  {
    printf(".");
    fflush(stdout);
    sleep(1);
  }
  exit(0);
}

void inicializar()
{
  system("clear");

  printf("Digite seu primeiro nome: ");

  scanf(" %19s", nomeJogador);

  printf("Prepare-se %s, o jogo vai começar!\n", nomeJogador);
  sleep(3);

  for (int i = 3; i > 0; i--)
  {
    system("clear");
    printf("%d...", i);
    fflush(stdout);
    sleep(1);
  }

  system("clear");
}

void jogar()
{
  pontuacaoCount = 1;
  pthread_t thread_id;
  pthread_mutex_init(&lock, NULL);
  pthread_create(&thread_id, NULL, atualizaPontuacao, NULL);

  Node *head = NULL;
  int passou = 0;
  inicializar();
  do
  {
    int quantidade = 5;
    int dificuldade = 1;
    gerarLista(quantidade, dificuldade, &head);
    imprimir(head);
    gerarResultado(&head);
    imprimir(head);
    if (compararResultado(head, quantidade))
    {
      printf("Parabens, voce acertou! Agora vai ser um pouco mais difícil!\n");
      passou = 1;
    }
    else
    {
      printf("Voce errou, sorteando um novo array...\n");
      passou = 0;
    }
    freeList(&head);
  } while (passou == 0);
  passou = 0;
  do
  {
    int quantidade = 6;
    int dificuldade = 2;
    gerarLista(quantidade, dificuldade, &head);
    imprimir(head);
    gerarResultado(&head);
    imprimir(head);
    if (compararResultado(head, quantidade))
    {
      printf("Parabens, voce acertou! Agora vai ser um pouco mais difícil!\n");
      passou = 1;
    }
    else
    {
      printf("Voce errou, sorteando um novo array...\n");
      passou = 0;
    }
    freeList(&head);
  } while (passou == 0);
  passou = 0;

  do
  {
    int quantidade = 7;
    int dificuldade = 3;
    gerarLista(quantidade, dificuldade, &head);
    imprimir(head);
    gerarResultado(&head);
    imprimir(head);
    if (compararResultado(head, quantidade))
    {
      printf("Parabens, voce acertou! Agora vai ser um pouco mais difícil!\n");
      passou = 1;
    }
    else
    {
      printf("Voce errou, sorteando um novo array...\n");
      passou = 0;
    }
    freeList(&head);
  } while (passou == 0);
  passou = 0;

  do
  {
    int quantidade = 8;
    int dificuldade = 4;
    gerarLista(quantidade, dificuldade, &head);
    imprimir(head);
    gerarResultado(&head);
    imprimir(head);
    if (compararResultado(head, quantidade))
    {
      printf("Parabens, voce acertou! Agora vai ser um pouco mais difícil!\n");
      passou = 1;
    }
    else
    {
      printf("Voce errou, sorteando um novo array...\n");
      passou = 0;
    }
    freeList(&head);
  } while (passou == 0);
  passou = 0;

  do
  {
    int quantidade = 9;
    int dificuldade = 5;
    gerarLista(quantidade, dificuldade, &head);
    imprimir(head);
    gerarResultado(&head);
    imprimir(head);
    if (compararResultado(head, quantidade))
    {
      printf("Parabens, voce acertou! Voce conseguiu finalizar a Sorting Race!!!\n");
      passou = 1;
    }
    else
    {
      printf("Voce errou, sorteando um novo array...\n");
      passou = 0;
    }
    freeList(&head);
  } while (passou == 0);
  pontuacaoCount = 0;
  pthread_join(thread_id, NULL);
  pthread_mutex_destroy(&lock);
  printf("Voce conseguiu fazer em %d segundos!\n", pontuacao);
  inserirHallDaFama(nomeJogador, pontuacao);
  pontuacao = 0;
}

void gerarLista(int num, int dificuldade, Node **head)
{
  while (num > 0)
  {
    if (dificuldade == 1)
    {
      int random = rand() % 20;
      insert(head, random);
      num--;
    }
    else if (dificuldade == 2)
    {
      int random = rand() % 100;
      insert(head, random);
      num--;
    }
    else if (dificuldade == 3)
    {
      int random = rand() % 250;
      insert(head, random);
      num--;
    }
    else if (dificuldade == 4)
    {
      int random = rand() % 500;
      insert(head, random);
      num--;
    }
    else if (dificuldade == 5)
    {
      int random = rand() % 1000;
      insert(head, random);
      num--;
    }
  }
}

void gerarResultado(Node **head)
{
  Node *sorted = NULL;

  Node *current = *head;
  while (current != NULL)
  {
    Node *next = current->next;

    if (sorted == NULL || sorted->num >= current->num)
    {
      current->next = sorted;
      sorted = current;
    }
    else
    {
      Node *temp = sorted;
      while (temp->next != NULL && temp->next->num < current->num)
      {
        temp = temp->next;
      }
      current->next = temp->next;
      temp->next = current;
    }
    current = next;
  }

  *head = sorted;
}

void *atualizaPontuacao(void *vargp)
{
  while (pontuacaoCount)
  {
    pthread_mutex_lock(&lock);
    pontuacao++;
    pthread_mutex_unlock(&lock);
    sleep(1);
  }
  return NULL;
}

int compararResultado(Node *head, int qtd) 
{
  while (qtd--)
  {
    int num;
    scanf("%d", &num);
    if (head->num != num)
    {
      return 0;
    }
    head = head->next;
  }
  return 1;
}

void inserirHallDaFama(char nome[20], int pontuacao) {
  FILE *arquivo = fopen("hallDaFama.txt", "a");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }
  fprintf(arquivo, "%s %d\n", nome, pontuacao);
  fclose(arquivo);
}

void verHallDaFama() {
  FILE *arquivo = fopen("hallDaFama.txt", "r");
  char nome[20];
  int pontuacao;
  while (fscanf(arquivo, "%s %d", nome, &pontuacao) != EOF) {
    printf("%s %d\n", nome, pontuacao);
  }
  sleep(3);
  fclose(arquivo);
}