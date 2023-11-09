#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int pontuacao = 0;
pthread_mutex_t lock;

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
int compararResultado(Node *head, int qtd);

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
}

int main()
{
  pthread_t thread_id;
  pthread_mutex_init(&lock, NULL);
  pthread_create(&thread_id, NULL, atualizaPontuacao, NULL);

  while (1)
  {
    menu();
  }
  pthread_join(thread_id, NULL);
  pthread_mutex_destroy(&lock);
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
  printf("%d", pontuacao);
  int opcao;
  scanf("%d", &opcao);
  while (opcao > 5 && opcao < 1)
  {
    scanf("%d", &opcao);
  }

  switch (opcao)
  {
  case 1:
    jogar();
    break;
  case 2:
    /* code */
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

  char nomeJogador[20];
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
  printf("Voce conseguiu fazer em %d segundos!\n", pontuacao);
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
  while (1)
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
