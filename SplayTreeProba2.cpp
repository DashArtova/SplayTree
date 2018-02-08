// SplayTreeProba2.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>

using namespace std;

struct node{
	int value;
	node *l, *r;
};


node* newNode(int number){
	auto temp = new node;
	temp->value = number;
	temp->l = temp->r = nullptr;
	return temp;
}
//Лівий поворот
node *Zag(node *root)
{
	node *temp = root->l;
	root->l = temp->r;
	temp->r = root;
	return temp;
}
//Правий поворот
node *Zig(node *root){
	node *temp = root->r;
	root->r = temp->l;
	temp->l = root;
	return temp;
}

node *Splay(node *root, int number){
	if (root == nullptr || root->value == number)
		return root;
	if (root->value > number){
		if (root->l == nullptr)
			return root;
		if (root->l->value > number){
			root->l->l = Splay(root->l->l, number);
			root = Zag(root);
		}
		else if (root->l->value < number){ 
			root->l->r = Splay(root->l->r, number);
			if (root->l->r != nullptr)
				root->l = Zig(root->l);
		}
		if (root->l == nullptr) 
            return root; 
        else return Zag(root);
	}
	else {
		if (root->r == nullptr)
			return root;
		if (root->r->value > number){
			root->r->l = Splay(root->r->l, number);
			if (root->r->l != nullptr)
				root->r = Zag(root->r);
		}
		else if (root->r->value < number){
			root->r->r = Splay(root->r->r, number);
			root = Zig(root);
		}
		if (root->r == nullptr) 
            return root;
        else return Zig(root);
	}
}

node *Search(node *root, int number)
{
	return Splay(root, number);
}

void Show(node *root)
{
	if (root != nullptr){
		cout << root->value << " ";
		Show(root->l);
		Show(root->r);
	}
}

node *Insert(node *root, int number){
	if (root == nullptr) 
		return newNode(number);
	root = Splay(root, number);
	if (root->value == number)
		return root;
	node *newnode = newNode(number);
	if (root->value > number){
		newnode->r = root;
		newnode->l = root->l;
		root->l = nullptr;
	}
	else{
		newnode->l = root;
		newnode->r = root->r;
		root->r = nullptr;
	}
	return newnode; 
}

node *Delete(node *root, int number){
	node *temp;
	if (root == nullptr)
		return root;
	root = Splay(root, number);
	if (number != root->value)
		return root;
	if (root->l == nullptr){
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
	auto root = newNode(10);

	root = Insert(root, 16);
	root = Insert(root, 21);
	root = Insert(root, 5);
	root = Insert(root, 30);
	root = Insert(root, 28);

	root = Search(root, 20);
	cout << "Розширюване дерево: " << endl;
	Show(root);
	cout << endl;

	int key = 5;
	root = Delete(root, key);
	cout << "Розширюване дерево після видалення елемента зі значенням 5: " << endl;
	Show(root);
	cout << endl;

	root = Insert(root, 25);
	cout << "Розширюване дерево після додавання елемента зі значенням 25: " << endl;
	Show(root);
	cout << endl;

	return 0;
}