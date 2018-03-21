#include "operations.h"

// create a list and return the pointer to it.
product * create()
{
	return makeNode();
}

// make a node and return a pointer to the node
// return a NULL pointer if failed.
product * makeNode()
{
	product * tmp = (product *) malloc(sizeof(product));
	if (tmp == NULL)
	{
		puts("\nInMakeNode: Memory allocation failed\n");
		return NULL;
	}
	fflush(stdin);
	printf("Please input product's name: ");
	scanf("%s", tmp->name);
	fflush(stdin);
	printf("Please input the qauntity of the product: ");
	scanf("%f", &(tmp->quantity_value));
	fflush(stdin);
	printf("Please input the product's quantity unit: ");
	scanf("%s", tmp->quantity_unit);
	fflush(stdin);
	printf("Please input the price: ");
	scanf("%f", &(tmp->price_value));
	fflush(stdin);
	printf("Please input the product's price unit: ");
	scanf("%s", tmp->price_unit);
	fflush(stdin);

	tmp->next = NULL;

	return tmp;
}

//creates node out of information given
product * buildNode(char fname[], float quantityValue, char quantityUnit[], float priceValue, char priceUnit[])
{
	product * p = (product *) malloc(sizeof(product));
	if(p == NULL) {
		puts("\nInBuildNode: Memory Allocation Failed!\n");
		return NULL;
	}
	strcpy(p->name, fname);
	p->quantity_value = quantityValue;
	strcpy(p->quantity_unit, quantityUnit);
	p->price_value = priceValue;
	strcpy(p->price_unit, priceUnit);
	return p;
}

// insert a node to the list
int insert(product **l, product *node){

	product * temp = findItem(*l, node->name);

	//if the product already exists,  will update quantity
	if (temp != NULL){
		temp->quantity_value = node->quantity_value + temp->quantity_value;
		printf("\n--------------------------------------------------\n");
		printf("Product already exists, updated quantity\n");
		printf("%s now has %f %s\n", node->name, node->quantity_value, node->quantity_unit);
		printf("-----------------------------------------------------\n\n");
		return 1;
	}

	//creates new node in the list
	else{
		node->next = *l;
		*l = node;
		return 0;
	}

}

// remove a node from list
void rmItem(product ** l, char name[]){

	product * current = *l;
	product * previous = current;

	//if the list is empty
	if(current == NULL){

		printf("\n-------------------------------\n");
		printf("The item was not found\n");
		printf("----------------------------------\n\n");
		return;
	}

	else {
		while(current != NULL) {

			//if the item was found in the list
			if (strcmp(current->name, name) == 0) {
				if(previous == current){
					*l = (current->next);
				}
				else{
					previous->next = current->next;
				}

				free (current);
				printf("\n*********************************\n");
				printf("The item was removed\n");
				printf("***********************************\n");
				return;
			}

			//if it wasn't found, will move to next node
			previous = current;
			current = current->next;
		}
	}
}

// show list
void showList(product * l){

	//if the node isn't empty
	if (l != NULL){

		printf("---------------------------------\n\n");
		printf("Product: %s", l->name);
		printf("\nQuantity Value: %f", l->quantity_value);
		printf("\nQuantity Unit: %s", l->quantity_unit);
		printf("\nPrice Value: %f", l->price_value);
		printf("\nPrice unit: %s\n", l->price_unit);
		printf("----------------------------------\n\n");

		//recursive call for the next node
		showList(&(*l->next));
		
	}

	else{
		printf("\nEnd of the inventory list\n\n");
	}

}

// load data from file inf
product * loadData(char inf[], product *l){

	char fname[N], quantityUnit[N], priceUnit[N];
	int id, rt;
	product * head = l;
	float quantityValue, priceValue;

	FILE * fin = fopen(inf, "r");
	if(fin == NULL) {
		printf("\nInLoad: File open failed (%s)\n", inf);
		return NULL;
	}

	while (1) {
		rt = fscanf(fin, "%s %f %s %f %s\n", fname, &quantityValue, quantityUnit, &priceValue, priceUnit);
		if (rt < 5)
			break;
		if (head == NULL)
			head = buildNode(fname, quantityValue, quantityUnit, priceValue, priceUnit);
		else
			insert(&head, buildNode(fname, quantityValue, quantityUnit, priceValue, priceUnit));
	}
	fclose(fin);
	return head;
}

// save data to file outf
int saveData(char outf[], product *l){

	FILE * fout = fopen(outf, "w");
	product * cursor = l;

	while (cursor != NULL){
		fprintf(fout, "%s %f %s %f %s\n", cursor->name, cursor->quantity_value, cursor->quantity_unit, cursor->price_value, cursor->price_unit);
		if (cursor->next != NULL){
			cursor = cursor->next;
		}
		else{
			cursor = NULL;
		}
	}

	fclose(fout);
	return 1;

}

// sell product product of quantity q
float purchase(product *l, char name[], float q){

	//first locate the product in the list
	product * node = findItem(l, name);
	float total = 0.0;

	//if the item is found
	if (node != NULL){

		//making sure the quantity needed is available
		if(node->quantity_value >= q){

			printf("q: %f\n", q);

			
			node->quantity_value = node->quantity_value - q;
			total = q * node->price_value;
			return total;
		}

		else {
			printf("\n-------------------------------\n");
			printf("There are not enough left!\n");
			printf("---------------------------------\n\n");
			return 0.0;
		}
	}

	//if the product wasn't found in the lsit
	else {
		printf("\n--------------------------\n");
		printf("Product was not found\n");
		printf("-----------------------------\n\n");
		return 0.0;
	}
}

// check out price of product p from list l
void check_price(product *l, char p[]){

	product * node = findItem(l,p);
	if (node != NULL){
		printf("\n===========================================\n");
		printf("%s costs %f %s.\n", p, node->price_value, node->price_unit);
		printf("\n===========================================\n");
	}

	else {
		printf("\n******************************************\n");
		printf("The item %s was not found\n", p);
		printf("******************************************\n\n");
	}
}

// find a product p from list l
product * findItem(product *l, char p[]){

	//reached end of list, so product isn't found
	if(l == NULL){
		return NULL;
	}

	//product was located
	else if (strcmp(l->name, p) == 0){
		return l;
	}

	//recursive call to move through the list
	else {
		return findItem(l->next, p);
	}
}

//shows the menu to the user
void displayMenu(){
	printf("\n==========================================================================\n");
	printf("Welcome to Kehlsey's Grocery Store\n");
	printf("Please let me know what you what you want to do by typing one of the numbers\n");
	printf("============================================================================\n");
	printf("0: Add product to store                  1: Purchase a product from the store\n");
	printf("2: Check price of a product              3: Show products in store\n");
	printf("4: Remove a product from a store         5: Find product\n");
	printf("6: Inventory and Sales                   7: Load a file\n");
	printf("8: Save and exit\n\n");

}

// the job starts here, start with loading data from
// the file data, and perform the functions by calling
// related functions. Ends at saving data to the file data.
int doIt(){

	product* list = NULL;
	product * node;
	char input[N], name[N];
	float quantity, price;
	float total = 0.0;
	int done = 0;
	int choice;
	float num = 0.0;
	float checkout;

	while (!done) {
		displayMenu();
		puts("What do you want to do?\n");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);

		switch (choice)
		{
			//insert product
			case 0:
			insert(&list, makeNode());
			break;

			//purchase product
			case 1:
			checkout = 0.0;

			printf("\nEnter item name: ");
			scanf("%s", input);
			strcpy(name, input);
			fflush(stdin);
			printf("\nEnter quantity: ");
			scanf("%f", &num);
			fflush(stdin);
			
			checkout = purchase(&(*list), name, num);
			total = total + checkout; 

			printf("\n-----------------------------------------\n");
			printf("Your total is: %f. Thank you!\n", checkout);
			printf("--------------------------------------------\n\n");
			break;

			//check price of product
			case 2:
			printf("\nEnter product name: ");
			scanf("%s", input);
			strcpy(name, input);
			fflush(stdin);
			check_price(&(*list), name);
			break;

			//shows inventory
			case 3:
			printf("\n**********************\n");
			showList(&(*list));
			printf("\n**********************\n\n");
			break;

			//remove a product from inventory
			case 4:
			fflush(stdin);
			printf("Input the product you want to delete: \n");
			fflush(stdin);
			scanf("%s", &name);
			fflush(stdin);
			rmItem(&list, name);
			break;

			//search for an item
			case 5:
			printf("\nEnter item name: ");
			scanf("%s", input);
			product * item = findItem(&(*list), input);
			fflush(stdin);

			if (item == NULL){
				printf("---------------------------\n");
				printf("Item was not found\n");
				printf("---------------------------\n\n");
			}
			else {
				printf("====================================\n");
				printf("Here is what was found: \n");
				printf("====================================\n");
				printf("Product: %s", item->name);
				printf("\n> Quantity Value: %f", item->quantity_value);
				printf("\n> Quantity Unit: %s", item->quantity_unit);
				printf("\n> Price Value: %f", item->price_value);
				printf("\n> Price unit: %s\n\n", item->price_unit);
			}
			break;

			//view sales and inventory
			case 6:
			printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			printf("\nThe total sales today are: %f\n", total);
			printf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			showList(&(*list));
			break;

			//load a file
			case 7:
			printf("\nEnter a file name to load: \n");
			scanf("%s",input);
			list = loadData(input,list);
			fflush(stdin);
			break;

			//exit and save
			case 8:
			printf("\nPlease enter a filename to save: ");
			scanf("%s", input);
			saveData(input,&(*list));
			fflush(stdin);
			printf("\n========================================\n");
			printf("Save successful, Have a good day!\n\n\n");
			done = 1;

			break;

			//if wrong input
			default:
			printf("\nWrong number. Please try again and enter a number 0-8.\n\n");
			break;
		}
	}

}