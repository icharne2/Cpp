#include <iostream>
#include <math.h>

using namespace std;

const int V = 9; // Liczba wierzcho³ków w grafie
const int E = 24; // Liczba krawêdzi w grafie

// Struktura krawêdzi grafu
struct Edge {
    int src, dest, weight;  // Wierzcho³ki krawêdzi, waga krawêdzi
};

// Struktura do reprezentowania zbioru wierzcho³ków
struct Subset {
    int parent; //wskaŸnik na rodzica w drzewie zbiorów,
    int rank;   //G³êbokoœæ drzewa
};

// Porównanie krawêdzi na podstawie ich wagi
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Znalezienie zbioru, do którego nale¿y element i
int find(Subset *subsets, int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);

    return subsets[i].parent;
}

// Implementacja bubble sort
void bubbleSort(Edge *arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].weight > arr[j + 1].weight)
                swap(arr[j], arr[j + 1]);
}

// Po³¹czenie dwóch zbiorów - x i y
void Connect(Subset *subsets, int x, int y) { // Tablica struktur - reprezentacja zbiorów, wierzcho³ki x,y
    int xroot = find(subsets, x);   //Znalezienie orzenia zbioru do ktorego nalezy wierzcho³ek x
    int yroot = find(subsets, y);   //Znalezienie orzenia zbioru do ktorego nalezy wierzcho³ek y

    //rank to przyblizona wartosc drzewa, wybieramy, który z korzeni stanie siê rodzicem, mniejsza ranga = dziecko
    if (subsets[xroot].rank < subsets[yroot].rank)  //Aby nie wyst¹pi³ probelm przy równowa¿eniu drzewa poniewa¿ wtedy wyst¹pi problem z u¿yciem funkcji 'find'
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {  //Jeœli s¹ równe, zwiêkszamy rangê drzewa wynikowego
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

void Kruskal(Edge *edges) {  //Przyjmuje wskaŸnik na krawedŸ
    Edge result[V];  // Wynik minimalnego drzewa rozpinaj¹cego (MST), bêdzie mieæ V-1 krawêdzi
    int e = 0;  // Indeks dla wyniku MST
    int i = 0;  // Indeks do iteracji po posortowanych krawêdziach

    // Sortowanie krawêdzi na podstawie ich wag
    bubbleSort(edges, E);

    // Tworzenie V ró¿nych zbiorów. Ka¿dy wierzcho³ek pocz¹tkowo jest w swoim w³asnym zbiorze.
    Subset* subsets = new Subset[V];

    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Iteracja przez posortowane krawêdzie i wybór tych, które nie tworz¹ cyklu
    while (e < V - 1 && i < E) {    //Dopóki nie skonstruujemy wystarczaj¹cej liczby krawêdzi lub nie przekroszymy wszystkich krawedzi
        Edge next_edge = edges[i++];    //Kolejna krawêdŸ posortownej tablicy krawêdzi

        int x = find(subsets, next_edge.src);   //zbiór, do którego nale¿y wierzcho³ek Ÿród³owy
        int y = find(subsets, next_edge.dest);  //zbiór, do którego nale¿y wierzcho³ek docelowy 

        // Jeœli w³¹czenie tej krawêdzi nie powoduje powstania cyklu, dodaj j¹ do wyniku
        if (x != y) {
            result[e++] = next_edge;    // Dodanie krawedzi do wynikow
            Connect(subsets, x, y);   // Funkcja ³¹cz¹ca oba zbiory w jeden wiêkszy
        }
    }

    // Wyœwietlenie skonstruowanego MST
    cout << "Krawedzie w konstrukcji:" << endl;

    for (i = 0; i < e; ++i)
        cout << result[i].src << " - " << result[i].dest << " = " << result[i].weight << endl;

    //Zwolnienie pamiêci
    delete[] subsets;
}


int main() {
	//Algorytm Kruskala
    
    //Tablica krawedzi grafu (Od,do,waga)
    Edge edges[E] = {
        {1, 2, 5}, {1, 4, 4}, {2, 1, 5}, {2, 8, 3}, {3, 5, 7}, {3, 6, 8}, 
        {3, 7, 1}, {3, 8, 7}, {4,1,4}, {4,6,20}, {4,8,14}, {5,3,7}, {5,6,3}, 
        {5,7,2}, {6,3,8}, {6,4,20}, {6,5,3}, {7,3,1}, {7,5,2}, {7,8,7}, {8,2,3}, 
        {8,3,7}, {8,4,14}, {8,7,7} 
    };

    Kruskal(edges);

	system("PAUSE");
	return 0;
}