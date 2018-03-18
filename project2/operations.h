#ifndef OPERATIONS_H
#define OPERATIONS_H

//#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/stat.h>
//#include <math.h>

#define N 20
struct product
{
char name[N];
float quantity_value;
char quantity_unit[N];
float price_value;
char price_unit[N];
struct product *next;
}; typedef struct product product;


// insert a node to the list
int insert(product **l, product *node);

// remove a node from list
void rmItem(product **l, char name[]);

// show list
void showList(product * l);

// load data from file inf
product * loadData(char inf[], product *l);

// save data to file outf
int saveData(char outf[], product *l);

// sell product product of quantity q
float purchase(product *l, char product[], float q);

// check out price of product p from list l
void check_price(product *l, char p[]);

// find a product p from list l
struct product * findItem(product *l, char p[]);

//shows the inventory list
void displayMenu();

// create a list and return the pointer to it.
product * create();

// make a node and return a pointer to the node
// return a NULL pointer if failed.
product * makeNode();


product * buildNode(char fname[], float quantityValue, char quantityUnit[], float priceValue, char priceUnit[]);

// the job starts here, start with loading data from
// the file data, and perform the functions by calling
// related functions. Ends at saving data to the file data.
int doIt();

#endif