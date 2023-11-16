#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ART (struct ArticleNode*)malloc(sizeof(struct ArticleNode))
#define MALLOC_VEN (struct VendorNode*)malloc(sizeof(struct VendorNode))
#define MALLOC_CLI (struct ClientNode*)malloc(sizeof(struct ClientNode))
#define CLEAR system("clear")
#define COL_SIZE 20

struct Article {
  char code[COL_SIZE];
  char name[COL_SIZE];
  float price;
  int ammount;
};

struct Date {
  int day;
  int month;
  int year;
};

struct Vendor {
  char name[COL_SIZE];
  char ci[COL_SIZE];
  struct Date date;
  int commission;
};

struct Client {
  char name[COL_SIZE];
  char ci[COL_SIZE];
  char dir[COL_SIZE];
  char cellphone[COL_SIZE];
};

struct ArticleNode {
  int key;
  struct Article article;
  struct ArticleNode* next;
};

struct VendorNode {
  struct Vendor vendor;
  struct VendorNode* next;
};

struct ClientNode {
  struct Client client;
  struct ClientNode* next;
};

int GetLastKey(struct ArticleNode* ArticlesList) {
  if (ArticlesList == NULL) { return 0; }
  int max = 0;
  do {
    if (ArticlesList->key > max) { max = ArticlesList->key; }
    ArticlesList = ArticlesList->next;
  } while(ArticlesList != NULL);
  return ++max;
};

struct ArticleNode* PreviousItemArt(struct ArticleNode* List, struct ArticleNode* article) {
  if (List == NULL) { return NULL; }
  if (List == article) { return NULL; }
  while (List->next != NULL) {
    if (List->next == article) { return List; }
    List = List->next;
  } return NULL;
};

struct VendorNode* PreviousItemVen(struct VendorNode* List, struct VendorNode* vendor) {
  if (List == NULL) { return NULL; }
  if (List == vendor) { return NULL; }
  while (List->next != NULL) {
    if (List->next == vendor) { return List; }
    List = List->next;
  } return NULL;
};

struct ClientNode* PreviousItemCli(struct ClientNode* List, struct ClientNode* client) {
  if (List == NULL) { return NULL; }
  if (List == client) { return NULL; }
  while (List->next != NULL) {
    if (List->next == client) { return List; }
    List = List->next;
  } return NULL;
};

struct Article CreateItemArt(char code[], char name[], float price, int ammount) {
  struct Article return_value;
  for (int i = 0; i < COL_SIZE - 1; i++) {
    return_value.code[i] = code[i];
    return_value.name[i] = name[i];
  }
  return_value.price = price;
  return_value.ammount = ammount;
  return return_value;
};

struct Vendor CreateItemVen(char name[], char ci[], struct Date date, int commission) {
  struct Vendor return_value;
  for (int i = 0; i < COL_SIZE - 1; i++) {
    return_value.name[i] = name[i];
    return_value.ci[i] = ci[i];
  }
  return_value.date = date;
  return_value.commission = commission;
  return return_value;
};

struct Client CreateItemCli(char name[], char ci[], char dir[], char cellphone[]) {
  struct Client return_value;
  for (int i = 0; i < COL_SIZE - 1; i++) {
    return_value.name[i] = name[i];
    return_value.ci[i] = ci[i];
    return_value.dir[i] = dir[i];
    return_value.cellphone[i] = cellphone[i];
  }
  return return_value;
};

void PrintItemAsTableArt(struct Article article, char text[]) {
  printf("  ||===============================||\n");
  printf("  ||%31s||\n", &text[0]);
  printf("  ||===============================||\n");
  printf("  | Codigo   | %20s |\n", &article.code[0]);
  printf("  | Nombre   | %20s |\n", &article.name[0]);
  printf("  | Precio   | %20.2f |\n", article.price);
  printf("  | Cantidad | %20d |\n", article.ammount);
  printf("  ||===============================||\n");
};

void PrintItemAsTableVen(struct Vendor vendor, char text[]) {
  printf("  ||===============================||\n");
  printf("  ||%31s||\n", &text[0]);
  printf("  ||===============================||\n");
  printf("  | Nombre   | %20s |\n", &vendor.name[0]);
  printf("  | C.I      | %20s |\n", &vendor.ci[0]);
  printf("  | Date     | %12d/%2d/%4d |\n", vendor.date.day, vendor.date.month, vendor.date.year);
  printf("  | Comision | %20d |\n", vendor.commission);
  printf("  ||===============================||\n");
};

void PrintItemAsTableCli(struct Client client, char text[]) {
  printf("  ||===============================||\n");
  printf("  ||%31s||\n", &text[0]);
  printf("  ||===============================||\n");
  printf("  | Nombre   | %20s |\n", &client.name[0]);
  printf("  | C.I      | %20s |\n", &client.ci[0]);
  printf("  | Date     | %20s |\n", &client.dir[0]);
  printf("  | Comision | %20s |\n", &client.cellphone[0]);
  printf("  ||===============================||\n");
};

void PrintItemListArt(struct ArticleNode* List) {
  CLEAR;
  if (List == NULL) {
    printf("Esta lista no contiene ningun articulo\n");
    printf("Presione ENTER para continuar"); getchar();
    return;
  }

  int item = 1;
  char tmp[20];
  struct ArticleNode* articulo_inicial = List;
  struct ArticleNode* aux = List;

  while (List != NULL) {
    CLEAR;
    sprintf(tmp, "Item: %d | LLave: %d", item, List->key);
    PrintItemAsTableArt(List->article, tmp);
    printf("\n");

    if (PreviousItemArt(articulo_inicial, List) != NULL) { printf("[P] Articulo Previo\n"); }
    if (List->next != NULL) { printf("[S] Articulo Siguiente\n"); }
    printf("[T] Terminar Visualizacion\n");
    switch(getchar()) {
      case 'T':
      case 't':
        return;
        break;
      case 'S':
      case 's':
        if (List->next == NULL) { break; }
        item++;
        List = List->next;
        break;
      case 'P':
      case 'p':
        aux = PreviousItemArt(articulo_inicial, List);
        if (aux != NULL) { List = aux; item--; }
        break;
    }
  }
};

void PrintItemListVen(struct VendorNode* List) {
  CLEAR;
  if (List == NULL) {
    printf("Esta lista no contiene ningun articulo\n");
    printf("Presione ENTER para continuar"); getchar();
    return;
  }

  int item = 1;
  char tmp[20];
  struct VendorNode* initial_vendor = List;
  struct VendorNode* aux = List;

  while (List != NULL) {
    CLEAR;
    sprintf(tmp, "Item: %d", item);
    PrintItemAsTableVen(List->vendor, tmp);
    printf("\n");

    if (PreviousItemVen(initial_vendor, List) != NULL) { printf("[P] Vendedor Previo\n"); }
    if (List->next != NULL) { printf("[S] Vendedor Siguiente\n"); }
    printf("[T] Terminar Visualizacion\n");
    switch(getchar()) {
      case 'T':
      case 't':
        return;
        break;
      case 'S':
      case 's':
        if (List->next == NULL) { break; }
        item++;
        List = List->next;
        break;
      case 'P':
      case 'p':
        aux = PreviousItemVen(initial_vendor, List);
        if (aux != NULL) { List = aux; item--; }
        break;
    }
  }
};

void PrintItemListCli(struct ClientNode* List) {
  CLEAR;
  if (List == NULL) {
    printf("Esta lista no contiene ningun articulo\n");
    printf("Presione ENTER para continuar"); getchar();
    return;
  }

  int item = 1;
  char tmp[20];
  struct ClientNode* initial_client = List;
  struct ClientNode* aux = List;

  while (List != NULL) {
    CLEAR;
    sprintf(tmp, "Item: %d", item);
    PrintItemAsTableCli(List->client, tmp);
    printf("\n");

    if (PreviousItemCli(initial_client, List) != NULL) { printf("[P] Cliente Previo\n"); }
    if (List->next != NULL) { printf("[S] Cliente Siguiente\n"); }
    printf("[T] Terminar Visualizacion\n");
    switch(getchar()) {
      case 'T':
      case 't':
        return;
        break;
      case 'S':
      case 's':
        if (List->next == NULL) { break; }
        item++;
        List = List->next;
        break;
      case 'P':
      case 'p':
        aux = PreviousItemCli(initial_client, List);
        if (aux != NULL) { List = aux; item--; }
        break;
    }
  }
};

void CreateListArt(struct ArticleNode** List, struct Article article_to_add) {
  CLEAR;
  if (*List == NULL) {
    PrintItemAsTableArt(article_to_add, "Creando lista con articulo: ");
    *List = MALLOC_ART;
    (*List)->article = article_to_add;
    (*List)->key = 0;
    return;
  }
  printf("La lista ya existe, conteniendo los siguientes articulos: \n");
  PrintItemListArt(*List);
};

void CreateListVen(struct VendorNode** List, struct Vendor vendor_to_add) {
  CLEAR;
  if (*List == NULL) {
    PrintItemAsTableVen(vendor_to_add, "Creando lista con articulo: ");
    *List = MALLOC_VEN;
    (*List)->vendor = vendor_to_add;
    return;
  }
  printf("La lista ya existe, conteniendo los siguientes articulos: \n");
  PrintItemListVen(*List);
};

void CreateListCli(struct ClientNode** List, struct Client client_to_add) {
  CLEAR;
  if (*List == NULL) {
    PrintItemAsTableCli(client_to_add, "Creando lista con articulo: ");
    *List = MALLOC_CLI;
    (*List)->client = client_to_add;
    return;
  }
  printf("La lista ya existe, conteniendo los siguientes articulos: \n");
  PrintItemListCli(*List);
};

void InsertItemArt(struct ArticleNode** List, struct Article article_to_add, int position) {
  if (*List == NULL) { CreateListArt(List, article_to_add); return; }
  struct ArticleNode* aux = MALLOC_ART;
  struct ArticleNode* aux_2 = MALLOC_ART;
  if (position <= 0) {
    aux->article = article_to_add;
    aux->key = GetLastKey(*List);
    aux->next = *List;
    *List = aux;
    return;
  }
  aux = *List;
  int key = GetLastKey(*List);
  while (aux->next != NULL && position-- > 1) { aux = aux->next; }
  aux_2 = aux->next;
  aux->next = MALLOC_ART;
  aux->next->article = article_to_add;
  aux->next->key = key;
  aux->next->next = aux_2;
  getchar();
};

void InsertItemVen(struct VendorNode** List, struct Vendor vendor_to_add, int position) {
  if (*List == NULL) { CreateListVen(List, vendor_to_add); return; }
  struct VendorNode* aux = MALLOC_VEN;
  struct VendorNode* aux_2 = MALLOC_VEN;
  if (position <= 0) {
    aux->vendor = vendor_to_add;
    aux->next = *List;
    *List = aux;
    return;
  }
  aux = *List;
  while (aux->next != NULL && position-- > 1) { aux = aux->next; }
  aux_2 = aux->next;
  aux->next = MALLOC_VEN;
  aux->next->vendor = vendor_to_add;
  aux->next->next = aux_2;
  getchar();
};

void InsertItemCli(struct ClientNode** List, struct Client client_to_add, int position) {
  if (*List == NULL) { CreateListCli(List, client_to_add); return; }
  struct ClientNode* aux = MALLOC_CLI;
  struct ClientNode* aux_2 = MALLOC_CLI;
  if (position <= 0) {
    aux->client = client_to_add;
    aux->next = *List;
    *List = aux;
    return;
  }
  aux = *List;
  while (aux->next != NULL && position-- > 1) { aux = aux->next; }
  aux_2 = aux->next;
  aux->next = MALLOC_CLI;
  aux->next->client = client_to_add;
  aux->next->next = aux_2;
  getchar();
};

void RemoveItemArt(struct ArticleNode** List, int position) {
  if (*List == NULL) { return; }
  if ((*List)->next == NULL) { free(*List); *List = NULL; return; }
  struct ArticleNode* aux = MALLOC_ART;
  struct ArticleNode* aux_2 = MALLOC_ART;
  if (position <= 0) {
    aux = (*List)->next;
    free(*List);
    *List = aux;
    return;
  }
  aux = *List;
  while(aux->next != NULL && position-- > 0) { aux = aux->next; }
  aux_2 = aux->next;
  aux = PreviousItemArt(*List, aux);
  free(aux->next);
  aux->next = aux_2;
};

void RemoveItemVen(struct VendorNode** List, int position) {
  if (*List == NULL) { return; }
  if ((*List)->next == NULL) { free(*List); *List = NULL; return; }
  struct VendorNode* aux = MALLOC_VEN;
  struct VendorNode* aux_2 = MALLOC_VEN;
  if (position <= 0) {
    aux = (*List)->next;
    free(*List);
    *List = aux;
    return;
  }
  aux = *List;
  while(aux->next != NULL && position-- > 0) { aux = aux->next; }
  aux_2 = aux->next;
  aux = PreviousItemVen(*List, aux);
  free(aux->next);
  aux->next = aux_2;
};

void RemoveItemCli(struct ClientNode** List, int position) {
  if (*List == NULL) { return; }
  if ((*List)->next == NULL) { free(*List); *List = NULL; return; }
  struct ClientNode* aux = MALLOC_CLI;
  struct ClientNode* aux_2 = MALLOC_CLI;
  if (position <= 0) {
    aux = (*List)->next;
    free(*List);
    *List = aux;
    return;
  }
  aux = *List;
  while(aux->next != NULL && position-- > 0) { aux = aux->next; }
  aux_2 = aux->next;
  aux = PreviousItemCli(*List, aux);
  free(aux->next);
  aux->next = aux_2;
};

void ReadFileArt(struct ArticleNode** List, char dir[]) {
  FILE *f;
  f = fopen(dir, "r");
  if (f == NULL) { return; }
  printf("Leyendo el archivo %s\n\n", &dir[0]);

  // Vaciamos la lista
  if (*List != NULL) {
    printf("La lista actual no se encuentra vacia, vaciandola...\n");
    while((*List)->next == NULL) {
      RemoveItemArt(List, 0);
    }
  }

  int input_code, key = 0;
  struct ArticleNode* aux = MALLOC_ART;
  struct ArticleNode* ret = aux;
  struct Article article;

  input_code = fscanf(f, "%*[^\n]\n");
  if (input_code == EOF) {
    printf("El archivo no contiene informacion, cerrando %s\n", &dir[0]);
    fclose(f);
    getchar();
    return;
  }
  while (1) {
    input_code = fscanf(f, "%s", article.code);
    input_code = fscanf(f, "%s", article.name);
    input_code = fscanf(f, "%f", &article.price);
    input_code = fscanf(f, "%d", &article.ammount);
    if (input_code != EOF) {
      PrintItemAsTableArt(article, "Articulo leido");
      printf("\n");
      getchar();
      aux->article = article;
      aux->key = key++;
      aux->next = MALLOC_ART;
      aux = aux->next;
      continue;
    }
    struct ArticleNode* prev = PreviousItemArt(ret, aux);
    free(prev->next); prev->next = NULL;
    *List = ret; fclose(f);
    break;
  }
};

void ReadFileVen(struct VendorNode** List, char dir[]) {
  FILE *f;
  f = fopen(dir, "r");
  if (f == NULL) { return; }
  printf("Leyendo el archivo %s\n\n", &dir[0]);

  // Vaciamos la lista
  if (*List != NULL) {
    printf("La lista actual no se encuentra vacia, vaciandola...\n");
    while((*List)->next == NULL) {
      RemoveItemVen(List, 0);
    }
  }

  int input_code, key = 0;
  struct VendorNode* aux = MALLOC_VEN;
  struct VendorNode* ret = aux;
  struct Vendor vendor;

  input_code = fscanf(f, "");
  if (input_code == EOF) {
    printf("El archivo no contiene informacion, cerrando %s\n", &dir[0]);
    fclose(f);
    getchar();
    return;
  }
  while (1) {
    input_code = fscanf(f, "%s", vendor.name);
    input_code = fscanf(f, "%s", vendor.ci);
    input_code = fscanf(f, "%d/%d/%d", &vendor.date.day, &vendor.date.month, &vendor.date.year);
    input_code = fscanf(f, "%d", &vendor.commission);
    if (input_code != EOF) {
      PrintItemAsTableVen(vendor, "Vendedor leido");
      printf("\n");
      getchar();
      aux->vendor = vendor;
      aux->next = MALLOC_VEN;
      aux = aux->next;
      continue;
    }
    struct VendorNode* prev = PreviousItemVen(ret, aux);
    free(prev->next); prev->next = NULL;
    *List = ret; fclose(f);
    break;
  }
};

void ReadFileCli(struct ClientNode** List, char dir[]) {
  FILE *f;
  f = fopen(dir, "r");
  if (f == NULL) { return; }
  printf("Leyendo el archivo %s\n\n", &dir[0]);

  // Vaciamos la lista
  if (*List != NULL) {
    printf("La lista actual no se encuentra vacia, vaciandola...\n");
    while((*List)->next == NULL) {
      RemoveItemCli(List, 0);
    }
  }

  int input_code, key = 0;
  struct ClientNode* aux = MALLOC_CLI;
  struct ClientNode* ret = aux;
  struct Client client;

  input_code = fscanf(f, "");
  if (input_code == EOF) {
    printf("El archivo no contiene informacion, cerrando %s\n", &dir[0]);
    fclose(f);
    getchar();
    return;
  }
  while (1) {
    input_code = fscanf(f, "%s", client.name);
    input_code = fscanf(f, "%s", client.ci);
    input_code = fscanf(f, "%s", client.dir);
    input_code = fscanf(f, "%s", client.cellphone);
    if (input_code != EOF) {
      PrintItemAsTableCli(client, "Vendedor leido");
      printf("\n");
      getchar();
      aux->client = client;
      aux->next = MALLOC_CLI;
      aux = aux->next;
      continue;
    }
    struct ClientNode* prev = PreviousItemCli(ret, aux);
    free(prev->next); prev->next = NULL;
    *List = ret; fclose(f);
    break;
  }
};

void SaveFileArt(struct ArticleNode** List, char dir[]) {
  FILE *f;
  f = fopen(dir, "w");
  if (f == NULL) { return; }
  printf("Escribiendo en el archivo %s\n\n", &dir[0]);

  struct ArticleNode* aux = *List;

  fprintf(f, "ARTICULOS\n");
  while (aux != NULL) {
    fprintf(f, "%s\n", aux->article.code);
    fprintf(f, "%s\n", aux->article.name);
    fprintf(f, "%2f\n", aux->article.price);
    fprintf(f, "%d\n", aux->article.ammount);
    aux = aux->next;
  }
  fclose(f);
};

void SaveFileVen(struct VendorNode** List, char dir[]) {
  FILE *f;
  f = fopen(dir, "w");
  if (f == NULL) { return; }
  printf("Escribiendo en el archivo %s\n\n", &dir[0]);

  struct VendorNode* aux = *List;

  while (aux != NULL) {
    fprintf(f, "%s ", aux->vendor.name);
    fprintf(f, "%s ", aux->vendor.ci);
    fprintf(f, "%d/%d/%d ", aux->vendor.date.day, aux->vendor.date.month, aux->vendor.date.year);
    fprintf(f, "%d\n", aux->vendor.commission);
    aux = aux->next;
  }
  fclose(f);
};

void SaveFileCli(struct ClientNode** List, char dir[]) {
  FILE *f;
  f = fopen(dir, "w");
  if (f == NULL) { return; }
  printf("Escribiendo en el archivo %s\n\n", &dir[0]);

  struct ClientNode* aux = *List;

  while (aux != NULL) {
    fprintf(f, "%s ", aux->client.name);
    fprintf(f, "%s ", aux->client.ci);
    fprintf(f, "%s ", aux->client.dir);
    fprintf(f, "%s\n", aux->client.cellphone);
    aux = aux->next;
  }
  fclose(f);
};

struct ArticleNode* ArticlesList = NULL;
struct VendorNode* VendorList = NULL;
struct ClientNode* ClientList = NULL;

int main(void) {
  return 0;
}
