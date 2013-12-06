#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <memory.h>

#define MAX 1000
#define TRUE 1
#define FALSE 0

typedef struct Warehouse *Warehouse_pointer; // pointer type of warehose structure
typedef struct Product* Product_pointer; // pointer type of product structure

typedef struct Warehouse { // warehouse structure 
	Warehouse_pointer prev; // previous node
	Warehouse_pointer next; // next node
	int no; // warehouse no
	char* name; // warehouse name
	char* location; // warehouse location
	Product_pointer products;
}Warehouse;

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
bool _p_deleteNode(Product_pointer target, bool isRecursiveCall);
Product_pointer _p_findTargetNodeByNo(Product_pointer head, int productNo);
Product_pointer _p_findNodeByNo(int productNo);
Product_pointer _p_findNodeByName(char* productName);
Product_pointer _p_findNodeByWarehouse(Warehouse_pointer w);
Product_pointer _p_inputNode(Product_pointer target, bool right);
Product_pointer _p_copyNode(Product_pointer target, Product_pointer node);
Product_pointer _p_joinNode(Product_pointer One, Product_pointer Two);
int _p_countNodes();
void _w_readNode(Warehouse_pointer target);
Warehouse_pointer _w_InsertNodeRight(Warehouse_pointer target, Warehouse_pointer node);
Warehouse_pointer _w_InsertNodeLeft(Warehouse_pointer target, Warehouse_pointer node);
Warehouse_pointer _w_InsertNode(Warehouse_pointer node);
bool _w_deleteNode(Warehouse_pointer target);
Warehouse_pointer _w_findNodeByNo(int houseNo);
Warehouse_pointer _w_findNodeByName(char* houseName);
Warehouse_pointer _w_inputNode(Warehouse_pointer target, bool right);
Warehouse_pointer _w_copyNode(Warehouse_pointer target, Warehouse_pointer node);
Warehouse_pointer _w_joinNode(Warehouse_pointer One, Warehouse_pointer Two);
int _w_countNodes();

/* function header */


void _p_Init()
{ // initializing global product variable 
	free(product);
	product = (Product*)malloc(sizeof(Product));
	product->prev = product;
	product->next = product;
}

void _p_Init_Search()
{
	free(p_searchResults);
	p_searchResults = (Product*)malloc(sizeof(Product));
	p_searchResults->prev = p_searchResults;
	p_searchResults->next = p_searchResults;
}

void _w_Init()
{ // initializing global warehouse variable 
	free(warehouse);
	warehouse = (Warehouse*)malloc(sizeof(Warehouse));
	warehouse->prev = warehouse;
	warehouse->next = warehouse;
	warehouse->products = NULL;
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
		if(node == product)
			break;
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

	if(rightNode != product) // if target has not last of the list
		rightNode->prev = newNode; // link node

	return newNode;
}

Product_pointer _p_InsertNodeLeft(Product_pointer target, Product_pointer node)
{// insert product node 'node' to 'target''s left
	Product_pointer leftNode; // crete temp node

	leftNode = target->prev; // get left node of target
	if(leftNode != product) // left node is not start node
		return _p_InsertNodeRight(leftNode, node); // link target's left node and node -> node inserted target's left node
	return NULL; // target has start node, cannot insert left node (may losing HEAD)
}

Product_pointer _p_InsertNode(Product_pointer node)
{//insert product node in product's last
	return _p_InsertNodeRight(product->prev->next, node);//insert node
}

Product_pointer _p_InsertTargetNode(Product_pointer head, Product_pointer node)
{//insert product node in 'head''s last
	Product_pointer newNode;

	newNode = (Product_pointer)malloc(sizeof(Product));

	_p_copyNode(newNode, node);

	return _p_InsertNodeRight(head, newNode); // insert node
}

bool _p_deleteNode(Product_pointer target, bool isRecusiveCall)
{
	Product_pointer temp; // create save node variable
	Warehouse_pointer w;

	if(target == NULL || target == product) // if head or null node
		return false;

	w = target->location;

	temp = _p_findTargetNodeByNo(w->products, target->no);
	if(temp == NULL)
	{
		printf("Invalid Product!\r\n");
		return false;
	}

	if(isRecusiveCall == false)
	{
		if(_p_deleteNode(temp, true) == false)
		{
			printf("Delete product in warehouse were failed! Operation aborted.\r\n");
			return false;
		}
	}

	target->prev->next = target->next;
	target->next->prev = target->prev;
	target->next = target;
	target->prev = target;

	free(target); // free memory 

	return true; 
}

Product_pointer _p_findTargetNodeByNo(Product_pointer head, int productNo)
{//find product by product no in 'head'
	Product_pointer target; // create temp node

	for(target = head->next; target; target = target->next)
	{// loop for whole products list
		if(target == head)
			break;
		if(target->no == productNo) // condition check
			return target;
	}

	return NULL;
}

Product_pointer _p_findNodeByNo(int productNo)
{//find product by product no
	Product_pointer target; // create temp node

	for (target = product->next; target; target = target->next) 
	{// loop for whole products list
		if(target == product)
			break;
		if (target->no == productNo) // condition check
			return target;
	}
	return NULL;
}

Product_pointer _p_findNodeByName(char* productName)
{//find product by product name
	Product_pointer target; // create temp node

	for (target = product->next; target; target = target->next)
	{// loop for whole products list
		if(target == product)
			break;
		if (strcmp(target->name, productName) == 0) // compare strings
			return target;
	}

	return NULL;
}

Product_pointer _p_findNodeByWarehouse(Warehouse_pointer w)
{//find products by product warehouse 
	Product_pointer target; // create temp node
	
	_p_Init_Search();

	for (target = product->next; target; target = target->next)
	{
		if(target == product)
			break;
		if (target->location == w)
			_p_InsertTargetNode(p_searchResults, target); // add products to list
	}

	return p_searchResults;
}

Product_pointer _p_inputNode(Product_pointer target, bool right)
{//input node itmes and insert to list 
	Product_pointer newNode, wNewNode; // create node variable
	Warehouse_pointer w; // create temp warehouse node

	char name[100], manufacture[100]; 
	int no, count, barcode, expiry_date, create_date, in_price, out_price;
	int warehouse_no; // variable for input values
	
	if(warehouse->next == NULL)
	{
		printf("Please create warehouse first!\r\n");
		_w_inputNode(NULL, false);
	}
	
	newNode = (Product_pointer)malloc(sizeof(Product)); // allocate memory
	wNewNode = (Product_pointer)malloc(sizeof(Product)); // allocate memory
	
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
	w = _w_findNodeByNo(warehouse_no); // find warehouse
	if (w == NULL) // warehouse not exists
	{
		printf("Warehouse not found! Insert fail.\r\n\r\n");
		return NULL; // insert fail
	}
	newNode->location = w; // set warehouse pointer
	wNewNode = _p_copyNode(wNewNode, newNode);
	_p_InsertNodeRight(w->products, wNewNode);
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
	target->name = (char*)malloc(sizeof(node->name)); // allocate memory for store strings
	memcpy_s(target->name, sizeof(target->name), node->name, sizeof(node->name)); // copy original string into node
	target->barcode = node->barcode;
	target->count = node->count;
	target->no = node->no;
	target->create_date = node->create_date;
	target->expiry_date = node->expiry_date;
	target->in_price = node->in_price;
	target->location = node->location;
	target->manufacture = (char*)malloc(sizeof(node->manufacture)); // allocate memory for store strings
	memcpy_s(target->manufacture, sizeof(target->manufacture), node->manufacture, sizeof(node->manufacture)); // copy original string into node
	target->out_price = node->out_price;
	target->prev = NULL;
	target->next = NULL;
	return target;
}

Product_pointer _p_joinNode(Product_pointer One, Product_pointer Two)	// 제품 정보 리스트 두 개를 연결시키는 함수
{
	Product_pointer temp1;	// 앞쪽 리스트의 처음을 가리키는 임시적인 포인터
	Product_pointer temp2;	// 뒤쪽 리스트의 처음을 가리키는 임시적인 포인터
	if(!One)	// 앞쪽 리스트가 제대로 된 리스트가 아닐 경우 뒤쪽 리스트 포인터를 반환
		return Two;
	else
	{
		for(temp1 = One ; temp1 ; temp1 = temp1->next)	// 더블 원형 링크드 리스트(앞쪽)에서 끝부분에 다다르기 위한 반복문    
		{
			if(temp1->next->no == One->no)	// 한바퀴를 돌아서 다시 원래자리로 올 경우 값이 같게 되는데 이 경우 탈출
				break;
		}

		temp1->next = Two->next;	// 앞쪽 리스트의 맨끝은 뒤쪽 리스트의 맨앞 다음을 가리킴 --> Two의 더미 헤드 제거
		Two->next->prev = temp1;	// 뒤쪽 리스트의 맨앞 다음의 이전 노드는 앞쪽 리스트의 맨뒤를 가리킴  --> Two의 더미 헤드 제거

		for(temp2 = Two ; temp2 ; temp2 = temp2->next)	// 더블 원형 링크드 리스트(뒤쪽)에서 끝부분에 다다르기 위한 반복문 
		{
			if(temp2->next->no == Two->no)	// 한바퀴를 돌아서 다시 원래자리로 올 경우 값이 같게 되는데 이 경우 탈출
				break;
		}
				
		temp2->next = One;	// 뒤쪽 리스트의 맨끝은 앞쪽 리스트의 맨앞을 가리킴
		One->prev = temp2->prev->next;		// 앞쪽 리스트의 맨앞은 뒤쪽 리스트의 맨뒤의 앞으로 가는 링크를 가리킴  --> Two의 더미 헤드 제거
	}
	return One;
}

int _p_countNodes()
{ // couting nodes
	Product_pointer target; // createing temp node
	int count = 0; // counter

	for (target = product->next; target; target = target->next)
	{ //loop for end of the list
		if(target == product)
			break;
		count++;
	}

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
		if(node == warehouse)
			break;
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

	if(rightNode != warehouse) // if target has right node
		rightNode->prev = newNode; // link node

	return newNode;
}

Warehouse_pointer _w_InsertNodeLeft(Warehouse_pointer target, Warehouse_pointer node)
{
	Warehouse_pointer leftNode; // create temp node

	leftNode = target->prev; // get left node of target
	if(leftNode != warehouse) // left node exists
		return _w_InsertNodeRight(leftNode, node); // insert node
	return NULL; // cannot insert left node if target's prev is head (may losing head)
}

Warehouse_pointer _w_InsertNode(Warehouse_pointer node)
{// insert node to last of the warehouse list

	return _w_InsertNodeRight(warehouse->prev->next, node); // insert to last of list
}

bool _w_deleteNode(Warehouse_pointer target)
{
	Warehouse_pointer prev,next; //create save node variables
	Warehouse_pointer other = NULL;
	Product_pointer p = NULL;
	int other_warehouse;
	

	if(target == NULL || target == warehouse) // if HEAD or target is null
		return false; // cannot delete node

	if(_w_countNodes() < 2)
	{
		printf("You should have one or more warehouses. Operation aborted.\r\n");
		return false;
	}

	if(target->products->next != target->products)
	{
		printf("You should move this warehouse's product to other warehouse\r\n");
		while(other == NULL)
		{
			printf("Please enter the target warehouse's No:");
			scanf_s("%d", &other_warehouse, sizeof(other_warehouse));
			other = _w_findNodeByNo(other_warehouse);
			if(other == NULL)
				printf("Invalid Warehouse No\r\n");
		}
		_p_joinNode(other->products, target->products);

		for(p = product->next; p; p = p->next)
		{
			if(p == product)
				break;
			p->location = other;
		}
	}

	target->prev->next = target->next;
	target->next->prev = target->prev;
	target->next = target;
	target->prev = target;

	free(target); // deallocate memory

	return true;
}

Warehouse_pointer _w_findNodeByNo(int houseNo)
{//find warehouse node using warehouse no
	Warehouse_pointer target; // create temp node

	for (target = warehouse->next; target; target = target->next) // loop for list
	{
		if(target == warehouse)
			break;

		if (target->no == houseNo) // condition
			return target;
	}

	return NULL;
}

Warehouse_pointer _w_findNodeByName(char* houseName)
{//find warehouse node using house name
	Warehouse_pointer target; // create temp node

	for (target = warehouse->next; target; target = target->next) // loop for list
	{
		if(target == warehouse)
			break;

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
	memcpy_s(newNode->name, sizeof(newNode->name) * 100, name, sizeof(name)); // cppy input string into node
	fflush(stdin);
	printf("Warehouse Location : ");
	scanf_s("%s", &location, sizeof(location));
	newNode->location = (char*)malloc(sizeof(char) * 100); // allocate memory for store string
	memcpy_s(newNode->location, sizeof(newNode->location) * 100, location, sizeof(location)); // copy input string into node
	newNode->products = (Product_pointer)malloc(sizeof(Product));
	newNode->products->next = newNode->products;
	newNode->products->prev = newNode->products;
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

Warehouse_pointer _w_copyNode(Warehouse_pointer target, Warehouse_pointer node) 
{// copy warehouse node
	target->no = node->no;
	memcpy_s(target->name, sizeof(target->name), node->name, sizeof(node->name)); // allocate memory for store strings
	target->name = (char*)malloc(sizeof(node->name)); // copy original string into target node
	memcpy_s(target->location, sizeof(target->location), node->location, sizeof(node->location)); // allocate memory for store strings
	target->location = (char*)malloc(sizeof(node->location)); // copy original string into target node
    target->prev = NULL;
    target->next = NULL;
    return target;
}

Warehouse_pointer _w_joinNode(Warehouse_pointer One, Warehouse_pointer Two)	// 창고 정보 리스트 두 개를 연결시키는 함수
{
	Warehouse_pointer temp1;	// 앞쪽 리스트의 처음을 가리키는 임시적인 포인터
	Warehouse_pointer temp2;	// 뒤쪽 리스트의 처음을 가리키는 임시적인 포인터
	if(!One)	// 앞쪽 리스트가 제대로 된 리스트가 아닐 경우 뒤쪽 리스트 포인터를 반환
		return Two;
	else
	{
		for(temp1 = One ; temp1 ; temp1 = temp1->next)	// 더블 원형 링크드 리스트(앞쪽)에서 끝부분에 다다르기 위한 반복문
		{
			if(temp1->next->no == One->no)	// 한바퀴를 돌아서 다시 원래자리로 올 경우 값이 같게 되는데 이 경우 탈출
				break;
		}

		temp1->next = Two->next;	// 앞쪽 리스트의 맨끝은 뒤쪽 리스트의 맨앞을 가리킴 
		Two->next->prev = temp1;	// 뒤쪽 리스트의 맨앞은 앞쪽 리스트의 맨뒤를 가리킴

		for(temp2 = Two ; temp2 ; temp2 = temp2->next)	// 더블 원형 링크드 리스트(뒤쪽)에서 끝부분에 다다르기 위한 반복문
		{
			if(temp2->next->no == Two->no)	// 한바퀴를 돌아서 다시 원래자리로 올 경우 값이 같게 되는데 이 경우 탈출
				break;
		}
				
		temp2->next = One;	// 뒤쪽 리스트의 맨끝은 앞쪽 리스트의 맨앞을 가리킴
		One->prev = temp2->prev->next;		// 앞쪽 리스트의 맨앞은 뒤쪽 리스트의 맨뒤의 앞으로 가는 링크를 가리킴  --> Two의 더미 헤드 제거
	}
	return One;
}

int _w_countNodes()
{// counting nodes
	Warehouse_pointer target; // create temp node
	int count = 0; // counter

	for (target = warehouse->next; target; target = target->next)
	{ // loop for lists
		if(target == warehouse)
			break;
		count++; 
	}
	
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
				w_temp = _w_findNodeByNo(key);
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
				p_temp = _p_findNodeByNo(key);
				if(p_temp == NULL)
				{
					printf("Cannot find Product No #%d\r\n",key);
					break;
				}
				if(_p_deleteNode(p_temp, false))
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
				w_temp = _w_findNodeByNo(key);
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
				w_temp = _w_findNodeByName(keyword);
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
				p_temp = _p_findNodeByNo(key);
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
				p_temp = _p_findNodeByName(keyword);
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
				w_temp = _w_findNodeByNo(key);
				if(w_temp == NULL)
				{
					printf("Cannot find warehouse #%d\r\n", key);
					break;
				}
				p_temp = _p_findNodeByWarehouse(w_temp);
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