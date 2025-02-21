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
	int x;
	ListV4<int> y;
	ListV4<float> z;

	Rune(int x, int y, float z) {
		this->x = x;
		this->y.insert(this->y.last(), y, false);
        this->z.insert(this->z.last(), z, false);
	}
};

struct Spell{
	string name;	
	ListV4<Rune> runes;
    
};

struct Wizard:Spell{
    string nombre;
};

class Arcane{
    ListV4<Spell> legalSpells;
	ListV4<Spell> illegalSpells;
    ListV4<Wizard> underInvestigation;
    public:
	void longestPathByEdge(Spell spell, bool first = true){

		if (it == nullptr) return;

        if (!first) {
			if (it == spell.runes.first()) 
		}
    }
    
}
void readFile(){

}

void writeFile(){

}

int main(){

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

    

    return 0;
}