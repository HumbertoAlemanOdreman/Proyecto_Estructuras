#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC_ART (struct ArticleNode*)malloc(sizeof(struct ArticleNode))
#define MALLOC_VEN (struct VendorNode*)malloc(sizeof(struct VendorNode))
#define MALLOC_CLI (struct ClientNode*)malloc(sizeof(struct ClientNode))


#define CLR_BUF while(getchar() != '\n') {}
#define ENTER_CONTINUAR printf("  Presione ENTER para continuar\n"); CLR_BUF; getchar();
#define TECLA_VALIDA printf("  ERROR: debe seleccionar una opcion valida\n"); ENTER_CONTINUAR;

#define CLEAR system("clear")
#define COL_SIZE 20

struct ArticleNode* ArticlesList = NULL;
struct VendorNode* VendorList = NULL;
struct ClientNode* ClientList = NULL;

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

char InputChar() {
  char sel; scanf(" %c%*[^\n]", &sel);
  return sel;
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
  printf("  | Codigo   | %20s |\n", article.code);
  printf("  | Nombre   | %20s |\n", article.name);
  printf("  | Precio   | %20.2f |\n", article.price);
  printf("  | Cantidad | %20d |\n", article.ammount);
  printf("  ||===============================||\n");
};

void PrintItemAsTableVen(struct Vendor vendor, char text[]) {
  printf("  ||===============================||\n");
  printf("  ||%31s||\n", &text[0]);
  printf("  ||===============================||\n");
  printf("  | Nombre   | %20s |\n", vendor.name);
  printf("  | C.I      | %20s |\n", vendor.ci);
  printf("  | Date     | %12d/%2d/%4d |\n", vendor.date.day, vendor.date.month, vendor.date.year);
  printf("  | Comision | %20d |\n", vendor.commission);
  printf("  ||===============================||\n");
};

void PrintItemAsTableCli(struct Client client, char text[]) {
  printf("  ||===============================||\n");
  printf("  ||%31s||\n", &text[0]);
  printf("  ||===============================||\n");
  printf("  | Nombre   | %20s |\n", client.name);
  printf("  | C.I      | %20s |\n", client.ci);
  printf("  | Date     | %20s |\n", client.dir);
  printf("  | Comision | %20s |\n", client.cellphone);
  printf("  ||===============================||\n");
};

void PrintItemListArt(struct ArticleNode* List) {
  CLEAR;

  int item = 1;
  char tmp[20];
  struct ArticleNode* articulo_inicial = List;
  struct ArticleNode* aux = List;

  while (List != NULL) {
    CLEAR;
    sprintf(tmp, "Item: %d | LLave: %d", item, List->key);
    PrintItemAsTableArt(List->article, tmp);
    printf("\n");

    if (PreviousItemArt(articulo_inicial, List) != NULL) { printf("  [P] Articulo Previo\n"); }
    if (List->next != NULL) { printf("  [S] Articulo Siguiente\n"); }
    printf("  [T] Terminar Visualizacion\n");
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

  int item = 1;
  char tmp[20];
  struct VendorNode* initial_vendor = List;
  struct VendorNode* aux = List;

  while (List != NULL) {
    CLEAR;
    sprintf(tmp, "Item: %d", item);
    PrintItemAsTableVen(List->vendor, tmp);
    printf("\n");

    if (PreviousItemVen(initial_vendor, List) != NULL) { printf("  [P] Vendedor Previo\n"); }
    if (List->next != NULL) { printf("  [S] Vendedor Siguiente\n"); }
    printf("  [T] Terminar Visualizacion\n");
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

  int item = 1;
  char tmp[20];
  struct ClientNode* initial_client = List;
  struct ClientNode* aux = List;

  while (List != NULL) {
    CLEAR;
    sprintf(tmp, "Item: %d", item);
    PrintItemAsTableCli(List->client, tmp);
    printf("\n");

    if (PreviousItemCli(initial_client, List) != NULL) { printf("  [P] Cliente Previo\n"); }
    if (List->next != NULL) { printf("  [S] Cliente Siguiente\n"); }
    printf("  [T] Terminar Visualizacion\n");
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

int RemoveItemArt(struct ArticleNode** List, int position) {
  if (*List == NULL) { return 1; }
  if ((*List)->next == NULL) { free(*List); *List = NULL; return 0; }
  struct ArticleNode* aux = MALLOC_ART;
  struct ArticleNode* aux_2 = MALLOC_ART;
  if (position <= 0) {
    aux = (*List)->next;
    free(*List);
    *List = aux;
    return 0;
  }
  aux = *List;
  while(aux->next != NULL && position-- > 0) { aux = aux->next; }
  aux_2 = aux->next;
  aux = PreviousItemArt(*List, aux);
  free(aux->next);
  aux->next = aux_2;
  return 0;
};

int RemoveItemVen(struct VendorNode** List, int position) {
  if (*List == NULL) { return 1; }
  if ((*List)->next == NULL) { free(*List); *List = NULL; return 0; }
  struct VendorNode* aux = MALLOC_VEN;
  struct VendorNode* aux_2 = MALLOC_VEN;
  if (position <= 0) {
    aux = (*List)->next;
    free(*List);
    *List = aux;
    return 0;
  }
  aux = *List;
  while(aux->next != NULL && position-- > 0) { aux = aux->next; }
  aux_2 = aux->next;
  aux = PreviousItemVen(*List, aux);
  free(aux->next);
  aux->next = aux_2;
  return 0;
};

int RemoveItemCli(struct ClientNode** List, int position) {
  if (*List == NULL) { return 1; }
  if ((*List)->next == NULL) { free(*List); *List = NULL; return 0; }
  struct ClientNode* aux = MALLOC_CLI;
  struct ClientNode* aux_2 = MALLOC_CLI;
  if (position <= 0) {
    aux = (*List)->next;
    free(*List);
    *List = aux;
    return 0;
  }
  aux = *List;
  while(aux->next != NULL && position-- > 0) { aux = aux->next; }
  aux_2 = aux->next;
  aux = PreviousItemCli(*List, aux);
  free(aux->next);
  aux->next = aux_2;
  return 0;
};

struct ArticleNode* GetNodeArt(struct ArticleNode* List, int position) {
  if (List == NULL) { return NULL; }
  if ((List)->next == NULL || position <= 0) { return List; }
  struct ArticleNode* aux = MALLOC_ART;
  aux = List;
  while(aux->next != NULL && position-- > 0) { aux = aux->next; }
  return aux;
};

struct VendorNode* GetNodeVen(struct VendorNode* List, int position) {
  struct Date date = {0, 0, 0};
  if (List == NULL) { return NULL; }
  if ((List)->next == NULL || position <= 0) { return List; }
  struct VendorNode* aux = MALLOC_VEN;
  aux = List;
  while(aux->next != NULL && position-- > 0) { aux = aux->next; }
  return aux;
};

struct ClientNode* GetNodeCli(struct ClientNode* List, int position) {
  struct Date date = {0, 0, 0};
  if (List == NULL) { return NULL; }
  if ((List)->next == NULL || position <= 0) { return List; }
  struct ClientNode* aux = MALLOC_CLI;
  aux = List;
  while(aux->next != NULL && position-- > 0) { aux = aux->next; }
  return aux;
};

void ReadFileArt(struct ArticleNode** List, char dir[]) {
  FILE *f;
  f = fopen(dir, "r");
  if (f == NULL) { return; }

  // Vaciamos la lista
  if (*List != NULL) {
    while((*List) != NULL) {
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
    ENTER_CONTINUAR;
    return;
  }
  while (1) {
    input_code = fscanf(f, "%s", article.code);
    input_code = fscanf(f, "%s", article.name);
    input_code = fscanf(f, "%f", &article.price);
    input_code = fscanf(f, "%d", &article.ammount);
    if (input_code != EOF) {
      printf("\n");
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
  if (f == NULL) {
    fclose(f);
    printf("  El archivo no se ha podido crear, no se ha podido guardar\n");
    ENTER_CONTINUAR;
    return;
  }

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

void PrintMenuArticulos(void) {
  CLEAR;
  printf("\n");
  printf("  ||===============================||\n");
  printf("  || Menu Articulos                ||\n");
  printf("  ||===============================||\n");
  printf("  || [1] Agregar un Articulo       ||\n");
  printf("  || [2] Remover un Articulo       ||\n");
  printf("  || [3] Modificar un Articulo     ||\n");
  printf("  || [4] Guardar en Archivo        ||\n");
  printf("  || [5] Cargar de un Archivo      ||\n");
  printf("  || [6] Leer Lista de Articulos   ||\n");
  printf("  ||                               ||\n");
  printf("  || [0] Regresar                  ||\n");
  printf("  ||===============================||\n");
};

void MenuManejoArticulos() {
  char sel[2];
  char buffer[64];
  int position;
  struct Article art;
  while (1) {
    PrintMenuArticulos();
    printf("\n");
    printf("  Seleccion: ");
    scanf("%1s", sel);
    switch(sel[0]) {
      //
      // CASO AGREGAR ARTICULO
      //
      case '1':
        art.code[0] = '\0';
        art.name[0] = '\0';
        art.price = 0;
        art.ammount = 0;

        while (1) {
          CLEAR;
          PrintMenuArticulos();
          printf("  ||                               ||\n");
          PrintItemAsTableArt(art, "Articulo Actual");
          printf("\n");
          if (art.code[0] == '\0') {
            printf("  Ingrese el Codigo del articulo: ");
            CLR_BUF; scanf("%19s", buffer);
            strcpy(art.code, buffer);
            continue; }
          if (art.name[0] == '\0') {
            printf("  Ingrese el Nombre del articulo: ");
            CLR_BUF; scanf("%19s", buffer);
            strcpy(art.name, buffer);
            continue; }
          if (art.price <= 0) {
            printf("  Ingrese el Precio del articulo: ");
            CLR_BUF; scanf("%10s", buffer);
            art.price = atof(buffer);
            continue; }
          if (art.ammount <= 0) {
            printf("  Ingrese la Cantidad de articulos: ");
            CLR_BUF; scanf("%10s", buffer);
            art.ammount = atoi(buffer);
            continue; }
          break;
        }

        while (1) {
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
          CLR_BUF; scanf("%10s", buffer);
          position = atoi(buffer);
          if (position == -1) { position = INT32_MAX; }
          if (position < -1) { continue; }
          break;
        }

        CLEAR;
        PrintMenuArticulos();
        printf("  ||                               ||\n");
        PrintItemAsTableArt(art, "Articulo Agregado");
        printf("\n");
        printf("  Articulo agregado a la lista!\n");
        ENTER_CONTINUAR;
        InsertItemArt(&ArticlesList, art, position);
        break;
      //
      // CASO ELIMINAR ARTICULO
      //
      case '2':
        if (ArticlesList == NULL) {
          printf("\n");
          printf("  La lista es NULL, no se puede eliminar nada");
          ENTER_CONTINUAR;
          break;
        }

        while (1) {
          position = -2;
          CLEAR;
          PrintMenuArticulos();
          printf("\n");
          printf("  Ingrese la posicion del articulo a eliminar: \n");
          printf("  [0, a-z, A-Z] Eliminar el primer articulo de la lista\n");
          printf("  [-1] Eliminar el ultimo articulo de la lista\n");
          printf("  Posicion: ");
          CLR_BUF; scanf("%10s", buffer);
          position = atoi(buffer);
          if (position == -1) { position = INT32_MAX; }
          if (position < -1) { continue; }
          break;
        }

        art = GetNodeArt(ArticlesList, position)->article;
        if (art.name[0]) {
          CLEAR;
          PrintMenuArticulos();
          printf("  ||                               ||\n");
          PrintItemAsTableArt(art, "Articulo a Eliminar");
          printf("\n");
          printf("  Eliminar %s de la lista?\n", art.name);
          printf("  [S] Eliminar\n");
          printf("  [N] No Eliminar\n");
          CLR_BUF; scanf("%1s", buffer);
        }
        if (!(buffer[0] == 's' || buffer[0] == 'S')) {
          printf("  No se ha eliminado ningun elemento\n");
        } else if (RemoveItemArt(&ArticlesList, position)) {
          printf("  La lista es NULL, no se ha podido eliminar ningun elemento\n");
        } else {
          printf( "  Se ha eliminado %s de la lista\n", art.name);
        } ENTER_CONTINUAR;
        break;
      //
      // CASO MODIFICAR ARTICULO
      //
      case '3':
        if (ArticlesList == NULL) {
          printf("\n");
          printf("  La lista es NULL, no se puede modificar nada");
          ENTER_CONTINUAR;
          break;
        }

        art.code[0] = '\0';
        art.name[0] = '\0';
        art.price = 0;
        art.ammount = 0;


        while (ArticlesList != NULL) {
          position = -2;
          CLEAR;
          PrintMenuArticulos();
          printf("\n");
          printf("  Ingrese la posicion del articulo a modificar: \n");
          printf("  [0, a-z, A-Z] Modificar el primer articulo de la lista\n");
          printf("  [-1] Modificar el ultimo articulo de la lista\n");
          printf("  Posicion: ");
          CLR_BUF; scanf("%10s", buffer);
          position = atoi(buffer);
          if (position == -1) { position = INT32_MAX; }
          if (position < -1) { continue; }
          break;
        }

        struct ArticleNode* aux = GetNodeArt(ArticlesList, position);

        while (1) {
          CLEAR;
          PrintMenuArticulos();
          printf("  ||                               ||\n");
          PrintItemAsTableArt(aux->article, "Articulo a Modificar");
          printf("\n");
          printf("  [-] No modificar\n");
          if (art.code[0] == '\0') {
            printf("  Ingrese el Nuevo Codigo del articulo: ");
            CLR_BUF; scanf("%19s", buffer);
            strcpy(art.code, buffer);
            if (buffer[0] == '-') { strcpy(art.code, aux->article.code); }
            if (art.code[0] != '\0') { strcpy(aux->article.code, art.code); }
            continue; }
          if (art.name[0] == '\0') {
            printf("  Ingrese el Nombre del articulo: ");
            CLR_BUF; scanf("%19s", buffer);
            strcpy(art.name, buffer);
            if (buffer[0] == '-') { strcpy(art.name, aux->article.name); }
            if (art.name[0] != '\0') { strcpy(aux->article.name, art.name); }
            continue; }
          if (art.price <= 0) {
            printf("  Ingrese el Precio del articulo: ");
            CLR_BUF; scanf("%10s", buffer);
            art.price = atof(buffer);
            if (buffer[0] == '-') { art.price = aux->article.price; }
            if (art.price > 0) { aux->article.price = art.price; }
            continue; }
          if (art.ammount <= 0) {
            printf("  Ingrese la Cantidad de articulos: ");
            CLR_BUF; scanf("%10s", buffer);
            art.ammount = atoi(buffer);
            if (buffer[0] == '-') { art.ammount = aux->article.ammount; }
            if (art.ammount > 0) { aux->article.ammount = art.ammount; }
            continue; }
          break;
        }

        CLEAR;
        PrintMenuArticulos();
        printf("  ||                               ||\n");
        PrintItemAsTableArt(art, "Articulo Modificado");
        printf("\n");
        ENTER_CONTINUAR;
        break;
      //
      // CASO GUARDAR ARTICULO
      //
      case '4':
        if (ArticlesList == NULL) {
          printf("\n");
          printf("  La lista es NULL, no se puede guardar");
          ENTER_CONTINUAR;
          break;
        }

        buffer[0] = '\n';
        while (buffer[0] == '\n') {
          CLEAR;
          PrintMenuArticulos();
          printf("\n");
          printf("  Ingrese el nombre del archivo (Sin txt)\n");
          printf("  Nombre: ");
          CLR_BUF; scanf("%58s", buffer);
        }

        strcat(buffer, ".txt");
        SaveFileArt(&ArticlesList, buffer);

        CLEAR;
        PrintMenuArticulos();
        printf("\n");
        printf("  Lista guardada en %s\n", buffer);
        ENTER_CONTINUAR;
        break;
      //
      // CASO GUARDAR ARTICULO
      //
      case '5':
        if (ArticlesList != NULL) {
          printf("\n");
          printf("  La lista NO es NULL, seguro que quiere continuar?\n");
          printf("  [S] Continuar\n");
          printf("  [N] Retornar\n");
          CLR_BUF; buffer[0] = getchar();
          if (!(buffer[0] == 's' || buffer[0] == 'S')) { break; }
        }

        buffer[0] = '\n';
        while (buffer[0] == '\n') {
          CLEAR;
          PrintMenuArticulos();
          printf("\n");
          printf("  Ingrese el nombre del archivo (Sin txt)\n");
          printf("  Nombre: ");
          CLR_BUF; scanf("%58s", buffer);
        }

        strcat(buffer, ".txt");
        ReadFileArt(&ArticlesList, buffer);

        CLEAR;
        PrintMenuArticulos();
        printf("\n");
        printf("  Lista cargada de %s.txt\n", buffer);
        printf("  [S] Leer lista\n");
        printf("  [N] Continuar\n");
        CLR_BUF; buffer[0] = getchar();
        if (buffer[0] == 'S' || buffer[0] == 's') { PrintItemListArt(ArticlesList); }
        break;
      case '6':
        if (ArticlesList == NULL) {
          printf("\n");
          printf("  La lista es NULL, no se puede visualizar");
          ENTER_CONTINUAR;
          break;
        }
        PrintItemListArt(ArticlesList);
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

void MainMenu() {
  char sel[2];
  while (1) {
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
    switch(sel[0]) {
      case '1':
        MenuManejoArticulos();
        break;
      case '2':
        break;
      case '3':
        break;
      case '0':
        return;
        break;
      default:
        TECLA_VALIDA;
    };
  }
};


int main(void) {
  MainMenu();
  return 0;
}
