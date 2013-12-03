#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <memory.h>

#define MAX 1000

typedef struct Warehouse *Warehouse_pointer; // pointer type of warehose structure
typedef struct Warehouse { // warehouse structure 
	Warehouse_pointer prev; // previous node
	Warehouse_pointer next; // next node
	int no; // warehouse no
	char* name; // warehouse name
	char* location; // warehouse location
}Warehouse;

typedef struct Product* Product_pointer; // pointer type of product structure
typedef struct Product { // product structure
	Product_pointer prev; // previous node
	Product_pointer next; // next node
	int no; // product no
	char* name; // product no
	int count; // product remaining count
	int barcode; // product barcode 
	char* manufacture; // product manufacture
	int expiry_date; // product expiry date
	int create_date; // product created date 
	int in_price; // product income price 
	int out_price; // product sale price
	Warehouse_pointer location; // product warehouse location
}Product;

Product *product; // global variable of product structure list
Product *p_searchResults; //global variable of product structure list using search results
Warehouse *warehouse; // global variable of product warehouse list

/* function header */

void _p_Init();
void _w_Init();
void _p_readNode(Product_pointer target);
Product_pointer _p_InsertNodeRight(Product_pointer target, Product_pointer node);
Product_pointer _p_InsertNodeLeft(Product_pointer target, Product_pointer node);
Product_pointer _p_InsertNode(Product_pointer node);
bool _p_deleteNode(Product_pointer target);
Product_pointer _p_findNode(int productNo);
Product_pointer _p_findNode(char* productName);
Product_pointer _p_findNode(Warehouse_pointer w);
Product_pointer _p_inputNode(Product_pointer target, bool right);
Product_pointer _p_copyNode(Product_pointer target, Product_pointer node);
int _p_countNodes();
void _w_readNode(Warehouse_pointer target);
Warehouse_pointer _w_InsertNodeRight(Warehouse_pointer target, Warehouse_pointer node);
Warehouse_pointer _w_InsertNodeLeft(Warehouse_pointer target, Warehouse_pointer node);
Warehouse_pointer _w_InsertNode(Warehouse_pointer node);
bool _w_deleteNode(Warehouse_pointer target);
Warehouse_pointer _w_findNode(int houseNo);
Warehouse_pointer _w_findNode(char* houseName);
Warehouse_pointer _w_inputNode(Warehouse_pointer target, bool right);
Warehouse_pointer _w_copyNode(Warehouse_pointer target, Warehouse_pointer node);
int _w_countNodes();

/* function header */


void _p_Init()
{ // initializing global product variable 
	free(product);
	product = (Product*)malloc(sizeof(Product));
	product->prev = NULL;
	product->next = NULL;
}

void _p_Init_Search()
{
	free(p_searchResults);
	p_searchResults = (Product*)malloc(sizeof(Product));
	p_searchResults->prev = NULL;
	p_searchResults->next = NULL;
}

void _w_Init()
{ // initializing global warehouse variable 
	free(warehouse);
	warehouse = (Warehouse*)malloc(sizeof(Warehouse));
	warehouse->prev = NULL;
	warehouse->next = NULL;
}

void _p_readNode(Product_pointer target)
{ // read product node
	if(target == NULL)
		return;

	printf("Product No : %d\r\n", target->no);
	printf("Product Name : %s\r\n", target->name);
	printf("Product Count : %d\r\n", target->count);
	printf("Product Barcode : %d\r\n", target->barcode);
	printf("Product Manufacture : %s\r\n", target->manufacture);
	printf("Product Expiray Date : %d\r\n", target->expiry_date);
	printf("Product Created Dated : %d\r\n", target->create_date);
	printf("Product Factory Price : %d\r\n", target->in_price);
	printf("Product Supply Price : %d\r\n", target->out_price);
	if (target->location != NULL)
	{
		printf("Product Warehouse : %s\r\n", target->location->name);
		printf("Product Warehouse Location : %s\r\n", target->location->location);
	}
	else
	{
		printf("Product has invailid warehouse information.\r\n");
	}
}

void _p_readAll()
{
	Product_pointer node; // create temp node

	for (node = product->next; node; node = node->next)
	{
		printf("========================\r\n");
		_p_readNode(node);
		printf("========================\r\n");
	}
	printf("Total : %d\r\n", _p_countNodes());
}

Product_pointer _p_InsertNodeRight(Product_pointer target, Product_pointer node)
{// insert product node 'node' to 'target''s right 
	Product_pointer newNode; // create temp node
	Product_pointer rightNode;

	newNode = (Product_pointer)malloc(sizeof(Product)); // allocate memory
	newNode = node; // allocate node to newNode

	rightNode = target->next; // get right node of target
	newNode->next = rightNode; // set next node 
	newNode->prev = target; // set previous node
	target->next = newNode; // link node

	if(rightNode != NULL) // if target has already right node
		rightNode->prev = newNode; // link node

	return newNode;
}

Product_pointer _p_InsertNodeLeft(Product_pointer target, Product_pointer node)
{// insert product node 'node' to 'target''s left
	Product_pointer leftNode; // crete temp node

	leftNode = target->prev; // get left node of target
	if(leftNode != NULL) // left node is exist
		return _p_InsertNodeRight(leftNode, node); // link target's left node and node -> node inserted target's left node
	return NULL; // target has not exist, cannot insert left node (may losing HEAD)
}

Product_pointer _p_InsertNode(Product_pointer node)
{//insert product node in product's last
	Product_pointer lastNode; // create temp node

	for (lastNode = product; lastNode->next; lastNode = lastNode->next) {} //find last node

	return _p_InsertNodeRight(lastNode, node);//insert node
}

Product_pointer _p_InsertNode(Product_pointer head, Product_pointer node)
{//insert product node in 'head''s last
	Product_pointer lastNode; // create temp node
	Product_pointer newNode;

	newNode = (Product_pointer)malloc(sizeof(Product));

	_p_copyNode(newNode, node);

	for (lastNode = head; lastNode->next; lastNode = lastNode->next){} // find last node

	return _p_InsertNodeRight(lastNode, newNode); // insert node
}

bool _p_deleteNode(Product_pointer target)
{
	Product_pointer prev,next; // create save node variable

	if(target == NULL || target == product) // if head or null node
		return false;

	prev = target->prev; // save prev node
	next = target->next; // save next node

	prev->next = next; // link prev's next node to target's next node

	if(next != NULL) // next node is proper node, link previous node
		next->prev = prev;

	free(target); // free memory 

	return true; 
}

Product_pointer _p_findNode(int productNo)
{//find product by product no
	Product_pointer target; // create temp node

	for (target = product->next; target; target = target->next) 
	{// loop for whole products list
		if (target->no == productNo) // condition check
			return target;
	}
	return NULL;
}

Product_pointer _p_findNode(char* productName)
{//find product by product name
	Product_pointer target; // create temp node

	for (target = product->next; target; target = target->next)
	{// loop for whole products list
		if (strcmp(target->name, productName) == 0) // compare strings
			return target;
	}

	return NULL;
}

Product_pointer _p_findNode(Warehouse_pointer w)
{//find products by product warehouse 
	Product_pointer target; // create temp node
	
	_p_Init_Search();

	for (target = product->next; target; target = target->next)
	{
		if (target->location == w)
			_p_InsertNode(p_searchResults, target); // add products to list
	}

	return p_searchResults;
}

Product_pointer _p_inputNode(Product_pointer target, bool right)
{//input node itmes and insert to list 
	Product_pointer newNode; // create node variable
	Warehouse_pointer w; // create temp warehouse node

	char name[100], manufacture[100]; 
	int no, count, barcode, expiry_date, create_date, in_price, out_price;
	int warehouse_no; // variable for input values
	
	newNode = (Product_pointer)malloc(sizeof(Product)); // allocate memory

	/* read attributes */
	printf_s("Product No : ");
	scanf_s("%d", &no, sizeof(no));
	newNode->no = no;
	printf_s("Product Name : ");
	scanf_s("%s", &name, sizeof(name));
	newNode->name = (char*)malloc(sizeof(char)* 100); // allocate memory for store strings
	memcpy_s(newNode->name, sizeof(newNode->name)*100, name, sizeof(name)); // copy input string into node item
	printf("Product Count : ");
	scanf_s("%d", &count, sizeof(count));
	newNode->count = count;
	printf("Product Barcode : ");
	scanf_s("%d", &barcode, sizeof(barcode));
	newNode->barcode = barcode;
	printf("Product Manufacture : ");
	scanf_s("%s", &manufacture, sizeof(manufacture));
	newNode->manufacture = (char*)malloc(sizeof(char)* 100); // allocate memory for store strings
	memcpy_s(newNode->manufacture, sizeof(newNode->manufacture)*100, manufacture, sizeof(manufacture)); // copy input string into node item
	printf("Product Expiry Date : ");
	scanf_s("%d", &expiry_date, sizeof(expiry_date));
	newNode->expiry_date = expiry_date;
	printf("Product Created Date : ");
	scanf_s("%d", &create_date, sizeof(create_date));
	newNode->create_date = create_date;
	printf("Product Factory Price : ");
	scanf_s("%d", &in_price, sizeof(in_price));
	newNode->in_price = in_price;
	printf("Product Supply Price : ");
	scanf_s("%d", &out_price, sizeof(out_price));
	newNode->out_price = out_price;
	printf("Product Warehouse No : ");
	scanf_s("%d", &warehouse_no, sizeof(warehouse_no));
	w = _w_findNode(warehouse_no); // find warehouse
	if (w == NULL) // warehouse not exists
	{
		printf("Warehouse not found! Insert fail.\r\n\r\n");
		return NULL; // insert fail
	}
	newNode->location = w; // set warehouse pointer
	
	if (target == NULL) // target not exists, insert last of the list
		return _p_InsertNode(newNode);
	else // target exists
	{
		if (right) // prev or next
			return _p_InsertNodeRight(target, newNode);
		else
			return _p_InsertNodeLeft(target, newNode);
	}
}

Product_pointer _p_copyNode(Product_pointer target, Product_pointer node)
{
	target->name = (char*)malloc(sizeof(node->name));
	memcpy_s(target->name, sizeof(target->name), node->name, sizeof(node->name));
	target->barcode = node->barcode;
	target->count = node->count;
	target->no = node->no;
	target->create_date = node->create_date;
	target->expiry_date = node->expiry_date;
	target->in_price = node->in_price;
	target->location = node->location;
	target->manufacture = (char*)malloc(sizeof(node->manufacture));
	memcpy_s(target->manufacture, sizeof(target->manufacture), node->manufacture, sizeof(node->manufacture));
	target->out_price = node->out_price;
	target->prev = NULL;
	target->next = NULL;
	return target;
}

int _p_countNodes()
{ // couting nodes
	Product_pointer target; // createing temp node
	int count = 0; // counter

	for (target = product->next; target; target = target->next) //loop for end of the list
		count++;

	return count; 
}

void _w_readNode(Warehouse_pointer target)
{ // read warehouse node 'target'
	if(target == NULL)
		return;

	printf("Warehouse No : %d\r\n", target->no);
	printf("Warehouse Name : %s\r\n", target->name);
	printf("Warehouse Location : %s\r\n", target->location);
}

void _w_readAll()
{
	Warehouse_pointer node; // create temp node

	for (node = warehouse->next; node; node = node->next)
	{
		printf("=========================\r\n");
		_w_readNode(node);
		printf("=========================\r\n");
	}
	printf("Total : %d\r\n", _w_countNodes());
}

Warehouse_pointer _w_InsertNodeRight(Warehouse_pointer target, Warehouse_pointer node)
{ // insert warehouse node 'node' to 'target' 's right
	Warehouse_pointer newNode; // create temp nodes
	Warehouse_pointer rightNode;
	newNode = (Warehouse_pointer)malloc(sizeof(Warehouse)); // allocate memory
	newNode = node; // allocate node to newNode

	rightNode = target->next; // get right node of target
	newNode->next = rightNode; // set next node of new node rightNode
	newNode->prev = target; // set prev node of new node to target
	target->next = newNode; // link node

	if(rightNode != NULL) // if target has right node
		rightNode->prev = newNode; // link node

	return newNode;
}

Warehouse_pointer _w_InsertNodeLeft(Warehouse_pointer target, Warehouse_pointer node)
{
	Warehouse_pointer leftNode; // create temp node

	leftNode = target->prev; // get left node of target
	if(leftNode != NULL) // left node exists
		return _w_InsertNodeRight(leftNode, node); // insert node
	return NULL; // cannot insert left node if target's prev is not exists (may losing head)
}

Warehouse_pointer _w_InsertNode(Warehouse_pointer node)
{// insert node to last of the warehouse list
	Warehouse_pointer lastNode; // create temp node

	for (lastNode = warehouse; lastNode->next; lastNode = lastNode->next) {} // find last

	return _w_InsertNodeRight(lastNode, node); // insert to last of list
}

bool _w_deleteNode(Warehouse_pointer target)
{
	Warehouse_pointer prev,next; //create save node variables

	if(target == NULL || target == warehouse) // if HEAD or target is null
		return false; // cannot delete node

	prev = target->prev; // save prev node
	next = target->next; // save next node

	prev->next = next; // link prev's next node to target's next node

	if(next != NULL)
		next->prev = prev; // if next is proper node, link prev node

	free(target); // deallocate memory

	return true;
}

Warehouse_pointer _w_findNode(int houseNo)
{//find warehouse node using warehouse no
	Warehouse_pointer target; // create temp node

	for (target = warehouse->next; target; target = target->next) // loop for list
	{
		if (target->no == houseNo) // condition
			return target;
	}

	return NULL;
}

Warehouse_pointer _w_findNode(char* houseName)
{//find warehouse node using house name
	Warehouse_pointer target; // create temp node

	for (target = warehouse->next; target; target = target->next) // loop for list
	{
		if (strcmp(target->name, houseName) == 0) // string comparison
			return target;
	}

	return NULL;
}

Warehouse_pointer _w_inputNode(Warehouse_pointer target, bool right)
{ // input node items and inser to list
	int no;
	char name[100]; 
	char location[100];  // input variables

	Warehouse_pointer newNode; // create node variables
	

	newNode = (Warehouse_pointer)malloc(sizeof(Warehouse)); // allocate memory

	printf("Warehouse No : "); 
	scanf_s("%d", &no, sizeof(no));
	newNode -> no = no;
	printf("Warehouse Name : ");
	scanf_s("%s", &name, sizeof(name));
	newNode->name = (char*)malloc(sizeof(char) * 100); // allocate memory for store strings
	memcpy_s(newNode->name, sizeof(newNode->name) * 100, name, sizeof(name)); // cpy input string into node
	fflush(stdin);
	printf("Warehouse Location : ");
	scanf_s("%s", &location, sizeof(location));
	newNode->location = (char*)malloc(sizeof(char) * 100); // allocate memory for store string
	memcpy_s(newNode->location, sizeof(newNode->location) * 100, location, sizeof(location)); // copy input string into node
	fflush(stdin);
	if (target == NULL) // target not exist, input item into last of the list
		return	_w_InsertNode(newNode);
	else // target exists
	{
		if (right) // prev or next
			return _w_InsertNodeRight(target, newNode);
		else
			return _w_InsertNodeLeft(target, newNode);
	}
}

int _w_countNodes()
{// counting nodes
	Warehouse_pointer target; // create temp node
	int count = 0; // counter

	for (target = warehouse->next; target; target = target->next) // loop for lists
		count++; 
	
	return count;
}

void main()
{
	int menu = -1;
	int key = 0;
	char keyword[100] = "";
	Warehouse_pointer w_temp = NULL;
	Product_pointer p_temp = NULL;

	_w_Init();
	_p_Init();
	printf("Welcome to DataStructureHW4!\r\n");
	while (menu != 0)
	{
		w_temp = NULL;
		p_temp = NULL;
		key = 0;
		printf("/--------------MENU-------------/\r\n");
		printf("1. View Warehouse Lits\r\n");
		printf("2. View Product Lists\r\n");
		printf("3. Insert Warehouse \r\n");
		printf("4. Insert Product \r\n");
		printf("5. Delete Warehouse\r\n");
		printf("6. Delete Product\r\n");
		printf("7. Find Warehouse using Warehouse No\r\n");
		printf("8. Find Warehouse using Warehouse Name\r\n");
		printf("9. Find Product using Product No\r\n");
		printf("10. Find Product using Product Name\r\n");
		printf("11. Find Product using Product Warehouse No\r\n");
		printf("/-------------------------------/\r\n");
		printf("Please enter the command no:");
		scanf_s("%d", &menu, sizeof(menu));
		switch (menu)
		{
			case 1:
				_w_readAll();
				break;
			case 2: 
				_p_readAll();
				break;
			case 3: 
				_w_inputNode(NULL, false);
				break;
			case 4: 
				_p_inputNode(NULL, false);
				break;
			case 5:
				printf("Please enter the Warehouse No : ");
				scanf_s("%d", &key, sizeof(key));
				w_temp = _w_findNode(key);
				if(w_temp == NULL)
				{
					printf("Cannot find Warehouse No #%d\r\n", key);
					break;
				}
				if(_w_deleteNode(w_temp))
				{
					printf("Succesfully delete Warehouse No #%d\r\n", key);
				}
				else
				{
					printf("Operation :: delete Warehouse No #%d fail.\r\n", key);
				}
				break;
			case 6: 
				printf("Please enter the Product No : ");
				scanf_s("%d", &key, sizeof(key));
				p_temp = _p_findNode(key);
				if(p_temp == NULL)
				{
					printf("Cannot find Product No #%d\r\n",key);
					break;
				}
				if(_p_deleteNode(p_temp))
				{
					printf("Succesfully delete Product No #%d\r\n", key);
				}
				else
				{
					printf("Operation :: delete Product No #%d fail.\r\n", key);
				}
				break;
			case 7: 
				printf("Please enter the Warehouse No : ");
				scanf_s("%d", &key, sizeof(key));
				w_temp = _w_findNode(key);
				if(w_temp == NULL)
				{
					printf("Cannot find Warehouse No #%d\r\n", key);
					break;
				}
				_w_readNode(w_temp);
				break;
			case 8: 
				printf("Please enter the Warehouse Name : ");
				scanf_s("%s", &keyword, sizeof(keyword));
				w_temp = _w_findNode(keyword);
				if(w_temp == NULL)
				{
					printf("Cannot find Warehouse Name :: %s\r\n", keyword);
					break;
				}
				_w_readNode(w_temp);
				break;
			case 9: 
				printf("Please enter the Product No : ");
				scanf_s("%d", &key, sizeof(key));
				p_temp = _p_findNode(key);
				if(p_temp == NULL)
				{
					printf("Cannot find Product No #%d\r\n",key);
					break;
				}
				_p_readNode(p_temp);
				break;
			case 10: 
				printf("Please enter the Product Name : ");
				scanf_s("%s", &keyword, sizeof(keyword));
				p_temp = _p_findNode(keyword);
				if(p_temp == NULL)
				{
					printf("Cannot find Product Name :: %s\r\n", keyword);
					break;
				}
				_p_readNode(p_temp);
				break;
			case 11: 
				printf("Please enter the warehouse No. : ");
				scanf_s("%d", &key, sizeof(key));
				w_temp = _w_findNode(key);
				if(w_temp == NULL)
				{
					printf("Cannot find warehouse #%d\r\n", key);
					break;
				}
				p_temp = _p_findNode(w_temp);
				for(Product_pointer p = p_temp->next; p; p = p->next)
				{
					printf("==========================\r\n");
					_p_readNode(p);
					printf("==========================\r\n");
				}
				break;
		}
	}
}