#include <iostream>
using namespace std;

struct Node
{
    int id;
    Node* next;
};

class CircularList
{
private:
    Node* head;

public:
    CircularList()
    {
        head = NULL;
    }

    // Create circular list
    void createCircle(int n)
    {
        if (n <= 0)
            return;

        Node* last = NULL;

        for (int i = 1; i <= n; i++)
        {
            Node* newNode = new Node;

            newNode->id = i;
            newNode->next = NULL;

            if (head == NULL)
            {
                head = newNode;
                last = newNode;
            }
            else
            {
                last->next = newNode;
                last = newNode;
            }
        }

        // Connect last node back to first
        last->next = head;
    }

    // Josephus elimination
    void josephus(int k)
    {
        if (head == NULL || k <= 0)
            return;

        Node* current = head;
        Node* previous = NULL;

        cout << "\nEliminated order: ";

        while (current->next != current)
        {
            // Move k-1 positions
            for (int i = 1; i < k; i++)
            {
                previous = current;
                current = current->next;
            }

            cout << current->id << " ";

            // Remove current
            previous->next = current->next;

            Node* deletedNode = current;
            current = current->next;

            delete deletedNode;
        }

        // Only one node remains
        cout << "\nSurvivor: " << current->id << endl;

        delete current;
        head = NULL;
    }
};

int main()
{
    int n;
    int k;

    cout << "Enter number of people: ";
    cin >> n;

    cout << "Enter step count: ";
    cin >> k;

    CircularList circle;

    circle.createCircle(n);

    circle.josephus(k);

    return 0;
}