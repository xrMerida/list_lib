#include "list.h"
#include <stdexcept>

void List::Add(int item) {
    Node **link = &header;
    while (*link) {
        link = &(*link)->next;
    }
    *link = new Node{item, *link};
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
    Node **link = &header;
    while (*link && index > 0) {
        index--;
        link = &(*link)->next;
    }

    if (index != 0) throw std::out_of_range("index out of range");

    *link = new Node{item, *link};
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
    Node **link = &header;
    while (*link && (*link)->data != item) {

        link = &(*link)->next;
    }

    if (!*link) return false;

    Node *del = *link;
    *link = (*link)->next;
    delete del;
    return true;
}

void List::RemoveAt(int index) {
    Node **link = &header;
    while (*link && index > 0) {
        index--;
        link = &((*link)->next);
    }

    if (index != 0 || !*link) throw std::out_of_range("index out of range");

    Node *del = *link;
    *link = (*link)->next;
    delete del;
}
