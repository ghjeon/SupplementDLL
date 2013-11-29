#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <memory.h>

#define MAX 1000

typedef struct Warehouse *Warehouse_pointer;
typedef struct Warehouse {
	Warehouse_pointer prev;
	Warehouse_pointer next;
	int no; 
	char* name;
	char* location;
}Warehouse;

typedef struct Product* Product_pointer;
typedef struct Product {
	Product_pointer prev;
	Product_pointer next;
	int no;
	char* name;
	int count;
	int barcode;
	char* manufacture;
	int expiry_date;
	int create_date;
	int in_price;
	int out_price;
	Warehouse_pointer location;
}Product;

Product *product;
Warehouse *warehouse;

void _p_Init();
void _w_Init();
Product_pointer _p_readNode(Product_pointer target, bool right);
Product_pointer _p_InsertNodeRight(Product_pointer target, Product_pointer node);
Product_pointer _p_InsertNodeLeft(Product_pointer target, Product_pointer node);
Product_pointer _p_InsertNode(Product_pointer node);
bool _p_deleteNode(Product_pointer target);
Product_pointer _p_findNode(int productNo);
Product_pointer _p_findNode(char* productName);
Product_pointer _p_findNode(Warehouse_pointer w);
Product_pointer _p_inputNode(Product_pointer target, bool right);
int _p_countNodes();
Warehouse_pointer _w_readNode(Warehouse_pointer target, bool right);
Warehouse_pointer _w_InsertNodeRight(Warehouse_pointer target, Warehouse_pointer node);
Warehouse_pointer _w_InsertNodeLeft(Warehouse_pointer target, Warehouse_pointer node);
Warehouse_pointer _w_InsertNode(Warehouse_pointer node);
bool _w_deleteNode(Warehouse_pointer target);
Warehouse_pointer _w_findNode(int houseNo);
Warehouse_pointer _w_findNode(char* houseName);
Warehouse_pointer _w_inputNode(Warehouse_pointer target, bool right);
int _w_countNodes();


void _p_Init()
{
	product = (Product*)malloc(sizeof(Product));
	product->prev = NULL;
	product->next = NULL;
}

void _w_Init()
{
	warehouse = (Warehouse*)malloc(sizeof(Warehouse));
	warehouse->prev = NULL;
	warehouse->next = NULL;
}

Product_pointer _p_readNode(Product_pointer target, bool right)
{
	printf("Product No : %d\r\n", target->no);
	printf("Product Name : %s\r\n", target->name);
	printf("Product Count : %d\r\n", target->count);
	printf("Product Barcode : %d\r\n", target->barcode);
	printf("Product Manufacture : %s\r\n", target->manufacture);
	printf("Product Expiray Date : %d\r\n", target->expiry_date);
	printf("Product Created Dated : %d\r\n", target->create_date);
	printf("Product Factory Price : %d\r\n", target->in_price);
	printf("Product Supply Price : %d\r\n", target->out_price);
	printf("Product Warehouse : %s", target->location->name);
	printf("Product Warehouse Location : %s", target->location);
	if (right)
		return target->next;
	else
		return target->prev;
}

Product_pointer _p_InsertNodeRight(Product_pointer target, Product_pointer node)
{
	Product_pointer newNode;
	Product_pointer rightNode;
	newNode = (Product_pointer)malloc(sizeof(Product));
	newNode = node;

	rightNode = target->next;
	newNode->next = rightNode;
	newNode->prev = target;
	target->next = newNode;

	if(rightNode != NULL)
		rightNode->prev = newNode;

	return newNode;
}

Product_pointer _p_InsertNodeLeft(Product_pointer target, Product_pointer node)
{
	Product_pointer leftNode;

	leftNode = target->prev;
	if(leftNode != NULL)
		return _p_InsertNodeRight(leftNode, node);
	return NULL;
}

Product_pointer _p_InsertNode(Product_pointer node)
{
	Product_pointer lastNode;

	for(lastNode = product; lastNode->next; lastNode = lastNode->next)
	{
	}
	return _p_InsertNodeRight(lastNode, node);
}

bool _p_deleteNode(Product_pointer target)
{
	Product_pointer prev,next;

	if(target == NULL || target == product)
		return false;

	prev = target->prev;
	next = target->next;

	prev->next = next;

	if(next != NULL)
		next->prev = prev;

	free(target);

	return true;
}

Product_pointer _p_findNode(int productNo)
{
	Product_pointer target;

	for (target = product->next; target; target = target->next)
	{
		if (target->no == productNo)
			return target;
	}
	return NULL;
}

Product_pointer _p_findNode(char* productName)
{
	Product_pointer target;

	for (target = product->next; target; target = target->next)
	{
		if (strcmp(target->name, productName) == 0)
			return target;
	}

	return NULL;
}

Product_pointer _p_findNode(Warehouse_pointer w)
{
	Product_pointer target;

	for (target = product->next; target; target = target->next)
	{
		if (target->location == w)
			return target;
	}

	return NULL;
}

Product_pointer _p_inputNode(Product_pointer target, bool right)
{
	Product_pointer newNode;

	char name[100], manufacture[100];
	int no, count, barcode, expiry_date, create_date, in_price, out_price;
	int warehouse_no;
	
	newNode = (Product_pointer)malloc(sizeof(Product));

	printf_s("Product No : ");
	scanf_s("%d", &no, sizeof(no));
	newNode->no = no;
	printf_s("Product Name : ");
	scanf_s("%s", &name, sizeof(name));
	newNode->name = (char*)malloc(sizeof(char)* 100);
	memcpy_s(newNode->name, sizeof(newNode->name)*100, name, sizeof(name));
	printf("Product Count : ");
	scanf_s("%d", &count, sizeof(count));
	newNode->count = count;
	printf("Product Barcode : ");
	scanf_s("%d", &barcode, sizeof(barcode));
	newNode->barcode = barcode;
	printf("Product Manufacture : ");
	scanf_s("%s", &manufacture, sizeof(manufacture));
	newNode->manufacture = (char*)malloc(sizeof(char)* 100);
	memcpy_s(newNode->manufacture, sizeof(newNode->manufacture)*100, manufacture, sizeof(manufacture));
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
	scanf_s("%s", &warehouse_no, sizeof(warehouse_no));
	newNode->location = _w_findNode(warehouse_no);
	
	if (target == NULL)
		return _p_InsertNode(newNode);
	else
	{
		if (right)
			return _p_InsertNodeRight(target, newNode);
		else
			return _p_InsertNodeLeft(target, newNode);
	}
}

int _p_countNodes()
{
	Product_pointer target;
	int count = 0;

	for (target = product->next; target; target = target->next)
		count++;

	return count;
}

Warehouse_pointer _w_readNode(Warehouse_pointer target, bool right)
{
	printf("Warehouse No : %d\r\n", target->no);
	printf("Warehouse Name : %s\r\n", target->name);
	printf("Warehouse Location : %s\r\n", target->location);
	if (right)
		return target->next;
	else
		return target->prev;
}

Warehouse_pointer _w_InsertNodeRight(Warehouse_pointer target, Warehouse_pointer node)
{
	Warehouse_pointer newNode;
	Warehouse_pointer rightNode;
	newNode = (Warehouse_pointer)malloc(sizeof(Warehouse));
	newNode = node;

	rightNode = target->next;
	newNode->next = rightNode;
	newNode->prev = target;
	target->next = newNode;

	if(rightNode != NULL)
		rightNode->prev = newNode;

	return newNode;
}

Warehouse_pointer _w_InsertNodeLeft(Warehouse_pointer target, Warehouse_pointer node)
{
	Warehouse_pointer leftNode;

	leftNode = target->prev;
	if(leftNode != NULL)
		return _w_InsertNodeRight(leftNode, node);
	return NULL;
}

Warehouse_pointer _w_InsertNode(Warehouse_pointer node)
{
	Warehouse_pointer lastNode;

	for(lastNode = warehouse; lastNode->next; lastNode = lastNode->next)
	{
	}
	return _w_InsertNodeRight(lastNode, node);
}

bool _w_deleteNode(Warehouse_pointer target)
{
	Warehouse_pointer prev,next;

	if(target == NULL || target == warehouse)
		return false;

	prev = target->prev;
	next = target->next;

	prev->next = next;

	if(next != NULL)
		next->prev = prev;

	free(target);

	return true;
}

Warehouse_pointer _w_findNode(int houseNo)
{
	Warehouse_pointer target;

	for (target = warehouse->next; target; target = target->next)
	{
		if (target->no == houseNo)
			return target;
	}

	return NULL;
}

Warehouse_pointer _w_findNode(char* houseName)
{
	Warehouse_pointer target;

	for (target = warehouse->next; target; target = target->next)
	{
		if (strcmp(target->name, houseName) == 0)
			return target;
	}

	return NULL;
}

Warehouse_pointer _w_inputNode(Warehouse_pointer target, bool right)
{
	char name[100];
	char location[100];
	Warehouse_pointer newNode;
	int no;

	newNode = (Warehouse_pointer)malloc(sizeof(Warehouse));

	printf("Warehouse No : ");
	scanf_s("%d", &no, sizeof(no));
	newNode -> no = no;
	printf("Warehouse Name : ");
	scanf_s("%s", &name, sizeof(name));
	newNode->name = (char*)malloc(sizeof(char) * 100);
	memcpy_s(newNode->name, sizeof(newNode->name) * 100, name, sizeof(name));
	printf("Warehouse Location : ");
	scanf_s("%s", &location, sizeof(location));
	newNode->location = (char*)malloc(sizeof(char) * 100);
	memcpy_s(newNode->location, sizeof(newNode->location) * 100, location, sizeof(location));

	if (target == NULL)
		return	_w_InsertNode(newNode);
	else
	{
		if (right)
			return _w_InsertNodeRight(target, newNode);
		else
			return _w_InsertNodeLeft(target, newNode);
	}
}

int _w_countNodes()
{
	Warehouse_pointer target;
	int count = 0;

	for (target = warehouse->next; target; target = target->next)
		count++;
	
	return count;
}

void main()
{
	_w_Init();
	_p_Init();
	
}