#include <iostream>

struct Node {
    int data;
    Node* next;
    Node* skip;

    Node(int value) : data(value), next(nullptr), skip(nullptr) {}
};

class SkipList {
public:
    SkipList() : head(nullptr) {}

    void add(int value) {
        Node* newNode = new Node(value);

        if (!head) {
            head = newNode;
            return;
        }

        Node* current = head;
        Node* prev = nullptr;

        while (current && current->data < value) {
            prev = current;
            current = current->next;
        }

        newNode->next = current;
        if (prev) {
            prev->next = newNode;
        }

        if (prev && prev->skip && prev->skip->data < value) {
            newNode->skip = prev->skip;
            prev->skip = newNode;
        }
        else if (prev) {
            prev->skip = newNode;
        }
    }

    bool search(int value) {
        Node* current = head;

        while (current) {
            if (current->data == value)
                return true;

            if (current->skip && current->skip->data <= value)
                current = current->skip;
            else
                current = current->next;
        }

        return false;
    }

    void printList() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    void printSkipList() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";

            if (current->skip)
                std::cout << " (Skip to " << current->skip->data << ") ";

            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

private:
    Node* head;
};

int main() {
    SkipList list;

    list.add(3);
    list.add(6);
    list.add(1);
    list.add(9);
    list.add(2);

    std::cout << "List: ";
    list.printList();

    std::cout << "Skip List: ";
    list.printSkipList();

    std::cout << "Searching for 6: " << (list.search(6) ? "Found" : "Not found") << std::endl;
    std::cout << "Searching for 5: " << (list.search(5) ? "Found" : "Not found") << std::endl;

    return 0;
}
