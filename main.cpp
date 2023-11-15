#include <cstdlib>
#include <fstream>
#include <string>

#define ARCHIVO_COLUMNAS 20
#define CLIENTE_COLUMNAS 20
#define VENDEDOR_COLUMNAS 20

struct Article {
	char code[ARCHIVO_COLUMNAS];
	char name[ARCHIVO_COLUMNAS];
	float price;
	int ammount;
};
	
struct Client {
	int idNumber;
	char address[CLIENTE_COLUMNAS];
	char cellphoneNumber[CLIENTE_COLUMNAS];
	char name[CLIENTE_COLUMNAS];
};

struct Vendor {
	int idNumber;
	int commissionPercentage;
	char name[VENDEDOR_COLUMNAS];
	char ingressDate[VENDEDOR_COLUMNAS];
};

struct ArticleNode { Article data; int key; ArticleNode* next = NULL; };
struct ClientNode { Client data; int key; ClientNode* next = NULL; };
struct VendorNode { Vendor data; int key; VendorNode* next = NULL; };

// OTHER FUNCTIONS

void CopyContents(char *arr1, char arr2[ARCHIVO_COLUMNAS]) { for(int i = 0; i < ARCHIVO_COLUMNAS; i++) *(arr1 + i*sizeof(char)) = arr2[i]; }

// END OTHER FUNCTIONS

// ARTICLES

template <typename T_ptr>
int GetMaxKey(T_ptr* list) {
	if (list == NULL) { return 0; }
	int max = 0;
	while (list->next != NULL) {
		if (list->key > max) { max = list->key; }
		list = list->next;
	} if (list->key > max) { max = list->key; }
	return ++max;
}

// Add at begining
template <typename T_ptr, typename T>
void PushElement(T_ptr* &list, T data) {
	T_ptr* tmp = new T_ptr;
	tmp->next = list;
	tmp->key = GetMaxKey<T_ptr>(list);
	tmp->data = data;
	list = tmp;
};

// Add at end
template <typename T_ptr, typename T>
void AppendElement(T_ptr* &list, T data) {
	if (list == NULL) { PushElement<T_ptr, T>(list, data); return; }
	T_ptr* tmp = list;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}; tmp->next = new T_ptr;
	tmp->next->key = GetMaxKey<T_ptr>(list);
	tmp->next->data = data;
};

// Add at specified position
template <typename T_ptr, typename T>
void InsertElement(T_ptr* &list, T data, int position) {
	if (list == NULL || position == 0) { PushElement<T_ptr, T>(list, data); return; }
	T_ptr* tmp = list;
	while (tmp->next != NULL && position != 1) {
		tmp = tmp->next; position--;
	} T_ptr* aux = tmp->next;
	int key = GetMaxKey<T_ptr>(list);
	tmp->next = new T_ptr;
	tmp->next->key = key;
	tmp->next->data = data;
	tmp->next->next = aux;
	return;
};

// Remove at position (if no position specified, at end)
template <typename T_ptr, typename T>
T PopElement(T_ptr* &list, int position = -1) {
	if (list == NULL) { printf("Cannot read value from NULL list, returning empty article\n"); return *new T; }
	if (list->next == NULL) { T aux = list->data; delete list; list = NULL; return aux; }
	T_ptr* tmp = list;
	while (tmp->next->next != NULL) {
		if (position == 1) { break; }
		tmp = tmp->next; position--;
	} T_ptr* aux = tmp->next->next;
	T ret_val = tmp->next->data;
	delete tmp->next; tmp->next = aux;
	return ret_val;
};

// Read at position (if no position specified, at end)
template <typename T_ptr, typename T>
T ReadElement(T_ptr* list, int position = -1) {
	if (list == NULL) { printf("Cannot read value from NULL list, returning empty article\n"); return *new T; }
	if (list->next == NULL) { return list->data; }
	while (list->next->next != NULL && position != 1) {
		list = list->next; position--;
	} return list->next->data;
};

template <typename T_ptr, typename T>
void ModifyElement(T_ptr* list, int position, T data) {
	while (list->next != NULL && position > 0) {
		list = list->next; position--;
	} list->data = data;
};

template <typename T_ptr>
void PrintElements(T_ptr* list) {
	if (list == NULL) { printf("NULL\n"); return; }
	while (list->next != NULL) {
		printf("%s -> ", &list->data.name[0]);
		list = list->next;
	} printf("%s -> NULL\n", &list->data.name[0]);
};

template <typename T_ptr>
void PrintKeys(T_ptr* list) {
	if (list == NULL) { printf("NULL\n"); return; }
	while (list->next != NULL) {
		printf("%d -> ", list->key);
		list = list->next;
	} printf("%d -> NULL\n", list->key);
};

Article CreateArticle(char code[ARCHIVO_COLUMNAS], int price, int ammount, char name[ARCHIVO_COLUMNAS]) {
	Article ret;
	CopyContents(&ret.code[0], code);
	ret.price = price;
	ret.ammount = ammount;
	CopyContents(&ret.name[0], name);
	return ret;
};

ArticleNode* ReadFileArticle(bool append = false, ArticleNode* list = NULL, int position = -1) {
	ArticleNode* tmp = append ? list : NULL;
	Article tmp_art;
	std::string input;
	std::ifstream f("Informacion/Articulos");

	while (!f.eof()) {
		getline(f, input); CopyContents(tmp_art.code, input);
		getline(f, input); tmp_art.price = std::atoi(&input[0]);
		getline(f, input); tmp_art.ammount = std::atoi(&input[0]);
		getline(f, input); tmp_art.name = input;
		if (!f.eof()) { InsertElement<ArticleNode, Article>(tmp, tmp_art, position); if (append) { position++; } }
	} f.close(); return tmp;
};

Client CreateClient(int idNumber, std::string address, std::string cellphoneNumber, std::string name) {
	Client ret;
	ret.idNumber = idNumber;
	ret.address = address;
	ret.cellphoneNumber = cellphoneNumber;
	ret.name = name;
	return ret;
};

ClientNode* ReadFileClientes(bool append = false, ClientNode* list = NULL, int position = -1) {
	ClientNode* tmp = append ? list : NULL;
	Client tmp_cli;
	std::string input;
	std::ifstream f("Informacion/Clientes");

	while (!f.eof()) {
		getline(f, input); tmp_cli.idNumber = std::atoi(&input[0]);
		getline(f, input); tmp_cli.address = input;
		getline(f, input); tmp_cli.cellphoneNumber = input;
		getline(f, input); tmp_cli.name = input;
		if (!f.eof()) { InsertElement<ClientNode, Client>(tmp, tmp_cli, position); if (append) { position++; } }
	} f.close(); return tmp;
};

Vendor CreateVendor(int idNumber, int commissionPercentage, std::string name, std::string ingressDate) {
	Vendor ret;
	ret.idNumber = idNumber;
	ret.commissionPercentage = commissionPercentage;
	ret.name = name;
	ret.ingressDate = ingressDate;
	return ret;
};

VendorNode* ReadFileVendor(bool append = false, VendorNode* list = NULL, int position = -1) {
	VendorNode* tmp = append ? list : NULL;
	Vendor tmp_ven;
	std::string input;
	std::ifstream f("Informacion/Vendedores");

	while (!f.eof()) {
		getline(f, input); tmp_ven.idNumber = std::atoi(&input[0]);
		getline(f, input); tmp_ven.commissionPercentage = std::atoi(&input[0]);
		getline(f, input); tmp_ven.name = input;
		getline(f, input); tmp_ven.ingressDate = input;
		if (!f.eof()) { InsertElement<VendorNode, Vendor>(tmp, tmp_ven, position); if (append) { position++; } }
	} f.close(); return tmp;
};

// END ARTICLES

int main() {
	ArticleNode* ArticleN = NULL;
	ClientNode* ClientN = NULL;
	VendorNode* VendorN = NULL;

	ArticleN = ReadFileArticle();
	ArticleN = ReadFileArticle(true, ArticleN, 1);
	ClientN = ReadFileClientes();
	VendorN = ReadFileVendor();

	PrintKeys<ArticleNode>(ArticleN);
	PrintElements<ArticleNode>(ArticleN);
	printf("\n");

	PrintKeys<ClientNode>(ClientN);
	PrintElements<ClientNode>(ClientN);
	printf("\n");

	PrintKeys<VendorNode>(VendorN);
	PrintElements<VendorNode>(VendorN);
	printf("\n");

	return 0;
}
