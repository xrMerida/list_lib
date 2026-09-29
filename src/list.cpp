#include "list.h"
#include <stdexcept>

void List::Add(int item) {
    Node *newNode = new Node{item, nullptr};

    if (header) {
        Node *node = header;
        while (node->next) node = node->next;
        node->next = newNode;
    } else {
        header = newNode;
    }
}

void List::Clear() {
    while (header) {
        Node *aux = header;
        header = header->next;
        delete aux;
    }
}

int List::Count() {
    int i = 0;
    Node *node = header;
    while (node) {
        node = node->next;
        i++;
    }
    return i;
}

bool List::Contains(int item) {
    Node *node = header;
    while (node) {
        if (node->data == item) return true;

        node = node->next;
    }
    return false;
}

int List::IndexOf(int item) {
    int i = 0;
    Node *node = header;
    while (node) {
        if (node->data == item) return i;

        node = node->next;
        i++;
    }
    return -1;
}

void List::Insert(int index, int item) {
    Node *prev = nullptr;
    Node *curr = header;
    while (curr && index > 0) {
        prev = curr;
        curr = curr->next;
        index--;
    }

    // Validar que el índice sea válido
    if (index != 0) throw std::out_of_range("index out of range");

    Node *newNode = new Node{item, curr};
    if (!prev) {
        header = newNode;
    } else {
        prev->next = newNode;
    }
}

int List::GetItem(int index) {
    Node *node = header;
    while (node && index > 0) {
        node = node->next;
        index--;
    }

    // Validar que el índice sea válido
    if (!node || index != 0) throw std::out_of_range("index out of range");

    return node->data;
}

void List::SetItem(int index, int item) {
    Node *node = header;
    while (node && index > 0) {
        node = node->next;
        index--;
    }

    // Validar que el índice sea válido
    if (!node || index != 0) throw std::out_of_range("index out of range");

    node->data = item;
}

int List::LastIndexOf(int item) {
    Node *node = header;
    int idx = -1;
    for (int i = 0; node; i++) {
        if (node->data == item) idx = i;
        node = node->next;
    }
    return idx;
}

bool List::Remove(int item) {
    Node *prev = nullptr;
    Node *curr = header;
    while (curr && curr->data != item) {
        prev = curr;
        curr = curr->next;
    }

    // Validar que el elemento exista en la lista
    if (!curr) return false;

    if (!prev) {
        header = header->next;
        delete curr;
    } else {
        prev->next = curr->next;
        delete curr;
    }
    return true;
}

void List::RemoveAt(int index) {
    Node *prev = nullptr;
    Node *curr = header;
    while (curr && index > 0) {
        prev = curr;
        curr = curr->next;
        index--;
    }

    // Validar que el indice sea valido
    if (!curr || index != 0 || !header)
        throw std::out_of_range("index out of range");

    if (!prev) {
        header = header->next;
        delete curr;
    } else {
        prev->next = curr->next;
        delete curr;
    }
}
