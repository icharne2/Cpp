#include<iostream>
#include<cstdlib>

using namespace std;

//Tree functions
struct Tree {
	char value;
	Tree* left;
	Tree* right;
	Tree* parent;
};

//List functions
struct List {
	int value;
	List* next;
	List* preview;
	Tree* treeValue;
};

//Print tree
void inorder(Tree* root) {
	if (root) {    
		inorder(root->left);
		cout << root->value << " ";
		inorder(root->right);
	}
}

//Add elements to list 
void AddToEnd(List*& Head, int x, char treeChar = '\0', Tree* left = nullptr, Tree* right = nullptr) {
	List* Element = new List;
	Element->value = x;
	Element->next = nullptr;
	Element->treeValue = new Tree;
	Element->treeValue->value = treeChar;

	if (left || right ) {	//if p1, p2 elements exist
		// Copy p1 element - left site
		Element->treeValue->left = new Tree;
		Element->treeValue->left->value = left->value;
		Element->treeValue->left->left = left->left;
		Element->treeValue->left->right = left->right;

		// Copy p2 element - left site
		Element->treeValue->right = new Tree;
		Element->treeValue->right->value = right->value;
		Element->treeValue->right->left = right->left;
		Element->treeValue->right->right = right->right;
	}
	else {	//if p1,p2 doesn't exist
		Element->treeValue->left = left;
		Element->treeValue->right = right;
	}
	
	if (!Head) {
		Element->preview = nullptr;
		Head = Element;
		Element->treeValue->parent = nullptr;
		Element->treeValue->parent = nullptr;
	}
	else {
		List* pom = Head;
		while (pom->next) {
			pom = pom->next;
		}
		Element->preview = pom;
		pom->next = Element;
		Element->treeValue->parent = pom->treeValue;
	}
}

//Print our list
void printList(List*& Head) {	
	if (Head) {
		List* pom = Head;	
		while (pom) {
			cout << pom->value << ": " << char(pom->treeValue->value) << endl;
			pom = pom->next;
		}
	}
}

//Delete list element
void Remove(List*& Head, int x) {
	if (Head) {	
		List* pom = Head; 
		List* prev = nullptr;	

		while (pom && pom->value != x) {
			prev = pom;
			pom = pom->next;
		}
		//pom -> element to delete
		if (pom) {  
			if (prev) {
				prev->next = pom->next;
				pom->next->preview = prev;
			}
			else {
				Head = pom->next;
			}

			//Delete Tree
			if (pom->treeValue) {
				delete pom->treeValue;
			}

			delete pom;
		}
	}
}

// Huffman Algorithm
void huffnamAlgorithm(List*& Head) {
	while (Head && Head->next) {
		List* p1 = Head;
		List* p2 = Head->next;
		List* tmp = Head->next;

		// Find two minimum elements
		while (tmp) {
			if (tmp->value < p1->value) {
				p2 = p1;
				p1 = tmp;
			}
			else if (tmp->value < p2->value) {
				p2 = tmp;
			}
			tmp = tmp->next;
		}

		// Add new list element p1 + p2
		// New list element
		AddToEnd(Head, (p1->value + p2->value), '\0', p1->treeValue, p2->treeValue);

		// Delete p1, p2
		Remove(Head, p1->value);
		Remove(Head, p2->value);
	}
}


int main() {
	//Huffman Algorithm
	//Create a list with number of elements and tree chars
	List* head = nullptr;

	AddToEnd(head, 92, 'A');
	AddToEnd(head, 53, 'D');
	AddToEnd(head, 3, 'E');
	AddToEnd(head, 28, 'F');
	AddToEnd(head, 3, 'G');
	AddToEnd(head, 58, 'S');
	AddToEnd(head, 1, 'W');
	AddToEnd(head, 2, 'X');
	
	//Check list
	cout << "List before Huffman Algorithm:" << endl;
	printList(head);

	huffnamAlgorithm(head);

	cout << "List after Huffman Algorithm:" << endl;
	printList(head);

	//Print Huffman Tree
	cout << "Huffman Tree" << endl;
	inorder(head->treeValue);


	system("PAUSE");
	return 0;
}
