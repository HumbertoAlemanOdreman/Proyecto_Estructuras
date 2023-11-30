#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __STDC_LIMIT_MACROS
#include <stdint.h>

#define MALLOC_ART (struct ArticleNode *)malloc(sizeof(struct ArticleNode))
#define MALLOC_VEN (struct VendorNode *)malloc(sizeof(struct VendorNode))
#define MALLOC_CLI (struct ClientNode *)malloc(sizeof(struct ClientNode))

#define CLR_BUF             \
  while (getchar() != '\n') \
  {                         \
  }
#define ENTER_CONTINUAR                        \
  printf("  Presione ENTER para continuar\n"); \
  CLR_BUF;                                     \
  getchar();
#define TECLA_VALIDA                                       \
  printf("  ERROR: debe seleccionar una opcion valida\n"); \
  ENTER_CONTINUAR;

#define CLEAR if(system("cls")) { system("clear"); }
#define COL_SIZE 20

struct ArticleNode *ArticlesList = NULL;
struct VendorNode *VendorList = NULL;
struct ClientNode *ClientList = NULL;

struct Article
{
  char code[COL_SIZE];
  char name[COL_SIZE];
  float price;
  int ammount;
};

struct Date
{
  int day;
  int month;
  int year;
};

struct Vendor
{
  char name[COL_SIZE];
  char ci[10];
  struct Date date;
  int commission;
};

struct Client
{
  char name[COL_SIZE];
  char ci[10];
  char dir[COL_SIZE];
  char cellphone[COL_SIZE];
};

struct ArticleNode
{
  int key;
  struct Article article;
  struct ArticleNode *next;
};

struct VendorNode
{
  struct Vendor vendor;
  struct VendorNode *next;
};

struct ClientNode
{
  struct Client client;
  struct ClientNode *next;
};

char InputChar()
{
  char sel;
  scanf(" %c%*[^\n]", &sel);
  return sel;
};

int IsInRange(int num, int min, int max) { return (num >= min && num <= max); }

int OmmitableInputString(char *str, char *format)
{
  char buffer[128];
  CLR_BUF;
  scanf(format, buffer);
  if (buffer[0] == '~')
  {
    return 1;
  }
  strcpy(str, buffer);
  return 0;
};

int OmmitableInputNumber(int *num, char *format)
{
  char buffer[128];
  CLR_BUF;
  scanf(format, buffer);
  if (buffer[0] == '~')
  {
    return 1;
  }
  *num = atoi(buffer);
  return 0;
};

int OmmitableInputFloat(float *num, char *format)
{
  char buffer[128];
  CLR_BUF;
  scanf(format, buffer);
  if (buffer[0] == '~')
  {
    return 1;
  }
  *num = atof(buffer);
  return 0;
};

void InputString(char *str, char *format)
{
  char buffer[128];
  CLR_BUF;
  scanf(format, buffer);
  strcpy(str, buffer);
};

void InputNumber(int *num, char *format)
{
  char buffer[128];
  CLR_BUF;
  scanf(format, buffer);
  *num = atoi(buffer);
};

void InputFloat(float *num, char *format)
{
  char buffer[128];
  CLR_BUF;
  scanf(format, buffer);
  *num = atof(buffer);
};

int GetLastKey(struct ArticleNode *ArticlesList)
{
  if (ArticlesList == NULL)
  {
    return 0;
  }
  int max = 0;
  do
  {
    if (ArticlesList->key > max)
    {
      max = ArticlesList->key;
    }
    ArticlesList = ArticlesList->next;
  } while (ArticlesList != NULL);
  return ++max;
};

struct ArticleNode *PreviousItemArt(struct ArticleNode *List, struct ArticleNode *article)
{
  if (List == NULL)
  {
    return NULL;
  }
  if (List == article)
  {
    return NULL;
  }
  while (List->next != NULL)
  {
    if (List->next == article)
    {
      return List;
    }
    List = List->next;
  }
  return NULL;
};

struct VendorNode *PreviousItemVen(struct VendorNode *List, struct VendorNode *vendor)
{
  if (List == NULL)
  {
    return NULL;
  }
  if (List == vendor)
  {
    return NULL;
  }
  while (List->next != NULL)
  {
    if (List->next == vendor)
    {
      return List;
    }
    List = List->next;
  }
  return NULL;
};

struct ClientNode *PreviousItemCli(struct ClientNode *List, struct ClientNode *client)
{
  if (List == NULL)
  {
    return NULL;
  }
  if (List == client)
  {
    return NULL;
  }
  while (List->next != NULL)
  {
    if (List->next == client)
    {
      return List;
    }
    List = List->next;
  }
  return NULL;
};

struct Article CreateItemArt(char code[], char name[], float price, int ammount)
{
  struct Article return_value;
  for (int i = 0; i < COL_SIZE - 1; i++)
  {
    return_value.code[i] = code[i];
    return_value.name[i] = name[i];
  }
  return_value.price = price;
  return_value.ammount = ammount;
  return return_value;
};

struct Vendor CreateItemVen(char name[], char ci[], struct Date date, int commission)
{
  struct Vendor return_value;
  for (int i = 0; i < COL_SIZE - 1; i++)
  {
    return_value.name[i] = name[i];
    return_value.ci[i] = ci[i];
  }
  return_value.date = date;
  return_value.commission = commission;
  return return_value;
};

struct Client CreateItemCli(char name[], char ci[], char dir[], char cellphone[])
{
  struct Client return_value;
  for (int i = 0; i < COL_SIZE - 1; i++)
  {
    return_value.name[i] = name[i];
    return_value.ci[i] = ci[i];
    return_value.dir[i] = dir[i];
    return_value.cellphone[i] = cellphone[i];
  }
  return return_value;
};

void PrintItemAsTableArt(struct Article article, char text[])
{
  printf("  ||===============================||\n");
  printf("  ||%31s||\n", &text[0]);
  printf("  ||===============================||\n");
  printf("  | Codigo   | %20s |\n", article.code);
  printf("  | Nombre   | %20s |\n", article.name);
  printf("  | Precio   | %19.2f$ |\n", article.price);
  printf("  | Cantidad | %20d |\n", article.ammount);
  printf("  ||===============================||\n");
};

void PrintItemAsTableVen(struct Vendor vendor, char text[])
{
  printf("  ||===============================||\n");
  printf("  ||%31s||\n", &text[0]);
  printf("  ||===============================||\n");
  printf("  | Nombre   | %20s |\n", vendor.name);
  printf("  | C.I      | %20s |\n", vendor.ci);
  printf("  | Fecha    | %12d/%2d/%4d |\n", vendor.date.day, vendor.date.month, vendor.date.year);
  printf("  | Comision | %19d%% |\n", vendor.commission);
  printf("  ||===============================||\n");
};

void PrintItemAsTableCli(struct Client client, char text[])
{
  printf("  ||===============================||\n");
  printf("  ||%31s||\n", &text[0]);
  printf("  ||===============================||\n");
  printf("  | Nombre   | %20s |\n", client.name);
  printf("  | C.I      | %20s |\n", client.ci);
  printf("  | Direccion| %20s |\n", client.dir);
  printf("  | Telefono | %20s |\n", client.cellphone);
  printf("  ||===============================||\n");
};

void PrintItemListArt(struct ArticleNode *List)
{
  CLEAR;

  int item = 1;
  char tmp[20];
  struct ArticleNode *articulo_inicial = List;
  struct ArticleNode *aux = List;

  while (List != NULL)
  {
    CLEAR;
    sprintf(tmp, "Item: %d | LLave: %d", item, List->key);
    PrintItemAsTableArt(List->article, tmp);
    printf("\n");

    if (PreviousItemArt(articulo_inicial, List) != NULL)
    {
      printf("  [P] Articulo Previo\n");
    }
    if (List->next != NULL)
    {
      printf("  [S] Articulo Siguiente\n");
    }
    printf("  [T] Terminar Visualizacion\n");
    switch (getchar())
    {
    case 'T':
    case 't':
      return;
      break;
    case 'S':
    case 's':
      if (List->next == NULL)
      {
        break;
      }
      item++;
      List = List->next;
      break;
    case 'P':
    case 'p':
      aux = PreviousItemArt(articulo_inicial, List);
      if (aux != NULL)
      {
        List = aux;
        item--;
      }
      break;
    }
  }
};

void PrintItemListVen(struct VendorNode *List)
{
  CLEAR;

  int item = 1;
  char tmp[20];
  struct VendorNode *initial_vendor = List;
  struct VendorNode *aux = List;

  while (List != NULL)
  {
    CLEAR;
    sprintf(tmp, "Item: %d", item);
    PrintItemAsTableVen(List->vendor, tmp);
    printf("\n");

    if (PreviousItemVen(initial_vendor, List) != NULL)
    {
      printf("  [P] Vendedor Previo\n");
    }
    if (List->next != NULL)
    {
      printf("  [S] Vendedor Siguiente\n");
    }
    printf("  [T] Terminar Visualizacion\n");
    switch (getchar())
    {
    case 'T':
    case 't':
      return;
      break;
    case 'S':
    case 's':
      if (List->next == NULL)
      {
        break;
      }
      item++;
      List = List->next;
      break;
    case 'P':
    case 'p':
      aux = PreviousItemVen(initial_vendor, List);
      if (aux != NULL)
      {
        List = aux;
        item--;
      }
      break;
    }
  }
};

void PrintItemListCli(struct ClientNode *List)
{
  CLEAR;

  int item = 1;
  char tmp[20];
  struct ClientNode *initial_client = List;
  struct ClientNode *aux = List;

  while (List != NULL)
  {
    CLEAR;
    sprintf(tmp, "Item: %d", item);
    PrintItemAsTableCli(List->client, tmp);
    printf("\n");

    if (PreviousItemCli(initial_client, List) != NULL)
    {
      printf("  [P] Cliente Previo\n");
    }
    if (List->next != NULL)
    {
      printf("  [S] Cliente Siguiente\n");
    }
    printf("  [T] Terminar Visualizacion\n");
    switch (getchar())
    {
    case 'T':
    case 't':
      return;
      break;
    case 'S':
    case 's':
      if (List->next == NULL)
      {
        break;
      }
      item++;
      List = List->next;
      break;
    case 'P':
    case 'p':
      aux = PreviousItemCli(initial_client, List);
      if (aux != NULL)
      {
        List = aux;
        item--;
      }
      break;
    }
  }
};

void CreateListArt(struct ArticleNode **List, struct Article article_to_add)
{
  CLEAR;
  if (*List == NULL)
  {
    PrintItemAsTableArt(article_to_add, "Creando lista con articulo: ");
    *List = MALLOC_ART;
    (*List)->article = article_to_add;
    (*List)->next = NULL;
    (*List)->key = 0;
    return;
  }
  printf("La lista ya existe, conteniendo los siguientes articulos: \n");
  PrintItemListArt(*List);
};

void CreateListVen(struct VendorNode **List, struct Vendor vendor_to_add)
{
  CLEAR;
  if (*List == NULL)
  {
    PrintItemAsTableVen(vendor_to_add, "Creando lista con articulo: ");
    *List = MALLOC_VEN;
    (*List)->vendor = vendor_to_add;
    (*List)->next = NULL;
    return;
  }
  printf("La lista ya existe, conteniendo los siguientes articulos: \n");
  PrintItemListVen(*List);
};

void CreateListCli(struct ClientNode **List, struct Client client_to_add)
{
  CLEAR;
  if (*List == NULL)
  {
    PrintItemAsTableCli(client_to_add, "Creando lista con articulo: ");
    *List = MALLOC_CLI;
    (*List)->client = client_to_add;
    (*List)->next = NULL;
    return;
  }
  printf("La lista ya existe, conteniendo los siguientes articulos: \n");
  PrintItemListCli(*List);
};

void InsertItemArt(struct ArticleNode **List, struct Article article_to_add, int position)
{
  if (*List == NULL)
  {
    CreateListArt(List, article_to_add);
    return;
  }
  struct ArticleNode *aux = MALLOC_ART;
  struct ArticleNode *aux_2 = MALLOC_ART;
  if (position <= 0)
  {
    aux->article = article_to_add;
    aux->key = GetLastKey(*List);
    aux->next = *List;
    *List = aux;
    return;
  }
  aux = *List;
  int key = GetLastKey(*List);
  while (aux->next != NULL && position-- > 1)
  {
    aux = aux->next;
  }
  aux_2 = aux->next;
  aux->next = MALLOC_ART;
  aux->next->article = article_to_add;
  aux->next->key = key;
  aux->next->next = aux_2;
};

void AppendItemArt(struct ArticleNode **List, struct Article article_to_add)
{
  if (*List == NULL)
  {
    CreateListArt(List, article_to_add);
    return;
  }
  struct ArticleNode *aux = *List;
  int key = GetLastKey(*List);
  while (aux->next != NULL)
  {
    aux = aux->next;
  }
  aux->next = MALLOC_ART;
  aux->next->article = article_to_add;
  aux->next->key = key;
  aux->next->next = NULL;
};

void AppendItemVen(struct VendorNode **List, struct Vendor vendor_to_add)
{
  if (*List == NULL)
  {
    CreateListVen(List, vendor_to_add);
    return;
  }
  struct VendorNode *aux = *List;
  while (aux->next != NULL)
  {
    aux = aux->next;
  }
  aux->next = MALLOC_VEN;
  aux->next->vendor = vendor_to_add;
  aux->next->next = NULL;
};

void AppendItemCli(struct ClientNode **List, struct Client client_to_add)
{
  if (*List == NULL)
  {
    CreateListCli(List, client_to_add);
    return;
  }
  struct ClientNode *aux = *List;
  while (aux->next != NULL)
  {
    aux = aux->next;
  }
  aux->next = MALLOC_CLI;
  aux->next->client = client_to_add;
  aux->next->next = NULL;
};

void InsertItemVen(struct VendorNode **List, struct Vendor vendor_to_add, int position)
{
  if (*List == NULL)
  {
    CreateListVen(List, vendor_to_add);
    return;
  }
  struct VendorNode *aux = MALLOC_VEN;
  struct VendorNode *aux_2 = MALLOC_VEN;
  if (position <= 0)
  {
    aux->vendor = vendor_to_add;
    aux->next = *List;
    *List = aux;
    return;
  }
  aux = *List;
  while (aux->next != NULL && position-- > 1)
  {
    aux = aux->next;
  }
  aux_2 = aux->next;
  aux->next = MALLOC_VEN;
  aux->next->vendor = vendor_to_add;
  aux->next->next = aux_2;
};

void InsertItemCli(struct ClientNode **List, struct Client client_to_add, int position)
{
  if (*List == NULL)
  {
    CreateListCli(List, client_to_add);
    return;
  }
  struct ClientNode *aux = MALLOC_CLI;
  struct ClientNode *aux_2 = MALLOC_CLI;
  if (position <= 0)
  {
    aux->client = client_to_add;
    aux->next = *List;
    *List = aux;
    return;
  }
  aux = *List;
  while (aux->next != NULL && position-- > 1)
  {
    aux = aux->next;
  }
  aux_2 = aux->next;
  aux->next = MALLOC_CLI;
  aux->next->client = client_to_add;
  aux->next->next = aux_2;
};

struct ArticleNode *LookForArticle(struct ArticleNode *List, struct Article data, int field)
{
  if (List == NULL)
  {
    return NULL;
  }
  struct ArticleNode *aux = List;
  struct ArticleNode *ret = NULL;
  while (aux != NULL)
  {
    switch (field)
    {
    case 0:
      if (!strcmp(data.code, aux->article.code))
      {
        AppendItemArt(&ret, aux->article);
      }
      break;
    case 1:
      if (!strcmp(data.name, aux->article.name))
      {
        AppendItemArt(&ret, aux->article);
      }
      break;
    case 2:
      if (data.price == aux->article.price)
      {
        AppendItemArt(&ret, aux->article);
      }
      break;
    case 3:
      if (data.ammount == aux->article.ammount)
      {
        AppendItemArt(&ret, aux->article);
      }
      break;
    };
    aux = aux->next;
  };
  return ret;
};

struct VendorNode *LookForVendor(struct VendorNode *List, struct Vendor data, int field)
{
  if (List == NULL)
  {
    return NULL;
  }
  struct VendorNode *aux = List;
  struct VendorNode *ret = NULL;
  while (aux != NULL)
  {
    switch (field)
    {
    case 0:
      if (!strcmp(data.name, aux->vendor.name))
      {
        AppendItemVen(&ret, aux->vendor);
      }
      break;
    case 1:
      if (!strcmp(data.ci, aux->vendor.ci))
      {
        AppendItemVen(&ret, aux->vendor);
      }
      break;
    case 2:
      if (data.date.day == aux->vendor.date.day && data.date.month == aux->vendor.date.month && data.date.year == aux->vendor.date.year)
      {
        AppendItemVen(&ret, aux->vendor);
      }
      break;
    case 3:
      if (data.commission == aux->vendor.commission)
      {
        AppendItemVen(&ret, aux->vendor);
      }
      break;
    };
    aux = aux->next;
  };
  return ret;
};

struct ClientNode *LookForClient(struct ClientNode *List, struct Client data, int field)
{
  if (List == NULL)
  {
    return NULL;
  }
  struct ClientNode *aux = List;
  struct ClientNode *ret = NULL;
  while (aux != NULL)
  {
    switch (field)
    {
    case 0:
      if (!strcmp(data.name, aux->client.name))
      {
        AppendItemCli(&ret, aux->client);
      }
      break;
    case 1:
      if (!strcmp(data.ci, aux->client.ci))
      {
        AppendItemCli(&ret, aux->client);
      }
      break;
    case 2:
      if (!strcmp(data.dir, aux->client.dir))
      {
        AppendItemCli(&ret, aux->client);
      }
      break;
    case 3:
      if (!strcmp(data.cellphone, aux->client.cellphone))
      {
        AppendItemCli(&ret, aux->client);
      }
      break;
    };
    aux = aux->next;
  };
  return ret;
};

int RemoveItemArt(struct ArticleNode **List, int position)
{
  if (*List == NULL)
  {
    return 1;
  }
  if ((*List)->next == NULL)
  {
    free(*List);
    *List = NULL;
    return 0;
  }
  struct ArticleNode *aux = MALLOC_ART;
  struct ArticleNode *aux_2 = MALLOC_ART;
  if (position <= 0)
  {
    aux = (*List)->next;
    free(*List);
    *List = aux;
    return 0;
  }
  aux = *List;
  while (aux->next != NULL && position-- > 0)
  {
    aux = aux->next;
  }
  aux_2 = aux->next;
  aux = PreviousItemArt(*List, aux);
  free(aux->next);
  aux->next = aux_2;
  return 0;
};

int RemoveItemVen(struct VendorNode **List, int position)
{
  if (*List == NULL)
  {
    return 1;
  }
  if ((*List)->next == NULL)
  {
    free(*List);
    *List = NULL;
    return 0;
  }
  struct VendorNode *aux = MALLOC_VEN;
  struct VendorNode *aux_2 = MALLOC_VEN;
  if (position <= 0)
  {
    aux = (*List)->next;
    free(*List);
    *List = aux;
    return 0;
  }
  aux = *List;
  while (aux->next != NULL && position-- > 0)
  {
    aux = aux->next;
  }
  aux_2 = aux->next;
  aux = PreviousItemVen(*List, aux);
  free(aux->next);
  aux->next = aux_2;
  return 0;
};

int RemoveItemCli(struct ClientNode **List, int position)
{
  if (*List == NULL)
  {
    return 1;
  }
  if ((*List)->next == NULL)
  {
    free(*List);
    *List = NULL;
    return 0;
  }
  struct ClientNode *aux = MALLOC_CLI;
  struct ClientNode *aux_2 = MALLOC_CLI;
  if (position <= 0)
  {
    aux = (*List)->next;
    free(*List);
    *List = aux;
    return 0;
  }
  aux = *List;
  while (aux->next != NULL && position-- > 0)
  {
    aux = aux->next;
  }
  aux_2 = aux->next;
  aux = PreviousItemCli(*List, aux);
  free(aux->next);
  aux->next = aux_2;
  return 0;
};

struct ArticleNode *GetNodeArt(struct ArticleNode *List, int position)
{
  if (List == NULL)
  {
    return NULL;
  }
  if ((List)->next == NULL || position <= 0)
  {
    return List;
  }
  struct ArticleNode *aux = MALLOC_ART;
  aux = List;
  while (aux->next != NULL && position-- > 0)
  {
    aux = aux->next;
  }
  return aux;
};

struct VendorNode *GetNodeVen(struct VendorNode *List, int position)
{
  struct Date date = {0, 0, 0};
  if (List == NULL)
  {
    return NULL;
  }
  if ((List)->next == NULL || position <= 0)
  {
    return List;
  }
  struct VendorNode *aux = MALLOC_VEN;
  aux = List;
  while (aux->next != NULL && position-- > 0)
  {
    aux = aux->next;
  }
  return aux;
};

struct ClientNode *GetNodeCli(struct ClientNode *List, int position)
{
  struct Date date = {0, 0, 0};
  if (List == NULL)
  {
    return NULL;
  }
  if ((List)->next == NULL || position <= 0)
  {
    return List;
  }
  struct ClientNode *aux = MALLOC_CLI;
  aux = List;
  while (aux->next != NULL && position-- > 0)
  {
    aux = aux->next;
  }
  return aux;
};

void ReadFileArt(struct ArticleNode **List, char dir[])
{
  FILE *f;
  f = fopen(dir, "r");
  if (f == NULL)
  {
    return;
  }

  // Vaciamos la lista
  while (*List != NULL)
  {
    RemoveItemArt(List, 0);
  }

  int input_code, key = 0;
  struct ArticleNode *aux = MALLOC_ART;
  struct ArticleNode *ret = aux;
  struct Article article;

  input_code = fscanf(f, "%*[^\n]\n");
  if (input_code == EOF)
  {
    fclose(f);
    return;
  }
  while (1)
  {
    input_code = fscanf(f, "%s", article.code);
    input_code = fscanf(f, "%s", article.name);
    input_code = fscanf(f, "%f", &article.price);
    input_code = fscanf(f, "%d", &article.ammount);
    if (input_code != EOF)
    {
      printf("\n");
      aux->article = article;
      aux->key = key++;
      aux->next = MALLOC_ART;
      aux = aux->next;
      continue;
    }
    struct ArticleNode *prev = PreviousItemArt(ret, aux);
    free(prev->next);
    prev->next = NULL;
    *List = ret;
    fclose(f);
    break;
  }
};

void ReadFileVen(struct VendorNode **List, char dir[])
{
  FILE *f;
  f = fopen(dir, "r");
  if (f == NULL)
  {
    return;
  }

  // Vaciamos la lista
  while (*List != NULL)
  {
    RemoveItemVen(List, 0);
  }

  int input_code, key = 0;
  struct VendorNode *aux = MALLOC_VEN;
  struct VendorNode *ret = aux;
  struct Vendor vendor;

  input_code = fscanf(f, "%*[^\n]\n");
  if (input_code == EOF)
  {
    fclose(f);
    return;
  }
  while (1)
  {
    input_code = fscanf(f, "%s", vendor.name);
    input_code = fscanf(f, "%s", vendor.ci);
    input_code = fscanf(f, "%d/%d/%d", &vendor.date.day, &vendor.date.month, &vendor.date.year);
    input_code = fscanf(f, "%d", &vendor.commission);
    if (input_code != EOF)
    {
      aux->vendor = vendor;
      aux->next = MALLOC_VEN;
      aux = aux->next;
      continue;
    }
    struct VendorNode *prev = PreviousItemVen(ret, aux);
    free(prev->next);
    prev->next = NULL;
    *List = ret;
    fclose(f);
    break;
  }
};

void ReadFileCli(struct ClientNode **List, char dir[])
{
  FILE *f;
  f = fopen(dir, "r");
  if (f == NULL)
  {
    return;
  }

  if (*List != NULL)
  {
    RemoveItemCli(List, 0);
  }

  int input_code, key = 0;
  struct ClientNode *aux = MALLOC_CLI;
  struct ClientNode *ret = aux;
  struct Client client;

  input_code = fscanf(f, "%*[^\n]\n");
  if (input_code == EOF)
  {
    fclose(f);
    return;
  }
  while (1)
  {
    input_code = fscanf(f, "%s", client.name);
    input_code = fscanf(f, "%s", client.ci);
    input_code = fscanf(f, "%s", client.dir);
    input_code = fscanf(f, "%s", client.cellphone);
    if (input_code != EOF)
    {
      aux->client = client;
      aux->next = MALLOC_CLI;
      aux = aux->next;
      continue;
    }
    struct ClientNode *prev = PreviousItemCli(ret, aux);
    free(prev->next);
    prev->next = NULL;
    *List = ret;
    fclose(f);
    break;
  }
};

void SaveFileArt(struct ArticleNode **List, char dir[])
{
  FILE *f;
  f = fopen(dir, "w");
  if (f == NULL)
  {
    fclose(f);
    printf("  El archivo no se ha podido crear, no se ha podido guardar\n");
    ENTER_CONTINUAR;
    return;
  }

  struct ArticleNode *aux = *List;

  if (*List == NULL)
  {
    fprintf(f, "");
    return;
  }
  fprintf(f, "ARTICULOS\n");
  while (aux != NULL)
  {
    fprintf(f, "%s\n", aux->article.code);
    fprintf(f, "%s\n", aux->article.name);
    fprintf(f, "%2f\n", aux->article.price);
    fprintf(f, "%d\n", aux->article.ammount);
    aux = aux->next;
  }
  fclose(f);
};

void SaveFileVen(struct VendorNode **List, char dir[])
{
  FILE *f;
  f = fopen(dir, "w");
  if (f == NULL)
  {
    return;
  }

  struct VendorNode *aux = *List;

  while (aux != NULL)
  {
    fprintf(f, "%s ", aux->vendor.name);
    fprintf(f, "%s ", aux->vendor.ci);
    fprintf(f, "%d/%d/%d ", aux->vendor.date.day, aux->vendor.date.month, aux->vendor.date.year);
    fprintf(f, "%d\n", aux->vendor.commission);
    aux = aux->next;
  }
  fclose(f);
};

void SaveFileCli(struct ClientNode **List, char dir[])
{
  FILE *f;
  f = fopen(dir, "w");
  if (f == NULL)
  {
    return;
  }
  printf("Escribiendo en el archivo %s\n\n", &dir[0]);

  struct ClientNode *aux = *List;

  while (aux != NULL)
  {
    fprintf(f, "%s ", aux->client.name);
    fprintf(f, "%s ", aux->client.ci);
    fprintf(f, "%s ", aux->client.dir);
    fprintf(f, "%s\n", aux->client.cellphone);
    aux = aux->next;
  }
  fclose(f);
};

void PrintMenuArticulos(void)
{
  CLEAR;
  printf("\n");
  printf("  ||===============================||\n");
  printf("  || Menu Articulos                ||\n");
  printf("  ||===============================||\n");
  printf("  || [1] Agregar un Articulo       ||\n");
  printf("  || [2] Remover un Articulo       ||\n");
  printf("  || [3] Modificar un Articulo     ||\n");
  printf("  || [4] Leer Lista de Articulos   ||\n");
  printf("  || [5] Buscar Articulo en Lista  ||\n");
  printf("  ||                               ||\n");
  printf("  || [0] Regresar                  ||\n");
  printf("  ||===============================||\n");
};

void PrintMenuVendedores(void)
{
  CLEAR;
  printf("\n");
  printf("  ||===============================||\n");
  printf("  || Menu Vendedores               ||\n");
  printf("  ||===============================||\n");
  printf("  || [1] Agregar un Vendedor       ||\n");
  printf("  || [2] Remover un Vendedor       ||\n");
  printf("  || [3] Modificar un Vendedor     ||\n");
  printf("  || [4] Leer Lista de Vendedores  ||\n");
  printf("  || [5] Buscar Vendedor en Lista  ||\n");
  printf("  ||                               ||\n");
  printf("  || [0] Regresar                  ||\n");
  printf("  ||===============================||\n");
};

void PrintMenuClientes(void)
{
  CLEAR;
  printf("\n");
  printf("  ||===============================||\n");
  printf("  || Menu Clientes                 ||\n");
  printf("  ||===============================||\n");
  printf("  || [1] Agregar un Cliente        ||\n");
  printf("  || [2] Remover un Cliente        ||\n");
  printf("  || [3] Modificar un Cliente      ||\n");
  printf("  || [4] Leer Lista de Clientes    ||\n");
  printf("  || [5] Buscar Clientes en Lista  ||\n");
  printf("  ||                               ||\n");
  printf("  || [0] Regresar                  ||\n");
  printf("  ||===============================||\n");
};

void MenuManejoArticulos()
{
  char sel[2];
  char buffer[64];
  int position;
  struct Article art;
  struct ArticleNode *aux = GetNodeArt(ArticlesList, position);
  while (1)
  {
    PrintMenuArticulos();
    printf("\n");
    printf("  Seleccion: ");
    scanf("%1s", sel);
    switch (sel[0])
    {
    //
    // CASO AGREGAR ARTICULO
    //
    case '1':
      art.code[0] = '\0';
      art.name[0] = '\0';
      art.price = 0;
      art.ammount = 0;

      while (1)
      {
        CLEAR;
        PrintMenuArticulos();
        printf("  ||                               ||\n");
        PrintItemAsTableArt(art, "Articulo Actual");
        printf("\n");
        if (art.code[0] == '\0')
        {
          printf("  Ingrese el Codigo del articulo: ");
          InputString(art.code, "%19s");
          continue;
        }
        if (art.name[0] == '\0')
        {
          printf("  Ingrese el Nombre del articulo: ");
          InputString(art.name, "%19s");
          continue;
        }
        if (art.price <= 0)
        {
          printf("  Ingrese el Precio del articulo: ");
          InputFloat(&art.price, "%10s");
          continue;
        }
        if (art.ammount <= 0)
        {
          printf("  Ingrese la Cantidad de articulos: ");
          InputNumber(&art.ammount, "%10s");
          continue;
        }
        break;
      }

      while (1)
      {
        position = -2;
        CLEAR;
        PrintMenuArticulos();
        printf("  ||                               ||\n");
        PrintItemAsTableArt(art, "Articulo a Agregar");
        printf("\n");
        printf("  Ingrese la posicion donde agregar el articulo: \n");
        printf("  [0, a-z, A-Z] Agregar al inicio de la lista\n");
        printf("  [-1] Agregar al final de la lista\n");
        printf("  Posicion: ");
        InputNumber(&position, "%10s");
        if (position < -1)
        {
          continue;
        }
        if (position == -1)
        {
          position = INT32_MAX;
        }
        break;
      }
      InsertItemArt(&ArticlesList, art, position);
      SaveFileArt(&ArticlesList, "Articulos.txt");
      CLEAR;
      PrintMenuArticulos();
      printf("  ||                               ||\n");
      PrintItemAsTableArt(art, "Articulo Agregado");
      printf("\n");
      printf("  Articulo agregado a la lista!\n");
      ENTER_CONTINUAR;
      break;
    //
    // CASO ELIMINAR ARTICULO
    //
    case '2':
      if (ArticlesList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede eliminar nada");
        ENTER_CONTINUAR;
        break;
      }

      while (1)
      {
        position = -2;
        CLEAR;
        PrintMenuArticulos();
        printf("\n");
        printf("  Ingrese la posicion del articulo a eliminar: \n");
        printf("  [0, a-z, A-Z] Eliminar el primer articulo de la lista\n");
        printf("  [-1] Eliminar el ultimo articulo de la lista\n");
        printf("  Posicion: ");
        InputNumber(&position, "%10s");
        if (position < -1)
        {
          continue;
        }
        if (position == -1)
        {
          position = INT32_MAX;
        }
        break;
      }

      art = GetNodeArt(ArticlesList, position)->article;
      if (art.name[0])
      {
        CLEAR;
        PrintMenuArticulos();
        printf("  ||                               ||\n");
        PrintItemAsTableArt(art, "Articulo a Eliminar");
        printf("\n");
        printf("  Eliminar %s de la lista?\n", art.name);
        printf("  [S] Eliminar\n");
        printf("  [N] No Eliminar\n");
        CLR_BUF;
        scanf("%1s", buffer);
      }

      if (!(buffer[0] == 's' || buffer[0] == 'S'))
      {
        printf("  No se ha eliminado ningun elemento\n");
      }
      else if (RemoveItemArt(&ArticlesList, position))
      {
        printf("  La lista es NULL, no se ha podido eliminar ningun elemento\n");
      }
      else
      {
        printf("  Se ha eliminado %s de la lista\n", art.name);
      }
      SaveFileArt(&ArticlesList, "Articulos.txt");
      ENTER_CONTINUAR;
      break;
    //
    // CASO MODIFICAR ARTICULO
    //
    case '3':
      if (ArticlesList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede modificar nada");
        ENTER_CONTINUAR;
        break;
      }

      art.code[0] = '\0';
      art.name[0] = '\0';
      art.price = 0;
      art.ammount = 0;

      while (ArticlesList != NULL)
      {
        position = -2;
        CLEAR;
        PrintMenuArticulos();
        printf("\n");
        printf("  Ingrese la posicion del articulo a modificar: \n");
        printf("  [0, a-z, A-Z] Modificar el primer articulo de la lista\n");
        printf("  [-1] Modificar el ultimo articulo de la lista\n");
        printf("  Posicion: ");
        InputNumber(&position, "%10s");
        if (position < -1)
        {
          continue;
        }
        if (position == -1)
        {
          position = INT32_MAX;
        }
        break;
      }

      while (1)
      {
        CLEAR;
        PrintMenuArticulos();
        printf("  ||                               ||\n");
        PrintItemAsTableArt(aux->article, "Articulo a Modificar");
        printf("\n");
        printf("  [~] No modificar\n");
        if (art.code[0] == '\0')
        {
          printf("  Ingrese el Nuevo Codigo del articulo: ");
          if (OmmitableInputString(art.code, "%19s"))
          {
            strcpy(art.code, aux->article.code);
          }
          if (art.code[0] != '\0')
          {
            strcpy(aux->article.code, art.code);
          }
          continue;
        }
        if (art.name[0] == '\0')
        {
          printf("  Ingrese el Nombre del articulo: ");
          if (OmmitableInputString(art.name, "%19s"))
          {
            strcpy(art.name, aux->article.name);
          }
          if (art.name[0] != '\0')
          {
            strcpy(aux->article.name, art.name);
          }
          continue;
        }
        if (art.price <= 0)
        {
          printf("  Ingrese el Precio del articulo: ");
          if (OmmitableInputFloat(&art.price, "%10s"))
          {
            art.price = aux->article.price;
          }
          if (art.price > 0)
          {
            aux->article.price = art.price;
          }
          continue;
        }
        if (art.ammount <= 0)
        {
          printf("  Ingrese la Cantidad de articulos: ");
          if (OmmitableInputNumber(&art.ammount, "%10s"))
          {
            art.ammount = aux->article.ammount;
          }
          if (art.ammount > 0)
          {
            aux->article.ammount = art.ammount;
          }
          continue;
        }
        break;
      }
      SaveFileArt(&ArticlesList, "Articulos.txt");

      CLEAR;
      PrintMenuArticulos();
      printf("  ||                               ||\n");
      PrintItemAsTableArt(art, "Articulo Modificado");
      printf("\n");
      ENTER_CONTINUAR;
      break;
    case '4':
      if (ArticlesList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede visualizar");
        ENTER_CONTINUAR;
        break;
      }
      PrintItemListArt(ArticlesList);
      break;
    case '5':
      if (ArticlesList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede realizar busquedas");
        ENTER_CONTINUAR;
        break;
      }

      CLEAR;
      PrintMenuArticulos();
      printf("\n");

      printf("  Seleccione el campo por el que va a buscar\n");
      printf("  [0] Codigo\n");
      printf("  [1] Nombre\n");
      printf("  [2] Precio\n");
      printf("  [3] Cantidad\n");
      InputString(sel, "%2s");

      art.code[0] = '\0';
      art.name[0] = '\0';
      art.price = 0;
      art.ammount = 0;

      printf("  Ingrese");
      switch (sel[0])
      {
      case '0':
        printf(" el Codigo a buscar: ");
        InputString(art.code, "%19s");
        break;
      case '1':
        printf(" el Nombre a buscar: ");
        InputString(art.name, "%19s");
        break;
      case '2':
        printf(" el Precio a buscar: ");
        InputFloat(&art.price, "%19s");
        break;
      case '3':
        printf(" la Cantidad a buscar: ");
        InputNumber(&art.ammount, "%19s");
        break;
      default:
        CLEAR;
        PrintMenuArticulos();
        printf("\n  El campo ingresado no existe, vuelvalo a intentar\n");
        ENTER_CONTINUAR;
        return;
        break;
      };
      aux = NULL;
      aux = LookForArticle(ArticlesList, art, sel[0] - '0');

      if (aux == NULL)
      {
        printf("  No se encontro ningun elemento con esa informacion\n");
        ENTER_CONTINUAR;
        break;
      }
      printf("  Articulo(s) entontrados\n");
      ENTER_CONTINUAR;
      PrintItemListArt(aux);
      break;
    case '0':
      return;
      break;
    default:
      TECLA_VALIDA;
      break;
    }
  }
};

void MenuManejoVendedores()
{
  char sel[2];
  char buffer[64];
  int position;
  struct Vendor ven;
  struct VendorNode *aux = GetNodeVen(VendorList, position);
  while (1)
  {
    PrintMenuVendedores();
    printf("\n");
    printf("  Seleccion: ");
    scanf("%1s", sel);
    switch (sel[0])
    {
    //
    // CASO AGREGAR VENDEDOR
    //
    case '1':
      ven.name[0] = '\0';
      ven.ci[0] = '\0';
      ven.date.day = 0;
      ven.date.month = 0;
      ven.date.year = 0;
      ven.commission = 0;

      while (1)
      {
        CLEAR;
        PrintMenuVendedores();
        printf("  ||                               ||\n");
        PrintItemAsTableVen(ven, "Vendedor Actual");
        printf("\n");
        if (ven.name[0] == '\0')
        {
          printf("  Ingrese el Nombre del vendedor: ");
          InputString(ven.name, "%19s");
          continue;
        }
        if (ven.ci[0] == '\0')
        {
          printf("  Ingrese la Cedula de Identidad del vendedor: ");
          InputString(ven.ci, "%10s");
          continue;
        }
        printf("\n");
        if (ven.date.year <= 0)
        {
          printf("  Ingrese el Anio en que el vendedor se unio: ");
          InputNumber(&ven.date.year, "%5s");
          if (!IsInRange(ven.date.year, 1, 2100))
          {
            ven.date.year = 0;
          }
          continue;
        }
        if (ven.date.month <= 0)
        {
          printf("  Ingrese el Mes en que el vendedor se unio: ");
          InputNumber(&ven.date.month, "%3s");
          if (!IsInRange(ven.date.month, 1, 12))
          {
            ven.date.month = 0;
          }
          continue;
        }
        if (ven.date.day <= 0)
        {
          printf("  Ingrese el Dia en que el vendedor se unio: ");
          InputNumber(&ven.date.day, "%3s");
          if (!IsInRange(ven.date.day, 1, 31))
          {
            ven.date.day = 0;
          }
          continue;
        }
        if (ven.commission <= 0)
        {
          printf("  Ingrese Porcentaje de Comision del vendedor: ");
          InputNumber(&ven.commission, "%4s");
          if (!IsInRange(ven.commission, 0, 100))
          {
            ven.commission = 0;
          }
          continue;
        }
        break;
      }

      while (1)
      {
        position = -2;
        CLEAR;
        PrintMenuVendedores();
        printf("  ||                               ||\n");
        PrintItemAsTableVen(ven, "Vendedor a Agregar");
        printf("\n");
        printf("  Ingrese la posicion donde agregar el vendedor: \n");
        printf("  [0, a-z, A-Z] Agregar al inicio de la lista\n");
        printf("  [-1] Agregar al final de la lista\n");
        printf("  Posicion: ");
        CLR_BUF;
        scanf("%10s", buffer);
        position = atoi(buffer);
        if (position == -1)
        {
          position = INT32_MAX;
        }
        if (position < -1)
        {
          continue;
        }
        break;
      }
      InsertItemVen(&VendorList, ven, position);
      SaveFileVen(&VendorList, "Vendedores.txt");
      CLEAR;
      PrintMenuVendedores();
      printf("  ||                               ||\n");
      PrintItemAsTableVen(ven, "Vendedor Agregado");
      printf("\n");
      printf("  Vendedor agregado a la lista!\n");
      ENTER_CONTINUAR;
      break;
    //
    // CASO ELIMINAR VENDEDOR
    //
    case '2':
      if (VendorList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede eliminar nada");
        ENTER_CONTINUAR;
        break;
      }

      while (1)
      {
        position = -2;
        CLEAR;
        PrintMenuVendedores();
        printf("\n");
        printf("  Ingrese la posicion del vendedor a eliminar: \n");
        printf("  [0, a-z, A-Z] Eliminar el primer vendedor de la lista\n");
        printf("  [-1] Eliminar el ultimo vendedor de la lista\n");
        printf("  Posicion: ");
        InputNumber(&position, "%10s");
        if (position == -1)
        {
          position = INT32_MAX;
        }
        if (position < -1)
        {
          continue;
        }
        break;
      }

      ven = GetNodeVen(VendorList, position)->vendor;
      if (ven.name[0])
      {
        CLEAR;
        PrintMenuVendedores();
        printf("  ||                               ||\n");
        PrintItemAsTableVen(ven, "Vendedor a Eliminar");
        printf("\n");
        printf("  Eliminar a %s de la lista?\n", ven.name);
        printf("  [S] Eliminar\n");
        printf("  [N] No Eliminar\n");
        CLR_BUF;
        scanf("%1s", buffer);
      }
      if (!(buffer[0] == 's' || buffer[0] == 'S'))
      {
        printf("  No se ha eliminado ningun elemento\n");
      }
      else if (RemoveItemVen(&VendorList, position))
      {
        printf("  La lista es NULL, no se ha podido eliminar ningun elemento\n");
      }
      else
      {
        printf("  Se ha eliminado %s de la lista\n", ven.name);
      }
      SaveFileVen(&VendorList, "Vendedores.txt");
      ENTER_CONTINUAR;
      break;
    //
    // CASO MODIFICAR VENDEDOR
    //
    case '3':
      if (VendorList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede modificar nada");
        ENTER_CONTINUAR;
        break;
      }

      ven.name[0] = '\0';
      ven.ci[0] = '\0';
      ven.date.day = 0;
      ven.date.month = 0;
      ven.date.year = 0;
      ven.commission = 0;

      while (VendorList != NULL)
      {
        position = -2;
        CLEAR;
        PrintMenuVendedores();
        printf("\n");
        printf("  Ingrese la posicion del vendedor a modificar: \n");
        printf("  [0, a-z, A-Z] Modificar el primer vendedor de la lista\n");
        printf("  [-1] Modificar el ultimo vendedor de la lista\n");
        printf("  Posicion: ");
        CLR_BUF;
        scanf("%10s", buffer);
        position = atoi(buffer);
        if (position == -1)
        {
          position = INT32_MAX;
        }
        if (position < -1)
        {
          continue;
        }
        break;
      }


      while (1)
      {
        CLEAR;
        PrintMenuVendedores();
        printf("  ||                               ||\n");
        PrintItemAsTableVen(aux->vendor, "Vendedor a Modificar");
        printf("\n");
        printf("  [~] No modificar\n");
        if (ven.name[0] == '\0')
        {
          printf("  Ingrese el Nombre del vendedor: ");
          if (OmmitableInputString(ven.name, "%19s"))
          {
            strcpy(ven.name, aux->vendor.name);
          }
          if (ven.name[0] != '\0')
          {
            strcpy(aux->vendor.name, ven.name);
          }
          continue;
        }
        if (ven.ci[0] == '\0')
        {
          printf("  Ingrese la Cedula de Identidad del vendedor: ");
          if (OmmitableInputString(ven.ci, "%10s"))
          {
            strcpy(ven.ci, aux->vendor.ci);
          }
          if (ven.ci[0] != '\0')
          {
            strcpy(aux->vendor.ci, ven.ci);
          }
          continue;
        }
        if (ven.date.year <= 0)
        {
          printf("  Ingrese Anio de ingreso del vendedor: ");
          if (OmmitableInputNumber(&ven.date.year, "%5s"))
          {
            ven.date.year = aux->vendor.date.year;
          }
          if (IsInRange(ven.date.year, 0, 2100))
          {
            aux->vendor.date.year = ven.date.year;
          }
          else
          {
            ven.date.year = 0;
          }
          continue;
        }
        if (ven.date.month <= 0)
        {
          printf("  Ingrese el Mes de ingreso del vendedor: ");
          if (OmmitableInputNumber(&ven.date.month, "%3s"))
          {
            ven.date.month = aux->vendor.date.month;
          }
          if (IsInRange(ven.date.month, 1, 12))
          {
            aux->vendor.date.month = ven.date.month;
          }
          else
          {
            ven.date.month = 0;
          }
          continue;
        }
        if (ven.date.day <= 0)
        {
          printf("  Ingrese el Dia de ingreso del vendedor: ");
          if (OmmitableInputNumber(&ven.date.day, "%3s"))
          {
            ven.date.day = aux->vendor.date.day;
          }
          if (IsInRange(ven.date.day, 1, 31))
          {
            aux->vendor.date.day = ven.date.day;
          }
          else
          {
            ven.date.day = 0;
          }
          continue;
        }
        if (ven.commission <= 0)
        {
          printf("  Ingrese la Comision del vendedor: ");
          if (OmmitableInputNumber(&ven.commission, "%4s"))
          {
            ven.commission = aux->vendor.commission;
          }
          if (IsInRange(ven.commission, 0, 100))
          {
            aux->vendor.commission = ven.commission;
          }
          else
          {
            ven.commission = 0;
          }
          continue;
        }
        break;
      }
      SaveFileVen(&VendorList, "Vendedores.txt");
      CLEAR;
      PrintMenuVendedores();
      printf("  ||                               ||\n");
      PrintItemAsTableVen(ven, "Vendedor Modificado");
      printf("\n");
      ENTER_CONTINUAR;
      break;
    case '4':
      if (VendorList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede visualizar");
        ENTER_CONTINUAR;
        break;
      }
      PrintItemListVen(VendorList);
      break;
    case '5':
      if (VendorList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede realizar busquedas");
        ENTER_CONTINUAR;
        break;
      }

      CLEAR;
      PrintMenuVendedores();
      printf("\n");

      printf("  Seleccione el campo por el que va a buscar\n");
      printf("  [0] Nombre\n");
      printf("  [1] Cedula\n");
      printf("  [2] Fecha de Ingreso\n");
      printf("  [3] Comision\n");
      InputString(sel, "%2s");

      ven.name[0] = '\0';
      ven.ci[0] = '\0';
      ven.date.day = 0;
      ven.date.month = 0;
      ven.date.year = 0;
      ven.commission = 0;

      printf("  Ingrese");
      switch (sel[0])
      {
      case '0':
        printf(" el Nombre a buscar: ");
        InputString(ven.name, "%19s");
        break;
      case '1':
        printf(" la Cedula de Identidad a buscar: ");
        InputString(ven.ci, "%10s");
        break;
      case '2':
        printf(" el Anio a buscar: ");
        InputNumber(&ven.date.year, "%3s");
        printf("  Ingrese el Mes a buscar: ");
        InputNumber(&ven.date.month, "%3s");
        printf("  Ingrese el Dia a buscar: ");
        InputNumber(&ven.date.day, "%5s");
        break;
      case '3':
        printf(" la Comision a buscar: ");
        InputNumber(&ven.commission, "%4s");
        break;
      default:
        CLEAR;
        PrintMenuVendedores();
        printf("\n  El campo ingresado no existe, vuelvalo a intentar\n");
        ENTER_CONTINUAR;
        return;
        break;
      };
      aux = NULL;
      aux = LookForVendor(VendorList, ven, sel[0] - '0');

      if (aux == NULL)
      {
        printf("  No se encontro ningun elemento con esa informacion\n");
        ENTER_CONTINUAR;
        break;
      }
      printf("  Vendedore(s) entontrado(s)\n");
      ENTER_CONTINUAR;
      PrintItemListVen(aux);
      break;
    case '0':
      return;
      break;
    default:
      TECLA_VALIDA;
      break;
    }
  }
};

void MenuManejoClientes()
{
  char sel[2];
  char buffer[64];
  int position;
  struct Client cli;
  struct ClientNode *aux = GetNodeCli(ClientList, position);
  while (1)
  {
    PrintMenuClientes();
    printf("\n");
    printf("  Seleccion: ");
    scanf("%1s", sel);
    switch (sel[0])
    {
    //
    // CASO AGREGAR CLIENTE
    //
    case '1':
      cli.name[0] = '\0';
      cli.ci[0] = '\0';
      cli.dir[0] = '\0';
      cli.cellphone[0] = '\0';

      while (1)
      {
        CLEAR;
        PrintMenuClientes();
        printf("  ||                               ||\n");
        PrintItemAsTableCli(cli, "Cliente Actual");
        printf("\n");
        if (cli.name[0] == '\0')
        {
          printf("  Ingrese el Nombre del cliente: ");
          InputString(cli.name, "%19s");
          continue;
        }
        if (cli.ci[0] == '\0')
        {
          printf("  Ingrese la Cedula de Identidad del cliente: ");
          InputString(cli.ci, "%10s");
          continue;
        }
        printf("\n");
        if (cli.dir[0] == '\0')
        {
          printf("  Ingrese la Direction del cliente: ");
          InputString(cli.dir, "%19s");
          continue;
        }
        printf("\n");
        if (cli.cellphone[0] == '\0')
        {
          printf("  Ingrese el Telefono del cliente: ");
          InputString(cli.cellphone, "%19s");
          continue;
        }
        printf("\n");
        break;
      }

      while (1)
      {
        position = -2;
        CLEAR;
        PrintMenuClientes();
        printf("  ||                               ||\n");
        PrintItemAsTableCli(cli, "Cliente a Agregar");
        printf("\n");
        printf("  Ingrese la posicion donde agregar el cliente: \n");
        printf("  [0, a-z, A-Z] Agregar al inicio de la lista\n");
        printf("  [-1] Agregar al final de la lista\n");
        printf("  Posicion: ");
        InputNumber(&position, "%19s");
        if (position == -1)
        {
          position = INT32_MAX;
        }
        if (position < -1)
        {
          continue;
        }
        break;
      }
      InsertItemCli(&ClientList, cli, position);
      SaveFileCli(&ClientList, "Clientes.txt");
      CLEAR;
      PrintMenuClientes();
      printf("  ||                               ||\n");
      PrintItemAsTableCli(cli, "Cliente Agregado");
      printf("\n");
      printf("  Cliente agregado a la lista!\n");
      ENTER_CONTINUAR;
      break;
    //
    // CASO ELIMINAR ARTICULO
    //
    case '2':
      if (ClientList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede eliminar nada");
        ENTER_CONTINUAR;
        break;
      }

      while (1)
      {
        position = -2;
        CLEAR;
        PrintMenuClientes();
        printf("\n");
        printf("  Ingrese la posicion del cliente a eliminar: \n");
        printf("  [0, a-z, A-Z] Eliminar el primer cliente de la lista\n");
        printf("  [-1] Eliminar el ultimo cliente de la lista\n");
        printf("  Posicion: ");
        InputNumber(&position, "%10s");
        if (position == -1)
        {
          position = INT32_MAX;
        }
        if (position < -1)
        {
          continue;
        }
        break;
      }

      cli = GetNodeCli(ClientList, position)->client;
      if (cli.name[0])
      {
        CLEAR;
        PrintMenuClientes();
        printf("  ||                               ||\n");
        PrintItemAsTableCli(cli, "Cliente a Eliminar");
        printf("\n");
        printf("  Eliminar a %s de la lista?\n", cli.name);
        printf("  [S] Eliminar\n");
        printf("  [N] No Eliminar\n");
        CLR_BUF;
        scanf("%1s", buffer);
      }
      if (!(buffer[0] == 's' || buffer[0] == 'S'))
      {
        printf("  No se ha eliminado ningun elemento\n");
      }
      else if (RemoveItemCli(&ClientList, position))
      {
        printf("  La lista es NULL, no se ha podido eliminar ningun elemento\n");
      }
      else
      {
        printf("  Se ha eliminado %s de la lista\n", cli.name);
      }
      SaveFileCli(&ClientList, "Clientes.txt");
      ENTER_CONTINUAR;
      break;
    //
    // CASO MODIFICAR ARTICULO
    //
    case '3':
      if (ClientList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede modificar nada");
        ENTER_CONTINUAR;
        break;
      }

      cli.name[0] = '\0';
      cli.ci[0] = '\0';
      cli.dir[0] = '\0';
      cli.cellphone[0] = '\0';

      while (ClientList != NULL)
      {
        position = -2;
        CLEAR;
        PrintMenuClientes();
        printf("\n");
        printf("  Ingrese la posicion del cliente a modificar: \n");
        printf("  [0, a-z, A-Z] Modificar el primer cliente de la lista\n");
        printf("  [-1] Modificar el ultimo cliente de la lista\n");
        printf("  Posicion: ");
        InputNumber(&position, "%10s");
        if (position == -1)
        {
          position = INT32_MAX;
        }
        if (position < -1)
        {
          continue;
        }
        break;
      }


      while (1)
      {
        CLEAR;
        PrintMenuClientes();
        printf("  ||                               ||\n");
        PrintItemAsTableCli(aux->client, "Cliente a Modificar");
        printf("\n");
        printf("  [~] No modificar\n");
        if (cli.name[0] == '\0')
        {
          printf("  Ingrese el Nombre del cliente: ");
          if (OmmitableInputString(cli.name, "%19s"))
          {
            strcpy(cli.name, aux->client.name);
          }
          if (cli.name[0] != '\0')
          {
            strcpy(aux->client.name, cli.name);
          }
          continue;
        }
        if (cli.ci[0] == '\0')
        {
          printf("  Ingrese la Cedula de Identidad del cliente: ");
          if (OmmitableInputString(cli.ci, "%10s"))
          {
            strcpy(cli.ci, aux->client.ci);
          }
          if (cli.ci[0] != '\0')
          {
            strcpy(aux->client.ci, cli.ci);
          }
          continue;
        }
        if (cli.dir[0] == '\0')
        {
          printf("  Ingrese la Direccion del cliente: ");
          if (OmmitableInputString(cli.dir, "%19s"))
          {
            strcpy(cli.dir, aux->client.dir);
          }
          if (cli.dir[0] != '\0')
          {
            strcpy(aux->client.dir, cli.dir);
          }
          continue;
        }
        if (cli.cellphone[0] == '\0')
        {
          printf("  Ingrese el Telefono del cliente: ");
          if (OmmitableInputString(cli.cellphone, "%19s"))
          {
            strcpy(cli.cellphone, aux->client.cellphone);
          }
          if (cli.cellphone[0] != '\0')
          {
            strcpy(aux->client.cellphone, cli.cellphone);
          }
          continue;
        }
        break;
      }
      SaveFileCli(&ClientList, "Clientes.txt");
      CLEAR;
      PrintMenuClientes();
      printf("  ||                               ||\n");
      PrintItemAsTableCli(cli, "Cliente Modificado");
      printf("\n");
      ENTER_CONTINUAR;
      break;
    case '4':
      if (ClientList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede visualizar");
        ENTER_CONTINUAR;
        break;
      }
      PrintItemListCli(ClientList);
      break;
    case '5':
      if (ClientList == NULL)
      {
        printf("\n");
        printf("  La lista es NULL, no se puede realizar busquedas");
        ENTER_CONTINUAR;
        break;
      }

      CLEAR;
      PrintMenuClientes();
      printf("\n");

      printf("  Seleccione el campo por el que va a buscar\n");
      printf("  [0] Nombre\n");
      printf("  [1] Cedula\n");
      printf("  [2] Direccion\n");
      printf("  [3] Telefono");
      InputString(sel, "%2s");

      cli.name[0] = '\0';
      cli.ci[0] = '\0';
      cli.dir[0] = '\0';
      cli.cellphone[0] = '\0';

      printf("  Ingrese");
      switch (sel[0])
      {
      case '0':
        printf(" el Nombre a buscar: ");
        InputString(cli.name, "%19s");
        break;
      case '1':
        printf(" la Cedula de Identidad a buscar: ");
        InputString(cli.ci, "%10s");
        break;
      case '2':
        printf(" la Direccion a buscar: ");
        InputString(cli.dir, "%19s");
        break;
      case '3':
        printf(" el Numero de Telefono a buscar: ");
        InputString(cli.cellphone, "%19s");
        break;
      default:
        CLEAR;
        PrintMenuClientes();
        printf("\n  El campo ingresado no existe, vuelvalo a intentar\n");
        ENTER_CONTINUAR;
        return;
        break;
      };
      aux = NULL;
      aux = LookForClient(ClientList, cli, sel[0] - '0');

      if (aux == NULL)
      {
        printf("  No se encontro ningun elemento con esa informacion\n");
        ENTER_CONTINUAR;
        break;
      }
      printf("  Cliente(s) entontrado(s)\n");
      ENTER_CONTINUAR;
      PrintItemListCli(aux);
      break;
    case '0':
      return;
      break;
    default:
      TECLA_VALIDA;
      break;
    }
  }
};

void MainMenu()
{
  char sel[2];
  while (1)
  {
    CLEAR;
    printf("\n");
    printf("  ||===============================||\n");
    printf("  || Menu Principal                ||\n");
    printf("  ||===============================||\n");
    printf("  || [1] Manejo Articulos          ||\n");
    printf("  || [2] Manejo Vendedores         ||\n");
    printf("  || [3] Manejo Clientes           ||\n");
    printf("  ||                               ||\n");
    printf("  || [0] Salir Del Programa        ||\n");
    printf("  ||===============================||\n\n");
    printf("  Seleccion: ");
    scanf("%1s", sel);
    switch (sel[0])
    {
    case '1':
      MenuManejoArticulos();
      break;
    case '2':
      MenuManejoVendedores();
      break;
    case '3':
      MenuManejoClientes();
      break;
    case '0':
      return;
      break;
    default:
      TECLA_VALIDA;
    };
  }
};

int main(void)
{
  ReadFileArt(&ArticlesList, "Articulos.txt");
  ReadFileVen(&VendorList, "Vendedores.txt");
  ReadFileCli(&ClientList, "Clientes.txt");

  MainMenu();
  return 0;
};
