// SplayTreeProba2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include <iostream>

using namespace std;

struct node{
	int value;
	node *l, *r;
};


node* newNode(int number){
	node* temp = new node;
	temp->value = number;
	temp->l = temp->r = NULL;
	return temp;
}

node *Zag(node *root)
{
	node *temp = root->l;
	root->l = temp->r;
	temp->r = root;
	return temp;
}

node *Zig(node *root){
	node *temp = root->r;
	root->r = temp->l;
	temp->l = root;
	return temp;
}

node *Splay(node *root, int number){
	if (root == NULL || root->value == number)
		return root;
	if (root->value > number){
		if (root->l == NULL)
			return root;
		if (root->l->value > number){
			root->l->l = Splay(root->l->l, number);
			root = Zag(root);
		}
		else if (root->l->value < number){ // Zig-Zag (Left Right)
			// First recursively bring the key as root of left-right
			root->l->r = Splay(root->l->r, number);
			// Do first rotation for root->left
			if (root->l->r != NULL)
				root->l = Zig(root->l);
		}
		// Do second rotation for root
		return (root->l == NULL) ? root : Zag(root);
	}
	else {
		if (root->r == NULL)
			return root;
		if (root->r->value > number){
			root->r->l = Splay(root->r->l, number);
			if (root->r->l != NULL)
				root->r = Zag(root->r);
		}
		else if (root->r->value < number){
			root->r->r = Splay(root->r->r, number);
			root = Zig(root);
		}
		return (root->r == NULL) ? root : Zig(root);
	}
}

node *Search(node *root, int number)
{
	return Splay(root, number);
}

void Show(node *root)
{
	if (root != NULL){
		cout << root->value << " ";
		Show(root->l);
		Show(root->r);
	}
}

node *Insert(node *root, int number){
	if (root == NULL) 
		return newNode(number);
	root = Splay(root, number);
	if (root->value == number)
		return root;
	node *newnode = newNode(number);
	if (root->value > number){
		newnode->r = root;
		newnode->l = root->l;
		root->l = NULL;
	}
	else{
		newnode->l = root;
		newnode->r = root->r;
		root->r = NULL;
	}
	return newnode; 
}

node *Delete(node *root, int number){
	node *temp;
	if (root == NULL)
		return NULL;
	root = Splay(root, number);
	if (number != root->value)
		return root;
	if (root->l == NULL){
		temp = root;
		root = root->r;
	}
	else{
		temp = root;
		root = Splay(root->r, number);
		root->r = temp->r;
	}
	delete(temp);
	return root;

}


int main()
{
	struct node *root = newNode(10);

	root = Insert(root, 16);
	root = Insert(root, 21);
	root = Insert(root, 5);
	root = Insert(root, 30);
	root = Insert(root, 28);

	root = Search(root, 20);
	cout << "The Splay tree is " << endl;
	Show(root);
	cout << endl;

	int key = 5;
	root = Delete(root, key);
	cout << "The modified Splay tree after removing an element with a value 4 is " << endl;
	Show(root);
	cout << endl;

	root = Insert(root, 25);
	cout << "The modified Splay tree after inserting an element with a value 25 is " << endl;
	Show(root);
	cout << endl;

	system("pause");
	return 0;
}