#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define ANSI_RESET "\x1b[0m"
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_CYAN "\x1b[36m"

int pontuacao = 0;
pthread_mutex_t lock;
char nomeJogador[20];
int vidas = 2;
typedef struct Node
{
  int num;
  struct Node *next;
} Node;

typedef struct Player
{
  int pontuacao;
  char nome[20];
  char modo[20];
  struct Player *next;
} Player;

void menu();
void creditos();
void sair();
void inicializar();
void jogarInteiros();
void comoJogar();
void jogarCaracteres();
void gerarLista(int num, int dificuldade, Node **head, int mode);
void gerarResultado(Node **head);
void *atualizaPontuacao(void *vargp);
void verHallDaFama();
void inserirHallDaFama(char nome[20], int pontuacao, int mode);
void insertPlayer(Player **head, char nome[20], int pontuacao, char modo[20]);
void insertionSortPlayer(Player **head);
void imprimirHallDaFama(Player *head);
int compararResultado(Node *head, Node *resposta);
int buscarNumero(Node *head, int num);
void scanearResposta(Node **resposta, int qtd, int mode);
void insertAtEnd(Node **head, int num);
void imprimir(Node *head, int mode);
void freeList(Node **head);
void insertAtEnd(Node **head, int num);
void insert(Node **head, int num);

int pontuacaoCount = 1;

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
  system("cls");
  printf(ANSI_GREEN "[1] - Jogar\n" ANSI_RESET);
  printf("[2] - Hall da Fama\n");
  printf("[3] - Como Jogar\n");
  printf("[4] - Creditos\n");
  printf(ANSI_RED "[5] - Sair\n" ANSI_RESET);
  int opcao;
  int mode;
  scanf("%d", &opcao);
  while (opcao > 5 || opcao < 1)
  {
    printf(ANSI_RED "Opção inválida. Por favor, escolha um número entre 1 e 5:\n" ANSI_RESET);
    scanf("%d", &opcao);
  }

  switch (opcao)
  {
  case 1:
    vidas = 2;
    printf(ANSI_GREEN "Escolha o Modo de Jogo!!\n" ANSI_RESET);
    printf("[1] - Ordenar Inteiros\n");
    printf("[2] - Ordenar Caracteres\n");
    scanf("%d", &mode);
    if (mode == 1)
    {
      jogarInteiros();
    }
    if (mode == 2)
    {
      jogarCaracteres();
    }
    break;
  case 2:
    verHallDaFama();
    break;
  case 3:
    comoJogar();
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
  system("cls");
  printf("Feito por:\n");
  printf(ANSI_CYAN "Luís Otávio Mingati e Pedro Henrique Andriotti\n" ANSI_RESET);
  printf("Turma 3A de CC\n");
  printf(ANSI_YELLOW "Cesar School\n\n" ANSI_RESET);

  printf(ANSI_YELLOW "Pressione enter para voltar ao menu.\n" ANSI_RESET);
  scanf("%*c");
  if (getchar() == '\n')
  {
    menu();
  }
  else
  {
    menu();
  }
}

void sair()
{
  printf(ANSI_GREEN "Obrigado por jogar! :)\n" ANSI_RESET);
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
  system("cls");

  printf("Digite seu primeiro nome: ");

  scanf(" %19s", nomeJogador);

  printf(ANSI_GREEN "Prepare-se %s, o jogo vai começar!\n" ANSI_RESET, nomeJogador);
  sleep(3);

  for (int i = 3; i > 0; i--)
  {
    system("cls");
    printf("%d...", i);
    fflush(stdout);
    sleep(1);
  }

  system("cls");
}

void jogarInteiros()
{
  int mode = 1;
  pontuacaoCount = 1;
  pthread_t thread_id;
  pthread_mutex_init(&lock, NULL);
  pthread_create(&thread_id, NULL, atualizaPontuacao, NULL);
  Node *resposta = NULL;
  Node *head = NULL;
  int passou = 0;
  inicializar();
  do
  {
    int quantidade = 5;
    int dificuldade = 2;
    gerarLista(quantidade, dificuldade, &head, mode);
    imprimir(head, mode);
    scanearResposta(&resposta, quantidade, mode);
    gerarResultado(&head);
    if (compararResultado(head, resposta))
    {
      printf(ANSI_GREEN "Parabens, voce acertou! Agora vai ser um pouco mais difícil!\n" ANSI_RESET);
      passou = 1;
    }
    else
    {
      vidas--;
      if (vidas == 0)
      {
        printf(ANSI_RED "Você perdeu :(\nTente a sorte jogando novamente!" ANSI_RESET);
        break;
      }
      printf(ANSI_RED "Voce errou, sorteando um novo array...\nVoce agora tem %d vida" ANSI_RESET, vidas);
      passou = 0;
    }
    printf("\n\n");
    freeList(&head);
    freeList(&resposta);
  } while (passou == 0);
  passou = 0;
  if (vidas > 0)
  {

    do
    {
      int quantidade = 6;
      int dificuldade = 10;
      gerarLista(quantidade, dificuldade, &head, mode);
      imprimir(head, mode);
      scanearResposta(&resposta, quantidade, mode);
      gerarResultado(&head);
      if (compararResultado(head, resposta))
      {
        printf(ANSI_GREEN "Parabens, voce acertou! Voce esta indo para o nivel 3.\n" ANSI_RESET);
        passou = 1;
      }
      else
      {
        vidas--;
        if (vidas == 0)
        {
          printf(ANSI_RED "Você perdeu :(\nTente a sorte jogando novamente!" ANSI_RESET);
          break;
        }
        printf(ANSI_RED "Voce errou, sorteando um novo array...\nVoce agora tem %d vida" ANSI_RESET, vidas);
        passou = 0;
      }
      printf("\n\n");
      freeList(&head);
      freeList(&resposta);

    } while (passou == 0);
  }
  passou = 0;
  if (vidas > 0)
  {

    do
    {
      int quantidade = 7;
      int dificuldade = 25;
      gerarLista(quantidade, dificuldade, &head, mode);
      imprimir(head, mode);
      scanearResposta(&resposta, quantidade, mode);
      gerarResultado(&head);
      if (compararResultado(head, resposta))
      {
        printf(ANSI_GREEN "Parabens, voce acertou! Agora quero ver!\n" ANSI_RESET);
        passou = 1;
      }
      else
      {
        vidas--;
        if (vidas == 0)
        {
          printf(ANSI_RED "Você perdeu :(\nTente a sorte jogando novamente!" ANSI_RESET);
          break;
        }
        printf(ANSI_RED "Voce errou, sorteando um novo array...\nVoce agora tem %d vida" ANSI_RESET, vidas);
        passou = 0;
      }
      printf("\n\n");
      freeList(&head);
      freeList(&resposta);

    } while (passou == 0);
  }
  passou = 0;
  if (vidas > 0)
  {

    do
    {
      int quantidade = 8;
      int dificuldade = 50;
      gerarLista(quantidade, dificuldade, &head, mode);
      imprimir(head, mode);
      scanearResposta(&resposta, quantidade, mode);
      gerarResultado(&head);
      if (compararResultado(head, resposta))
      {
        printf(ANSI_GREEN "Parabens, voce acertou! So falta mais um!\n" ANSI_RESET);
        passou = 1;
      }
      else
      {
        vidas--;
        if (vidas == 0)
        {
          printf(ANSI_RED "Você perdeu :(\nTente a sorte jogando novamente!" ANSI_RESET);
          break;
        }
        printf(ANSI_RED "Voce errou, sorteando um novo array...\nVoce agora tem %d vida" ANSI_RESET, vidas);
        passou = 0;
      }
      printf("\n\n");
      freeList(&head);
      freeList(&resposta);

    } while (passou == 0);
  }
  passou = 0;
  if (vidas > 0)
  {

    do
    {
      int quantidade = 9;
      int dificuldade = 100;
      gerarLista(quantidade, dificuldade, &head, mode);
      imprimir(head, mode);
      scanearResposta(&resposta, quantidade, mode);
      gerarResultado(&head);
      if (compararResultado(head, resposta))
      {
        printf(ANSI_GREEN "Parabens, voce acertou! Voce conseguiu finalizar a Sorting Race!!!\n" ANSI_RESET);
        passou = 1;
      }
      else
      {
        vidas--;
        if (vidas == 0)
        {
          printf(ANSI_RED "Você perdeu :(\nTente a sorte jogando novamente!" ANSI_RESET);
          break;
        }
        printf(ANSI_RED "Voce errou, sorteando um novo array...\nVoce agora tem %d vida" ANSI_RESET, vidas);
        passou = 0;
      }
      printf("\n\n");
      freeList(&head);
      freeList(&resposta);

    } while (passou == 0);
  }
  pontuacaoCount = 0;
  pthread_join(thread_id, NULL);
  pthread_mutex_destroy(&lock);
  if (vidas > 0)
  {
    printf(ANSI_CYAN "Voce conseguiu fazer em %d segundos!\n" ANSI_RESET, pontuacao);
    inserirHallDaFama(nomeJogador, pontuacao, mode);
  }
  pontuacao = 0;
}

void jogarCaracteres()
{
  int mode = 2;
  pontuacaoCount = 1;
  pthread_t thread_id;
  pthread_mutex_init(&lock, NULL);
  pthread_create(&thread_id, NULL, atualizaPontuacao, NULL);
  Node *resposta = NULL;
  Node *head = NULL;
  int passou = 0;

  inicializar();

  do
  {
    int quantidade = 5;
    int dificuldade = 0;
    gerarLista(quantidade, dificuldade, &head, mode);
    imprimir(head, mode);
    gerarResultado(&head);
    scanearResposta(&resposta, quantidade, mode);
    if (compararResultado(head, resposta))
    {
      printf(ANSI_GREEN "Parabens, voce acertou! Agora vai ser um pouco mais difícil!\n" ANSI_RESET);
      passou = 1;
    }
    else
    {
      vidas--;
      if (vidas == 0)
      {
        printf(ANSI_RED "Você perdeu :(\nTente a sorte jogando novamente!" ANSI_RESET);
        break;
      }
      printf(ANSI_RED "Voce errou, sorteando um novo array...\nVoce agora tem %d vida" ANSI_RESET, vidas);
      passou = 0;
    }
    printf("\n\n");
    freeList(&head);
    freeList(&resposta);
  } while (passou == 0);
  passou = 0;
  if (vidas > 0)
  {

    do
    {
      int quantidade = 6;
      int dificuldade = 0;
      gerarLista(quantidade, dificuldade, &head, mode);
      imprimir(head, mode);
      gerarResultado(&head);
      scanearResposta(&resposta, quantidade, mode);
      if (compararResultado(head, resposta))
      {
        printf(ANSI_GREEN "Parabens, voce acertou! Voce esta indo para o nivel 3.\n" ANSI_RESET);
        passou = 1;
      }
      else
      {
        vidas--;
        if (vidas == 0)
        {
          printf(ANSI_RED "Você perdeu :(\nTente a sorte jogando novamente!" ANSI_RESET);
          break;
        }
        printf(ANSI_RED "Voce errou, sorteando um novo array...\nVoce agora tem %d vida" ANSI_RESET, vidas);
        passou = 0;
      }
      printf("\n\n");
      freeList(&head);
      freeList(&resposta);

    } while (passou == 0);
  }
  passou = 0;
  if (vidas > 0)
  {

    do
    {
      int quantidade = 7;
      int dificuldade = 0;
      gerarLista(quantidade, dificuldade, &head, mode);
      imprimir(head, mode);
      gerarResultado(&head);
      scanearResposta(&resposta, quantidade, mode);
      if (compararResultado(head, resposta))
      {
        printf(ANSI_GREEN "Parabens, voce acertou! Agora quero ver!\n" ANSI_RESET);
        passou = 1;
      }
      else
      {
        vidas--;
        if (vidas == 0)
        {
          printf(ANSI_RED "Você perdeu :(\nTente a sorte jogando novamente!" ANSI_RESET);
          break;
        }
        printf(ANSI_RED "Voce errou, sorteando um novo array...\nVoce agora tem %d vida" ANSI_RESET, vidas);
        passou = 0;
      }
      printf("\n\n");
      freeList(&head);
      freeList(&resposta);

    } while (passou == 0);
  }
  passou = 0;
  if (vidas > 0)
  {

    do
    {
      int quantidade = 8;
      int dificuldade = 0;
      gerarLista(quantidade, dificuldade, &head, mode);
      imprimir(head, mode);
      scanearResposta(&resposta, quantidade, mode);
      gerarResultado(&head);
      if (compararResultado(head, resposta))
      {
        printf(ANSI_GREEN "Parabens, voce acertou! So falta mais um!\n" ANSI_RESET);
        passou = 1;
      }
      else
      {
        vidas--;
        if (vidas == 0)
        {
          printf(ANSI_RED "Você perdeu :(\nTente a sorte jogando novamente!" ANSI_RESET);
          break;
        }
        printf(ANSI_RED "Voce errou, sorteando um novo array...\nVoce agora tem %d vida" ANSI_RESET, vidas);
        passou = 0;
      }
      printf("\n\n");
      freeList(&head);
      freeList(&resposta);

    } while (passou == 0);
  }
  passou = 0;
  if (vidas > 0)
  {

    do
    {
      int quantidade = 9;
      int dificuldade = 0;
      gerarLista(quantidade, dificuldade, &head, mode);
      imprimir(head, mode);
      scanearResposta(&resposta, quantidade, mode);
      gerarResultado(&head);
      if (compararResultado(head, resposta))
      {
        printf(ANSI_GREEN "Parabens, voce acertou! Voce conseguiu finalizar a Sorting Race!!!\n" ANSI_RESET);
        passou = 1;
      }
      else
      {
        vidas--;
        if (vidas == 0)
        {
          printf(ANSI_RED "Você perdeu :(\nTente a sorte jogando novamente!" ANSI_RESET);
          break;
        }
        printf(ANSI_RED "Voce errou, sorteando um novo array...\nVoce agora tem %d vida" ANSI_RESET, vidas);
        passou = 0;
      }
      printf("\n\n");
      freeList(&head);
      freeList(&resposta);

    } while (passou == 0);
  }
  pontuacaoCount = 0;
  pthread_join(thread_id, NULL);
  pthread_mutex_destroy(&lock);
  if (vidas > 0)
  {
    printf(ANSI_CYAN "Voce conseguiu fazer em %d segundos!\n" ANSI_RESET, pontuacao);
    inserirHallDaFama(nomeJogador, pontuacao, mode);
  }
  pontuacao = 0;
}

void gerarLista(int num, int dificuldade, Node **head, int mode)
{
  if (mode == 1)
  {
    while (num > 0)
    {
      int random;
      do
      {
        random = rand() % (10 * dificuldade);
      } while (buscarNumero(*head, random));
      insert(head, random);
      num--;
    }
  }
  else if (mode == 2)
  {
    while (num > 0)
    {
      int random;
      do
      {
        random = rand() % 26;
      } while (buscarNumero(*head, random));
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

int compararResultado(Node *head, Node *resposta)
{
  while (head != NULL && resposta != NULL)
  {
    if (head->num != resposta->num)
    {
      return 0;
    }
    head = head->next;
    resposta = resposta->next;
  }
  return 1;
}

void inserirHallDaFama(char nome[20], int pontuacao, int mode)
{
  FILE *arquivo = fopen("hallDaFama.txt", "a");
  if (arquivo == NULL)
  {
    perror("Erro ao abrir o arquivo");
    return;
  }
  if (mode == 1)
  {
    fprintf(arquivo, "%s %d Int\n", nome, pontuacao);
  }
  else
  {
    fprintf(arquivo, "%s %d Char\n", nome, pontuacao);
  }
  fclose(arquivo);
}

void verHallDaFama()
{
  Player *head = NULL;
  system("cls");
  fflush(stdout);
  printf(ANSI_BLUE "Nome - Menor Tempo - Modo\n\n" ANSI_RESET);
  FILE *arquivo = fopen("hallDaFama.txt", "r");
  char nome[20];
  int pontuacao;
  char modo[20];
  while (fscanf(arquivo, "%s %d %s", nome, &pontuacao, modo) != EOF)
  {
    insertPlayer(&head, nome, pontuacao, modo);
  }
  insertionSortPlayer(&head);
  imprimirHallDaFama(head);
  printf(ANSI_YELLOW "Pressione enter para voltar ao menu.\n" ANSI_RESET);
  scanf("%*c");
  if (getchar() == '\n')
  {
    fclose(arquivo);
    menu();
  }
  else
  {
    fclose(arquivo);
    menu();
  }
}

void comoJogar()
{
  system("cls");
  fflush(stdout);
  printf(ANSI_GREEN "Sort Race e um jogo de raciocínio rapido.\n" ANSI_RESET);
  printf("O objetivo e reescrever o array gerado aleatoriamente em ordem crescente.\n");
  printf("A cada array ordenado, voce passa para o proximo nivel que sera ainda mais dificil.\n");
  printf("Voce tem 2 vidas, se errar 2 vezes, voce perde.\n");
  printf("A pontuacao e baseada no tempo que voce leva para ordenar todos os arrays.\n");
  printf("Faca com calma e divirta-se!\n\n");

  printf(ANSI_YELLOW "Pressione enter para voltar ao menu.\n" ANSI_RESET);
  scanf("%*c");
  if (getchar() == '\n')
  {
    menu();
  }
  else
  {
    menu();
  }
}

void insertPlayer(Player **head, char nome[20], int pontuacao, char modo[20])
{
  Player *new = (Player *)malloc(sizeof(Player));
  new->pontuacao = pontuacao;
  strcpy(new->nome, nome);
  strcpy(new->modo, modo);
  new->next = *head;
  *head = new;
}

void insertionSortPlayer(Player **head)
{
  Player *sorted = NULL;

  Player *current = *head;
  while (current != NULL)
  {
    Player *next = current->next;

    if (sorted == NULL || sorted->pontuacao >= current->pontuacao)
    {
      current->next = sorted;
      sorted = current;
    }
    else
    {
      Player *temp = sorted;
      while (temp->next != NULL && temp->next->pontuacao < current->pontuacao)
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

void imprimirHallDaFama(Player *head)
{
  Player *aux = head;
  while (aux != NULL)
  {
    printf("%s - %d - Modo %s\n", aux->nome, aux->pontuacao, aux->modo);
    aux = aux->next;
  }
  printf("\n");
}

int buscarNumero(Node *head, int num)
{
  while (head != NULL)
  {
    if (head->num == num)
    {
      return 1;
    }
    head = head->next;
  }
  return 0;
}

void scanearResposta(Node **resposta, int qtd, int mode)
{
  while (qtd--)
  {
    if (mode == 1)
    {
      int num;
      scanf("%d", &num);
      insertAtEnd(resposta, num);
    }
    else
    {
      char caractere;
      do
      {
        scanf(" %c", &caractere);
      } while (caractere == ' ' || caractere == '\n');
      int num = caractere - 97;
      insertAtEnd(resposta, num);
    }
  }
}

void insertAtEnd(Node **head, int num)
{
  Node *new = (Node *)malloc(sizeof(Node));
  new->num = num;
  new->next = NULL;
  if (*head == NULL)
  {
    *head = new;
    return;
  }
  Node *aux = *head;
  while (aux->next != NULL)
  {
    aux = aux->next;
  }
  aux->next = new;
}

void imprimir(Node *head, int mode)
{
  Node *aux = head;
  if (mode == 1)
  {
    while (aux != NULL)
    {
      printf("%d ", aux->num);
      aux = aux->next;
    }
    printf("\n");
  }
  else if (mode == 2)
  {
    while (aux != NULL)
    {
      printf("%c ", (aux->num + 97));
      aux = aux->next;
    }
    printf("\n");
  }
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

void insert(Node **head, int num)
{
  Node *new = (Node *)malloc(sizeof(Node));
  new->num = num;
  new->next = *head;
  *head = new;
}
