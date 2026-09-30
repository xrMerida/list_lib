#include "list.h"
#include <stdexcept>

void List::Add(int item) {
    Node **node = &header;
    while (*node) {
        node = &(*node)->next;
    }
    *node = new Node{item, *node};
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
    Node **node = &header;
    while (*node && index > 0) {
        index--;
        node = &(*node)->next;
    }

    if (index != 0) throw std::out_of_range("index out of range");

    *node = new Node{item, *node};
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
    Node **node = &header;
    while (*node && (*node)->data != item) {

        node = &(*node)->next;
    }

    if (!*node) return false;

    Node *del = *node;
    *node = (*node)->next;
    delete del;
    return true;
}

void List::RemoveAt(int index) {
    Node **node = &header;
    while (*node && index > 0) {
        index--;
        node = &((*node)->next);
    }

    if (index != 0 || !*node) throw std::out_of_range("index out of range");

    Node *del = *node;
    *node = (*node)->next;
    delete del;
}
