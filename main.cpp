#include <stdio.h>
#include <string>

struct Article {
	std::string code = "";
	int price;
	int ammount;
	std::string name = "";
};
	
struct Client {
	int idNumber;
	std::string address;
	std::string cellphoneNumber;
	std::string name;
};

struct Vendor {
	int idNumber;
	int commissionPercentage;
	std::string name;
	std::string ingressDate;
};

struct ArticleNode { Article data; int key; ArticleNode* next = NULL; };
struct ClientNode { Client data; int key; ClientNode* next = NULL; };
struct VendorNode { Vendor data; int key; VendorNode* next = NULL; };

// OTHER FUNCTIONS

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
	if (position < 0) { printf("Cannot insert article in negative position"); return; }
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
T PopArticle(T_ptr* &list, int position = -1) {
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
T ReadArticle(T_ptr* list, int position = -1) {
	if (list == NULL) { printf("Cannot read value from NULL list, returning empty article\n"); return *new T; }
	if (list->next == NULL) { return list->data; }
	while (list->next->next != NULL && position != 1) {
		list = list->next; position--;
	} return list->next->data;
};

template <typename T_ptr, typename T>
void ModifyArticle(T_ptr* list, int position, T data) {
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

Article CreateArticle(std::string code, int price, int ammount, std::string name) {
	Article ret;
	ret.code = code;
	ret.price = price;
	ret.ammount = ammount;
	ret.name = name;
	return ret;
};

Client CreateClient(int idNumber, std::string address, std::string cellphoneNumber, std::string name) {
	Client ret;
	ret.idNumber = idNumber;
	ret.address = address;
	ret.cellphoneNumber = cellphoneNumber;
	ret.name = name;
	return ret;
};

Vendor CreateVendor(int idNumber, int commissionPercentage, std::string name, std::string ingressDate) {
	Vendor ret;
	ret.idNumber = idNumber;
	ret.commissionPercentage = commissionPercentage;
	ret.name = name;
	ret.ingressDate = ingressDate;
	return ret;
};

// END ARTICLES

int main() {
	ArticleNode* ArticleN = NULL;
	ClientNode* ClientN = NULL;
	VendorNode* VendorN = NULL;

	PushElement<ArticleNode, Article>(ArticleN,
		CreateArticle("A123", 100, 2, "Cambur"));
	PushElement<ClientNode, Client>(ClientN,
		CreateClient(30142718, "My Home", "04143103358", "Humberto Aleman"));
	PushElement<VendorNode, Vendor>(VendorN,
		CreateVendor(9878643, 20, "Robert Topala", "01/01/1970"));
	AppendElement<ArticleNode, Article>(ArticleN,
		CreateArticle("A123", 100, 2, "Cambur"));
	AppendElement<ClientNode, Client>(ClientN,
		CreateClient(30142718, "My Home", "04143103358", "Humberto Aleman"));
	AppendElement<VendorNode, Vendor>(VendorN,
		CreateVendor(9878643, 20, "Robert Topala", "01/01/1970"));
	InsertElement<ArticleNode, Article>(ArticleN,
		CreateArticle("A123", 100, 2, "Cambur"), 0);
	InsertElement<ClientNode, Client>(ClientN,
		CreateClient(30142718, "My Home", "04143103358", "Humberto Aleman"), 0);
	InsertElement<VendorNode, Vendor>(VendorN,
		CreateVendor(9878643, 20, "Robert Topala", "01/01/1970"), 2);
	InsertElement<ArticleNode, Article>(ArticleN,
		CreateArticle("A123", 100, 2, "Cambur"), 2);
	InsertElement<ClientNode, Client>(ClientN,
		CreateClient(30142718, "My Home", "04143103358", "Humberto Aleman"), 0);
	InsertElement<VendorNode, Vendor>(VendorN,
		CreateVendor(9878643, 20, "Robert Topala", "01/01/1970"), 2);
	InsertElement<ArticleNode, Article>(ArticleN,
		CreateArticle("A123", 100, 2, "Cambur"), 99);
	InsertElement<ClientNode, Client>(ClientN,
		CreateClient(30142718, "My Home", "04143103358", "Humberto Aleman"), 99);
	InsertElement<VendorNode, Vendor>(VendorN,
		CreateVendor(9878643, 20, "Robert Topala", "01/01/1970"), 99);

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
