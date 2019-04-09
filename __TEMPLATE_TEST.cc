#include <string>
#include <iostream>

template<typename T> struct Node {
    Node<T> *next;
    T head;
    public:

    Node<T>(void);
    Node<T>(const T&);

    template<typename> friend struct LinkedList;
};

template<typename T> Node<T>::Node(void): next(nullptr), head() {}
template<typename T> Node<T>::Node(const T& _) { this->head = _; }


template<typename T> struct LinkedList {
    Node<T> *root;
    size_t size;
    public:

    LinkedList(void);
    ~LinkedList(void);

    void push(const T&);
    void pop(void);
    size_t getSize(void) const;

    T& operator[] (int);
};

template<typename T> LinkedList<T>::LinkedList(void): root(nullptr), size(0) {}

template<typename T>
void LinkedList<T>::push(const T& _) {

    if (this->root == nullptr)
    {
        this->root = new Node<T>(_);
    }
    else
    {
        Node<T>* node = this->root;
        while ((node = node->next) != nullptr);
        node = new Node<T>(_);
    }

    ++this->size;
}

template<typename T>
void LinkedList<T>::pop(void) {
    Node<T> *node = this->root;

    for(size_t i = 0; i < this->size-1; ++i) node = node->next;

    delete node->next;
    node->next = nullptr;
    
    --this->size;
}

template<typename T> size_t LinkedList<T>::getSize(void) const { return this->size; }


template<typename T>
T& LinkedList<T>::operator[] (int index) {
    Node<T> *node = this->root;

    for(size_t i = 0; i < index && node != nullptr; ++i) node = node->next;

    if (node != nullptr) {
        return node->head;
    } else {
        throw std::runtime_error("node is nullptr!");
    }
}

struct Guest {
    std::string name;
    uint32_t id;
};

int main() {
    Guest guest1;
    guest1.name = "Saidwho12";
    guest1.id = 2256;

    LinkedList<Guest> guestList;
    guestList.push(guest1);

    std::cout << guestList[0].name << std::endl;

    return 0;
}