#include <iostream>

using namespace std;

struct BinaryTree {
    BinaryTree* parent, * left, * right;
    int key;
    int bf;  // Wspó³czynnik równowa¿enia (Balance Factor) - ró¿nica wysokoœci lewego i prawego poddrzewa
};

// Funkcja wypisuj¹ca drzewo w porz¹dku inorder
void inorder(BinaryTree* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " node height:" << root->bf << endl;
        inorder(root->right);
    }
}

// Funkcja do obliczania wysokoœci wêz³a
int height(BinaryTree* node) {
    if (node == nullptr) {
        return 0;
    }
    // Wysokoœæ wêz³a to maksymalna wartoœæ pomiêdzy wysokoœciami lewego i prawego poddrzewa, plus jeden (wêze³ g³ówny)
    return max(height(node->left), height(node->right)) + 1;
}

// Aktualizacja wspó³czynnika równowa¿enia i wysokoœci wêz³a
void updateHeight(BinaryTree* node) {
    if (node) {
        // Obliczanie wspó³czynnika równowa¿enia (Balance Factor)
        node->bf = height(node->left) - height(node->right);
    }
}

// Rotacja w lewo
void rotateLeft(BinaryTree*& x) {
    if (x && x->right) {
        BinaryTree* tmp = x->right;
        BinaryTree* tmp2 = tmp->left;

        // Przeprowadzanie rotacji w lewo
        tmp->left = x;
        x->right = tmp2;

        // Aktualizacja wysokoœci wêz³ów po rotacji
        updateHeight(x);
        updateHeight(tmp);

        x = tmp;  // Aktualizacja korzenia poddrzewa
    }
}

// Rotacja w prawo
void rotateRight(BinaryTree*& x) {
    if (x && x->left) {
        BinaryTree* tmp = x->left;
        BinaryTree* tmp2 = tmp->right;

        // Przeprowadzanie rotacji w prawo
        tmp->right = x;
        x->left = tmp2;

        // Aktualizacja wysokoœci wêz³ów po rotacji
        updateHeight(x);
        updateHeight(tmp);

        x = tmp;  // Aktualizacja korzenia poddrzewa
    }
}

// Balansowanie drzewa AVL po dodaniu wêz³a
void balanceTree(BinaryTree*& root, BinaryTree* node) {
    while (node != nullptr) {
        // Aktualizacja wspó³czynnika równowa¿enia i wysokoœci dla bie¿¹cego wêz³a
        updateHeight(node);

        // Sprawdzenie, czy drzewo jest niezbalansowane
        if (node->bf > 1) {     //Lewa strona drzewa jest wieksza
            if (node->left->bf < 0) {   //Czy lewa strona jest "ciê¿sza"
                // Rotacja lewo-prawo (LR)
                rotateLeft(node->left);
            }
            // Rotacja prawo (RR)
            rotateRight(node);
        }
        else if (node->bf < -1) {   //Prawa strona wiêksza ni¿ lewa
            if (node->right->bf > 0) {  // Czy prawa strona jest "ciê¿sza"
                // Rotacja prawo-lewo (RL)
                rotateRight(node->right);
            }
            // Rotacja lewo (LL)
            rotateLeft(node);
        }

        // Przechodzenie w górê drzewa
        node = node->parent;
    }
}

// Dodawanie wêz³a do drzewa AVL
void AddToTree(BinaryTree*& root, int value, BinaryTree* parent = nullptr) {
    if (!root) {    // Je¿eli korzeñ drzewa nie istnieje
        BinaryTree* tmp = new BinaryTree;
        tmp->key = value;
        tmp->parent = parent;
        tmp->left = tmp->right = nullptr; // Inne elementy nie istniej¹
        tmp->bf = 0;
        root = tmp;

    }
    else {        // Je¿eli drzewo nie jest puste
        if (value >= root->key) {   // Dodanie do prawej strony drzewa
            AddToTree(root->right, value, root);
        }
        else {        // Dodanie do lewej strony drzewa
            AddToTree(root->left, value, root);
        }

        // Balansowanie drzewa po dodaniu wêz³a
        balanceTree(root, root);
    }
}

// Znajdowanie najmniejszego wêz³a w danym drzewie
BinaryTree* findMin(BinaryTree* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

void deleteNodeHelper(BinaryTree*& root, int key) {
    if (!root) {    //  Je¿eli dzrewo nie istnieje
        return;
    }
    else {  //  W przeciwnym wypadku - jesli drzewo istanieje
        //Szukanie klucza do usuniecia
        if (key < root->key) {
            // Szukaj w lewym poddrzewie
            deleteNodeHelper(root->left, key);
        }
        else if (key > root->key) {
            // Szukaj w prawym poddrzewie
            deleteNodeHelper(root->right, key);
        }
        else {
            // Gdy znaleziono wêze³ do usuniêcia
            if (!root->left && !root->right) {
                // Przypadek 1: Wêze³ nie ma dzieci (jest liœciem)
                delete root;
                root = nullptr;
            }
            else if (!root->left) {
                // Przypadek 2: Wêze³ ma tylko prawe dziecko
                BinaryTree* temp = root;
                root = root->right;
                delete temp;
            }
            else if (!root->right) {
                // Przypadek 2: Wêze³ ma tylko lewe dziecko
                BinaryTree* temp = root;
                root = root->left;
                delete temp;
            }
            else {
                // Przypadek 3: Wêze³ ma dwoje dzieci
                BinaryTree* minRight = findMin(root->right);
                root->key = minRight->key;
                deleteNodeHelper(root->right, minRight->key);
            }
        }
    }
}

// Funkcja usuwaj¹ca wêze³ z drzewa AVL
void deleteNode(BinaryTree*& root, int key) {
    // Wywo³anie funkcji pomocniczej deleteNodeHelper, aby usun¹æ wêze³ o kluczu 'key'
    deleteNodeHelper(root, key);

    // Balansowanie drzewa po usuniêciu wêz³a
    if (root) {
        balanceTree(root, root);
    }
}


int main() {
    BinaryTree* root = nullptr;

    // Dodawanie przyk³adowych wêz³ów
    AddToTree(root, 30);
    AddToTree(root, 20);
    AddToTree(root, 40);
    AddToTree(root, 10);
    AddToTree(root, 25);
    AddToTree(root, 35);
    AddToTree(root, 50);
    AddToTree(root, 5);

    // Wypisywanie drzewa w porz¹dku inorder po dodaniu elementow
    cout << "Print inorder AVL tree:" << endl;
    inorder(root);

    //Usuniecie wezla
    int tmp;
    cout << "Enter element to be removed" << endl;
    cin >> tmp;

    deleteNode(root, tmp);

    //Wypisanie drzewa po usunieciu wezla
    cout << "\nNode with key " << tmp << " deleted.\n\n";

    // Wypisywanie drzewa po usuniêciu wêz³a
    cout << "Print inorder AVL tree (after deletion):" << endl;
    inorder(root);

    return 0;
}
