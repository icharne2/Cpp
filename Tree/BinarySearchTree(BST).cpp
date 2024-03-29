#include<iostream>
#include<cstdlib>

using namespace std;

struct BinaryTree {
	int key;	//wartosc wez³a
	BinaryTree* parent, * left, * right;
};

//Funkcja dodaj¹ca do drzewa
void AddToTree(BinaryTree*& root, int value, BinaryTree* parent = NULL) {
	if (!root) {	//Je¿eli korzeñ drzewa nie istnieje
		BinaryTree* tmp = new BinaryTree;
		tmp->key = value;
		tmp->parent = parent;
		tmp->left = tmp->right = nullptr;	//Inne elementy nie istniej¹
		root = tmp;
	}
	else {		//Je¿eli drzewo nie jest puste
		if (value >= root->key) {	//Dodanie do prawej strony drzewa
			AddToTree(root->right, value, root);
		}
		else {		//Dodanie do lewej strony drzewa
			AddToTree(root->left, value, root);
		}
	}
}

//Funkcja wypusujaca inorder --> lewe poddrzewo, korzen, prawe poddrzewo
void inorder(BinaryTree* root) {
	if (root) {    // Je¿eli istnieje
		inorder(root->left);	//Wywolanie funkcji dla lewego wezla 
		cout << root->key << endl;	//Wypisanie obecnego elementu
		inorder(root->right);	//Wypowalanie funkcji dla prawego poddrzewa
	}
}

//Funkcja znajduj¹ca miniumum w drzewie
BinaryTree* minimum(BinaryTree* root) {
	while (root && root->left) {	//Poniewaz element minimalny to element maksymalnie na lewo
		root = root->left;
	}

	return root;
}

//Funkcja znajduj¹ca maksimum w drzewie
BinaryTree* maximum(BinaryTree* root) {
	while (root && root->right) {	//Poniewaz element maksymalny to element maksymalnie na prawo
		root = root->right;
	}

	return root;
}

//Funkcja szukajaca elementu w drzewie - rekurencyjnie
BinaryTree* findElement(BinaryTree* root, int value) {
	if (root) {	//Jezeli istanieje korzen drzewa
		if (value < root->key) {	//Jezeli element szukanay jest mniejszy 
			return findElement(root->left, value);		//zwracany element jest po lewej stronie
		}
		else if(value > root->key) {
			return findElement(root->right, value);		//zwracany element jest po prawej stronie
		}
		else {	//Sutacja, gdy root == value
			return root;
		}

	}
	else return nullptr;
}

//Funkcja szukaj¹ca poprzednika
BinaryTree* findPredecessor(BinaryTree* node) {
	if (node) {
		if (node->left) {	//Jezeli wezel posiada lewego potomka
			return maximum(node->left); //o poprzednikiem wêz³a bêdzie element o najwiêkszym kluczu w lewym poddrzewie BST wêz³a
		}
		else {	//Jeœli wêze³ nie posiada lewego potomka
			//to poprzednikiem wêz³a bêdzie pierwszy rodzic, dla którego wêze³ le¿y w prawym poddrzewie.
			BinaryTree* parent = node->parent;

			while (parent && node == parent->left) {	//Dopóki mo¿emy isc po lewych elementach 
				node = parent;
				parent = parent->parent;
			}

			return parent;
		}
	}
	else return nullptr;	//Je¿eli dany wezel nie istnieje to nie ma poprzednika
}

//Funkcja szukaj¹ca nastêpnika
BinaryTree* findSuccessor(BinaryTree* node) {
	if (node) {
		if (node->right) {	// jeœli wêze³ posiada prawego potomka
			//to nastêpnikiem jest wêze³ minimalny w prawym poddrzewie BST wêz³a
			return minimum(node->right);
		}else {		//jeœli wêze³ nie posiada prawego potomka
			//to nastêpnikiem bêdzie pierwszy rodzic, dla którego wêze³ le¿y w lewym poddrzewie.
			BinaryTree* parent = node->parent;

			while (parent && node == parent->right) {	//Dopóki mo¿emy isc po prawych elementach 
				node = parent;
				parent = parent->parent;
			}
			return parent;
		}

	}
	else return nullptr;	//Je¿eli dany wezel nie istnieje to nie ma nastepnika
}



int main() {
	BinaryTree* root = nullptr;	//Utworzenie wskaŸnika na korzeñ drzewa

	//Dodanie pare wartosci do drzewa BST
	AddToTree(root, 20);
	AddToTree(root, 10);
	AddToTree(root, 15);
	AddToTree(root, 25);
	AddToTree(root, 30);

	//Wypisanie INORDER
	inorder(root);

	//Minimum w drzewie
	cout << "Minimum element: " << minimum(root)->key << endl;

	//Maksimum w dzrewie
	cout << "Maximum element: " << maximum(root)->key << endl;

	//Szukanie elementu w dzewie BST
	int elementValue;
	cout << "Enter the value you want to find." << endl;
	cin >> elementValue;

	if (findElement(root, elementValue)) {
		cout << "Found: " << findElement(root, elementValue)->key << endl;
	}else {
		cout << "Element not found." << endl;
	}
	
	//Poprzednik podanego elementu
	BinaryTree* predecessor = findPredecessor(findElement(root, 20));

	if (predecessor) {
		cout << "Predecessor: " << predecessor->key << endl;
	}
	else {
		cout << "Predecessor not found." << endl;
	}

	//Nastepnik podanego elementu
	BinaryTree* Successor = findSuccessor(findElement(root, 20));

	if (Successor) {
		cout << "Successor: " << Successor->key << endl;
	}
	else {
		cout << "Successor not found." << endl;
	}

	system("PAUSE");
	return 0;
}