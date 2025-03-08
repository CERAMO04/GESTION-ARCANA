#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<math.h>
using namespace std;

template <typename T>
class BaseNode {
public:
	T payload;

	BaseNode(T payload) {
		this->payload = payload;
	}

	BaseNode() {
		this->payload = T();
	}
};

// Nodo con un solo enlace al siguiente
template <typename T>
class SimpleLinkNode : public BaseNode<T> {
public:
	SimpleLinkNode<T>* next;

	SimpleLinkNode() : BaseNode<T>() {
		next = nullptr;
	}

	SimpleLinkNode(T payload) : BaseNode<T>(payload) {
		next = nullptr;
	}
};

// Nodo con doble enlace, siguiente y previo
template <typename T>
class DoubleLinkNode : public BaseNode<T> {
public:
	DoubleLinkNode<T>* prev;
	DoubleLinkNode<T>* next;

	DoubleLinkNode(T payload) : BaseNode<T>(payload) {
		next = nullptr;
		prev = nullptr;
	}
};

template <typename T>
class ListV4
{
public:
	typedef DoubleLinkNode<T>* iterator;

	// Construye una lista vacia
	ListV4();

	~ListV4();

	iterator first(); // En este caso esta funcion no puede ser const porque podemos alterar first a travez de ella
	// ya que retorna la direccion de memoria de la variable _first

	iterator last();

	T* get(iterator i) const;

	void next(iterator& i) const;

	void prev(iterator& i) const;

	bool isEmpty() const;

	int size() const;

	void insert(iterator i, T payload, bool before = true);

	void deleteNode(iterator i);

private:
	iterator _first;
	iterator _last;
	int _size;
};

template<typename T>
ListV4<T>::ListV4()
{
	this->_first = nullptr;
	this->_last = nullptr;
}

template<typename T>
ListV4<T>::~ListV4()
{
	while (!this->isEmpty()) {
		this->deleteNode(this->first());
	}
}

template<typename T>
typename::ListV4<T>::iterator ListV4<T>::first()
{
	return this->_first;
}

template<typename T>
typename::ListV4<T>::iterator ListV4<T>::last()
{
	return this->_last;
}

template<typename T>
T* ListV4<T>::get(iterator i) const
{
	if (i == nullptr) return nullptr;

	return &i->payload;
}

template<typename T>
void ListV4<T>::next(iterator& i) const
{
	if (i == nullptr) return;
	i = i->next;
}

template<typename T>
void ListV4<T>::prev(iterator& i) const
{
	if (i == nullptr) return;
	i = i->prev;
}

template<typename T>
bool ListV4<T>::isEmpty() const
{
	return this->_first == nullptr;
}

template<typename T>
int ListV4<T>::size() const
{
	return this->_size;
}

template<typename T>
void ListV4<T>::insert(iterator i, T payload, bool before)
{
	DoubleLinkNode<T>* newNode = new DoubleLinkNode<T>(payload);

	this->_size++;

	if (this->isEmpty()) {
		this->_first = newNode;
		this->_last = newNode;
		return;
	}

	if (before) {
		newNode->next = i;
		newNode->prev = i->prev;
		if (i->prev != nullptr)
			i->prev->next = newNode;

		i->prev = newNode;

		if (this->first() == i) this->_first = newNode;

		return;
	}

	newNode->next = i->next;
	newNode->prev = i;
	if (i->next != nullptr)
		i->next->prev = newNode;

	i->next = newNode;

	if (this->last() == i) this->_last = newNode;
}

template<typename T>
void ListV4<T>::deleteNode(iterator i)
{
	if (i == nullptr) return;

	this->_size--;

	if (i == this->first()) this->_first = i->next;

	if (i == this->last()) this->_last = i->prev;

	if (i->prev != nullptr) i->prev->next = i->next;

	if (i->next != nullptr) i->next->prev = i->prev;

	delete i;
}

struct Rune {
    char type;
    int x;
    ListV4<int> y;
    ListV4<int> z; 

    Rune(char type = '\0', int x = 0) : type(type), x(x) {}
};

struct Spell{
	string spellName;
	string wizardName;
	ListV4<Rune> runes;

	Spell(string name = "test", string wizard = "") : spellName(name), wizardName(wizard) {
		cout << "Spell created: " << name << endl;
	}

	~Spell(){
		cout << "Spell destroyed: " << spellName << endl;
	}

    void addRunes(const string runeChars) {
        for (size_t i = 0; i < runeChars.size(); i++) {
            runes.insert(runes.last(), Rune(runeChars[i], i + 1), false);
        }
    }

    void addEdge(int x, int y, int z) {
        ListV4<Rune>::iterator it = runes.first();
        while (it != nullptr) {
            Rune* current = runes.get(it);
            if (current->x == x) {
                current->y.insert(current->y.last(), y, false);
                current->z.insert(current->z.last(), z, false);
                break;
            }
			runes.next(it);
        }
        it = runes.first();
        while (it != nullptr) {
            Rune* current = runes.get(it);
            if (current->x == y) {
                current->y.insert(current->y.last(), x, false);
                current->z.insert(current->z.last(), z, false);
                break;
            }
            runes.next(it);
        }
	}
        void printAdjacencyList() {
            auto it = runes.first();
            while (it != nullptr) {
                Rune* current = runes.get(it);
                cout << "Rune " << current->type << " (" << current->x << ") is connected to: ";
                
                // Print connected vertices and weights
                auto yIt = current->y.first();
                auto zIt = current->z.first();
                while (yIt != nullptr && zIt != nullptr) {
                    int connectedVertex = *current->y.get(yIt);
                    int weight = *current->z.get(zIt);
                    cout << "(" << connectedVertex << ", " << weight << ") ";
                    current->y.next(yIt);
                    current->z.next(zIt);
                }
                cout << endl;
                runes.next(it);
            }
        }	
};

class Arcane{
	public:
    ListV4<Spell> legalSpells;
	ListV4<Spell> illegalSpells;
    ListV4<string> underInvestigation;

	void longestPathByEdge(Spell spell, bool first = true){
		/*
		if (it == nullptr) return;

        if (!first) {
			if (it == spell.runes.first()) 
		}
		*/
    }

	void readFile() {
		int n_spells, n_vertex, n_edges, x, y, z;
		string name, rune;
		ifstream file;
	
		file.open("spellList.in");
		if (!file.is_open()) {
			cout << "Error al abrir el archivo" << endl;
			exit(1);
		}
	
		while (!file.eof()) {
			Spell aux;
			file >> n_spells;
			file.ignore();
			getline(file, name);
			aux.wizardName = name;
			file >> n_vertex;
			file.ignore();
			getline(file, rune);
			cout << "Adding runes..." << endl;
			aux.addRunes(rune);
			file >> n_edges;
			file.ignore();
			for (int i = 0; i < n_edges; i++) {
				file >> x >> y >> z;
				cout << "Adding adjacency for " << x << " " << y << " " << z << endl;
				aux.addEdge(x, y, z);
			}
			legalSpells.insert(legalSpells.last(), aux, false);
		}
		file.close();
	} 
};


void writeFile(){
	
}

int main(){
	/*
    ListV4<int> a;
    a.insert(a.first(), 2, false);
    a.insert(a.first(), 1, false);

    ListV4<int> b;
    b.insert(b.first(), 3, false);
    b.insert(b.first(), 4, false);

    ListV4<int>::iterator it = a.first();

    while (it != nullptr) {
        int* aux = a.get(it);
        ListV4<int>::iterator toDelete = it;
        a.next(it) ;// Avanza el iterador antes de eliminar el nodo
    	b.insert(b.last(), *aux, false);
        //a.deleteNode(toDelete); // Elimina el nodo de la lista 'a'
    }

    it = b.first();
	ListV4<int>::iterator lastNode = b.last();  // Obtiene el iterador del último nodo de 'b'
    b.deleteNode(lastNode);  // Elimina el último nodo de 'b'
    while (it != nullptr) {
        int* aux = b.get(it);
        cout << *aux << " ";
        b.next(it);
    }

    */
	Arcane arcane;
	arcane.readFile();
	/*ListV4<Spell>::iterator it = arcane.legalSpells.first();
	Spell* auxPtr = arcane.legalSpells.get(it);

	if (auxPtr) {
		cout << auxPtr->wizardName << endl;
		auxPtr->printAdjacencyList();
	}*/

    return 0;
}