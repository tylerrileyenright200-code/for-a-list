#include <iostream>
#include <cstddef>
#include <cassert>

class LinkedList
{
private:
    struct Node
    {
        int data;
        Node* next;

        Node(int value)
            : data(value), next(nullptr)
        {
        }
    };

    Node* head;
    std::size_t nodeCount;

public:
    // Constructor
    LinkedList()
        : head(nullptr), nodeCount(0)
    {
    }

    // Destructor
    ~LinkedList()
    {
        clear();
    }

    // Prevent accidental shallow copies
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    // Add a value to the beginning of the list
    void pushFront(int value)
    {
        Node* newNode = new Node(value);

        newNode->next = head;
        head = newNode;

        ++nodeCount;
    }

    // Add a value to the end of the list
    void pushBack(int value)
    {
        Node* newNode = new Node(value);

        if (head == nullptr)
        {
            head = newNode;
            ++nodeCount;
            return;
        }

        Node* current = head;

        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newNode;
        ++nodeCount;
    }

    // Check whether the list contains a value
    bool contains(int value) const
    {
        const Node* current = head;

        while (current != nullptr)
        {
            if (current->data == value)
            {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    // Check whether the list is empty
    bool empty() const
    {
        return head == nullptr;
    }

    // Return the number of nodes in the list
    std::size_t size() const
    {
        return nodeCount;
    }

    // Display the contents of the list
    void print() const
    {
        if (head == nullptr)
        {
            std::cout << "[empty]\n";
            return;
        }

        const Node* current = head;

        while (current != nullptr)
        {
            std::cout << current->data;

            if (current->next != nullptr)
            {
                std::cout << " -> ";
            }

            current = current->next;
        }

        std::cout << '\n';
    }

    // Delete every node in the list
    void clear()
    {
        Node* current = head;

        while (current != nullptr)
        {
            Node* nodeToDelete = current;
            current = current->next;

            delete nodeToDelete;
        }

        head = nullptr;
        nodeCount = 0;
    }

    /*
        New function 1: reverse()

        Reverses the order of the nodes in the list.
    */
    void reverse()
    {
        Node* previous = nullptr;
        Node* current = head;

        while (current != nullptr)
        {
            Node* nextNode = current->next;

            current->next = previous;
            previous = current;
            current = nextNode;
        }

        head = previous;
    }

    /*
        New function 2: remove()

        Removes the first node containing the given value.

        Returns true if a node was removed.
        Returns false if the value was not found.
    */
    bool remove(int value)
    {
        if (head == nullptr)
        {
            return false;
        }

        // Remove the first node
        if (head->data == value)
        {
            Node* nodeToDelete = head;
            head = head->next;

            delete nodeToDelete;
            --nodeCount;

            return true;
        }

        Node* current = head;

        // Search for the value after the first node
        while (current->next != nullptr)
        {
            if (current->next->data == value)
            {
                Node* nodeToDelete = current->next;

                current->next = nodeToDelete->next;

                delete nodeToDelete;
                --nodeCount;

                return true;
            }

            current = current->next;
        }

        return false;
    }
};

int main()
{
    LinkedList numbers;

    std::cout << "Creating the linked list...\n\n";

    numbers.pushBack(10);
    numbers.pushBack(20);
    numbers.pushBack(30);
    numbers.pushBack(40);
    numbers.pushFront(5);

    std::cout << "Original list:\n";
    numbers.print();

    std::cout << "\nList size: "
        << numbers.size()
        << '\n';

    // Test contains()
    assert(numbers.contains(20));
    assert(!numbers.contains(100));

    std::cout << "\nContains 20: ";

    if (numbers.contains(20))
    {
        std::cout << "Yes\n";
    }
    else
    {
        std::cout << "No\n";
    }

    std::cout << "Contains 100: ";

    if (numbers.contains(100))
    {
        std::cout << "Yes\n";
    }
    else
    {
        std::cout << "No\n";
    }

    // Test the reverse() function
    std::cout << "\nCalling reverse()...\n";

    numbers.reverse();

    std::cout << "Reversed list:\n";
    numbers.print();

    /*
        The list should now be:

        40 -> 30 -> 20 -> 10 -> 5
    */

    assert(numbers.size() == 5);
    assert(numbers.contains(40));
    assert(numbers.contains(5));

    // Test removing a value from the middle
    std::cout << "\nRemoving 30...\n";

    if (numbers.remove(30))
    {
        std::cout << "30 was removed successfully.\n";
    }
    else
    {
        std::cout << "30 was not found.\n";
    }

    std::cout << "List after removing 30:\n";
    numbers.print();

    assert(!numbers.contains(30));
    assert(numbers.size() == 4);

    // Test removing the first node
    std::cout << "\nRemoving 40 from the front...\n";

    if (numbers.remove(40))
    {
        std::cout << "40 was removed successfully.\n";
    }
    else
    {
        std::cout << "40 was not found.\n";
    }

    std::cout << "List after removing 40:\n";
    numbers.print();

    assert(!numbers.contains(40));
    assert(numbers.size() == 3);

    // Test removing a value that is not in the list
    std::cout << "\nAttempting to remove 99...\n";

    if (numbers.remove(99))
    {
        std::cout << "99 was removed successfully.\n";
    }
    else
    {
        std::cout << "99 was not found, so nothing was removed.\n";
    }

    assert(numbers.size() == 3);

    // Verify the remaining values
    assert(numbers.contains(5));
    assert(numbers.contains(10));
    assert(numbers.contains(20));

    std::cout << "\nFinal list:\n";
    numbers.print();

    std::cout << "Final size: "
        << numbers.size()
        << '\n';

    // Test clear()
    std::cout << "\nClearing the list...\n";

    numbers.clear();

    assert(numbers.empty());
    assert(numbers.size() == 0);

    std::cout << "List after clear():\n";
    numbers.print();

    std::cout << "\nAll tests passed successfully.\n";

    return 0;
}