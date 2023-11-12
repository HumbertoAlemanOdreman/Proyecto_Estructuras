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

struct Vendors {
	int idNumber;
	int commissionPercentage;
	std::string name;
	std::string ingressDate;
};

struct ArticleNode { Article data; int key; ArticleNode* next = NULL; };
struct ClientNode { Client data; ClientNode* next = NULL; };
struct VendorsNode { Vendors data; VendorsNode* next = NULL; };

// OTHER FUNCTIONS

// END OTHER FUNCTIONS

// ARTICLES

int GetMaxKey(ArticleNode* list) {
	if (list == NULL) { return 0; }
	int max = 0;
	while (list->next != NULL) {
		if (list->key > max) { max = list->key; }
		list = list->next;
	}
	if (list->key > max) { max = list->key; }
	return ++max;
}

// Add at begining
void PushArticle(ArticleNode* &list, std::string code, int price, int ammount, std::string name) {
	ArticleNode* tmp = new ArticleNode;
	tmp->next = list;
	tmp->key = GetMaxKey(list);
	tmp->data.code = code;
	tmp->data.price = price;
	tmp->data.ammount = ammount;
	tmp->data.name = name;
	list = tmp;
};

// Add at end
void AppendArticle(ArticleNode* &list, std::string code, int price, int ammount, std::string name) {
	if (list == NULL) { PushArticle(list, code, price, ammount, name); return; }
	ArticleNode* tmp = list;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	};
	tmp->next = new ArticleNode;
	tmp->next->key = GetMaxKey(list);
	tmp->next->data.code = code;
	tmp->next->data.price = price;
	tmp->next->data.ammount = ammount;
	tmp->next->data.name = name;
};

// Add at specified position
void InsertArticle(ArticleNode* &list, std::string code, int price, int ammount, std::string name, int position) {
	if (position < 0) { printf("Cannot insert article in negative position"); return; }
	if (list == NULL || position == 0) { PushArticle(list, code, price, ammount, name); return; }
	ArticleNode* tmp = list;
	while (tmp->next != NULL && position != 1) {
		tmp = tmp->next; position--;
	}
	ArticleNode* aux = tmp->next;
	int key = GetMaxKey(list);
	tmp->next = new ArticleNode;
	tmp->next->key = key; 
	tmp->next->data.code = code;
	tmp->next->data.price = price;
	tmp->next->data.ammount = ammount;
	tmp->next->data.name = name;
	tmp->next->next = aux;
	return;
};

// Remove at position (if no position specified, at end)
Article PopArticle(ArticleNode* &list, int position = -1) {
	if (list == NULL) { printf("Cannot read value from NULL list, returning empty article\n"); return *new Article; }
	if (list->next == NULL) { Article aux = list->data; delete list; list = NULL; return aux; }
	ArticleNode* tmp = list;
	while (tmp->next->next != NULL) {
		if (position == 1) { break; }
		tmp = tmp->next; position--;
	} ArticleNode* aux = tmp->next->next;
	Article ret_val = tmp->next->data;
	delete tmp->next; tmp->next = aux;
	return ret_val;
};

// Read at position (if no position specified, at end)
Article ReadArticle(ArticleNode* list, int position = -1) {
	if (list == NULL) { printf("Cannot read value from NULL list, returning empty article\n"); return *new Article; }
	if (list->next == NULL) { return list->data; }
	while (list->next->next != NULL && position != 1) {
		list = list->next; position--;
	} return list->next->data;
};

void ModifyArticle(ArticleNode* list, int position, std::string code, int price, int ammount, std::string name) {
	while (list->next != NULL && position > 0) {
		list = list->next; position--;
	}
	list->data.code = code;
	list->data.price = price;
	list->data.ammount = ammount;
	list->data.name = name;
};

void PrintArticles(ArticleNode* list) {
	if (list == NULL) { printf("NULL\n"); return; }
	while (list->next != NULL) {
		printf("%s -> ", &list->data.name[0]);
		list = list->next;
	} printf("%s -> NULL\n", &list->data.name[0]);
};

void PrintKeys(ArticleNode* list) {
	if (list == NULL) { printf("NULL\n"); return; }
	while (list->next != NULL) {
		printf("%d -> ", list->key);
		list = list->next;
	} printf("%d -> NULL\n", list->key);
};

// END ARTICLES

int main() {
	ArticleNode* InitialNode = NULL;
	InsertArticle(InitialNode, "CEA", 10, 1, "Pootis Engage CD", 4);
	InsertArticle(InitialNode, "CEA", 10, 1, "Big Chungus Action Figure", 0);
	InsertArticle(InitialNode, "CEA", 10, 1, "Skibidi Toilet Collectors Edition", 0);
	InsertArticle(InitialNode, "CEA", 10, 1, "Fanum Tax Reduction Notice", 0);
	InsertArticle(InitialNode, "CEA", 10, 1, "Lobotomy Kit", 10);
	InsertArticle(InitialNode, "CEA", 10, 1, "Lobotomy Kit", 3);
	InsertArticle(InitialNode, "CEA", 10, 1, "Lobotomy Kit", 3);

	PrintArticles(InitialNode);
	PrintKeys(InitialNode);
	printf("%d", GetMaxKey(InitialNode));


	return 0;
}
