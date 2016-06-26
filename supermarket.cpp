/* Created by br8th on 26/06/2016 */
/* Program that allows entry of items, gives total costs
 * & change using a list */
#include <iostream>

using namespace std;

struct item {
	int id;
	double price;
	string name;
	item *next;
};

typedef struct item* ItemPtr;
ItemPtr head = nullptr;

/* function prototypes */
void instructions(void);
void insert(void);
void search (void);
void update (void);
void printStock(void);
int getSize(void);
int hasItem(void);
ItemPtr findItem (int id);

int main (void) {
	int itemId, quantity;
	double total = 0;

	for (;;){
		int choice;
		instructions();
		cout << "? ";
		cin >> choice;
		switch (choice) {
			case 1:
				insert();
				break;
			case 2:
				printStock();
				break;
			case 3: {
				if (hasItem()) {
					cout << "Enter item id: ";
					cin >> itemId;
					ItemPtr i = findItem(itemId);
					if ( i != nullptr) {
						cout << "Quantity: ";
						cin >> quantity;
						total += i->price * quantity;
					} else {
						cout << "Invalid item id\n\n";
					}
				} else {
					cout << "No items in stock" << endl;
				}
				break;
			}
			case 4:
				if (total != 0) {
					double cash;
					cout << "Your total is: " << total << endl;
					cout << "Cash: ";
					cin >> cash;
					if (cash < total) {
						cout << "Pay up!" <<  total - cash << endl;
						return 0;
					} else if (cash == total) {
						cout << "Thank you for shopping with us" << endl;
						return 0;
					} else if (cash > total) {
						cout << "Your change: " << cash - total << endl;
						return 0;
					}
				} else {
					cout << "Shop first, smh" << endl;
				}
				break;
			case 5:
				cout << "Goodbye!" << endl;
				return 0;
			default:
				cout << "Invalid choice. Try again: ";
				break;
		}
	}
	return 0;
}

void instructions(void) {
	cout << "1.Stock\n";
	cout << "2.Show Stock\n";
	cout << "3.Shop\n";
	cout << "4.Pay\n";
	cout << "5.Exit\n";
}

void insert(void) {
	ItemPtr new_node  = new item;
	ItemPtr curr, prev;

	cout << "Enter item id: ";
	cin >> new_node->id;

	/* check if id already exists */
	for (curr = head, prev = nullptr;
		curr != nullptr && curr->id != new_node->id;
		  prev = curr, curr = curr->next)
		;

	/* found item */
	if (curr != nullptr && curr->id == new_node-> id) {
		cout << "Item already exists" << endl;
		delete new_node;
		return;
	}

	cout << "Enter item name: ";
	cin >> new_node->name;

	cout << "Enter item price: ";
	cin >> new_node->price;

	/* add node as ...*/
	new_node->next = curr;
	if (prev == nullptr)
		head = new_node; /* ... first item on list */
	else
		prev->next = new_node; /*...other items on list */
}

ItemPtr findItem (int id) {
	ItemPtr p;

	for(p = head;
		p != nullptr && p->id != id;
			p = p->next)
        	;
	if (p != nullptr && p->id == id)
		return p;
	return nullptr;
}

void search (void) {
	int number;
	cout << "Enter item number: ";
	cin >> number;
	ItemPtr i = findItem(number);
	if (i != nullptr) {
		cout << "Item Name:"<<  i->name << endl;
		cout << "Item Price:"<<  i->price << endl;
	} else {
		cout << "Item not found";
	}
}

void update (void) {
	int number;
	double price;
	string name;

	cout << "Enter item number: ";
	cin >> number;
	ItemPtr i = findItem(number);
	if (i != nullptr) {
		cout << "Enter new item name: ";
		cin >> name;
		i->name = name;
		cout << "Enter new item price: ";
		cin >> price;
		i->price = price;
	} else {
		cout << "item not found!" << endl;
	}
}

void printStock (void) {
	if (head == nullptr) {
		cout << "Sorry, no items in stock" << endl;
		return;
	}

	cout << "Id\t\tName\t\tPrice" << endl;
	for (ItemPtr i = head; i != nullptr; i = i->next)
		cout << i-> id << "\t\t"
		<< i->name << "\t\t"
		<< i->price << "\t\t"<< endl;

}

/* the number of items in the list */
int getSize() {
	int i = 0;
	ItemPtr p = head;

	for (;p != nullptr; p = p->next, i++)
		;
	return i;
}

int hasItem() {
	return (head != nullptr);
}
