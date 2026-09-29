#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int id;
    string name;
    string duration;

    Node* next;
    Node* prev;
};

class Playlist
{
private:
    Node* head;
    Node* tail;
    Node* current;

public:

    Playlist()
    {
        head = NULL;
        tail = NULL;
        current = NULL;
    }

    // Add song at the end
    void addSong()
    {
        int id;
        string name;
        string duration;

        cout << "Enter Song ID: ";
        cin >> id;

        cin.ignore();

        cout << "Enter Song Name: ";
        getline(cin, name);

        cout << "Enter Duration (minutes:seconds): ";
        getline(cin, duration);

        Node* newNode = new Node;

        newNode->id = id;
        newNode->name = name;
        newNode->duration = duration;

        newNode->next = NULL;
        newNode->prev = NULL;

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
            current = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }

        cout << "Song added successfully!\n";
    }

    // Delete song by ID
    void deleteSong()
    {
        if (head == NULL)
        {
            cout << "Playlist is empty.\n";
            return;
        }

        int id;
        cout << "Enter Song ID to delete: ";
        cin >> id;

        Node* temp = head;

        while (temp != NULL && temp->id != id)
        {
            temp = temp->next;
        }

        if (temp == NULL)
        {
            cout << "Song not found.\n";
            return;
        }

        // If deleting the first node
        if (temp == head)
        {
            head = head->next;

            if (head != NULL)
                head->prev = NULL;
        }
        else
        {
            temp->prev->next = temp->next;

            if (temp->next != NULL)
                temp->next->prev = temp->prev;
        }

        // If deleting the last node
        if (temp == tail)
        {
            tail = temp->prev;
        }

        // Update current song
        if (current == temp)
        {
            if (temp->next != NULL)
                current = temp->next;
            else
                current = temp->prev;
        }

        delete temp;

        cout << "Song deleted successfully!\n";
    }

    // Display playlist forward
    void displayForward()
    {
        if (head == NULL)
        {
            cout << "Playlist is empty.\n";
            return;
        }

        Node* temp = head;

        cout << "\n----- Playlist Forward -----\n";

        while (temp != NULL)
        {
            cout << "ID: " << temp->id << endl;
            cout << "Song: " << temp->name << endl;
            cout << "Duration: " << temp->duration << endl;
            cout << "----------------------------\n";

            temp = temp->next;
        }
    }

    // Display playlist backward
    void displayBackward()
    {
        if (tail == NULL)
        {
            cout << "Playlist is empty.\n";
            return;
        }

        Node* temp = tail;

        cout << "\n----- Playlist Backward -----\n";

        while (temp != NULL)
        {
            cout << "ID: " << temp->id << endl;
            cout << "Song: " << temp->name << endl;
            cout << "Duration: " << temp->duration << endl;
            cout << "----------------------------\n";

            temp = temp->prev;
        }
    }

    // Search song
    void searchSong()
    {
        if (head == NULL)
        {
            cout << "Playlist is empty.\n";
            return;
        }

        int id;

        cout << "Enter Song ID to search: ";
        cin >> id;

        Node* temp = head;

        while (temp != NULL)
        {
            if (temp->id == id)
            {
                cout << "\nSong Found!\n";
                cout << "ID: " << temp->id << endl;
                cout << "Song: " << temp->name << endl;
                cout << "Duration: " << temp->duration << endl;

                return;
            }

            temp = temp->next;
        }

        cout << "Song not found.\n";
    }

    // Play next song
    void playNext()
    {
        if (current == NULL)
        {
            cout << "Playlist is empty.\n";
            return;
        }

        if (current->next != NULL)
        {
            current = current->next;

            cout << "Now playing: "
                 << current->name << endl;
        }
        else
        {
            cout << "Already at the last song.\n";
        }
    }

    // Play previous song
    void playPrevious()
    {
        if (current == NULL)
        {
            cout << "Playlist is empty.\n";
            return;
        }

        if (current->prev != NULL)
        {
            current = current->prev;

            cout << "Now playing: "
                 << current->name << endl;
        }
        else
        {
            cout << "Already at the first song.\n";
        }
    }

    // Reverse playlist
    void reversePlaylist()
    {
        if (head == NULL)
        {
            cout << "Playlist is empty.\n";
            return;
        }

        Node* temp = head;

        while (temp != NULL)
        {
            Node* nextNode = temp->next;

            temp->next = temp->prev;
            temp->prev = nextNode;

            temp = nextNode;
        }

        // Swap head and tail
        Node* tempHead = head;
        head = tail;
        tail = tempHead;

        cout << "Playlist reversed successfully!\n";
    }
};


int main()
{
    Playlist playlist;

    int choice;

    do
    {
        cout << "\n========== PLAYLIST MENU ==========\n";
        cout << "1. Add Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist Forward\n";
        cout << "4. Display Playlist Backward\n";
        cout << "5. Search Song\n";
        cout << "6. Play Next Song\n";
        cout << "7. Play Previous Song\n";
        cout << "8. Reverse Playlist\n";
        cout << "9. Exit\n";
        cout << "===================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                playlist.addSong();
                break;

            case 2:
                playlist.deleteSong();
                break;

            case 3:
                playlist.displayForward();
                break;

            case 4:
                playlist.displayBackward();
                break;

            case 5:
                playlist.searchSong();
                break;

            case 6:
                playlist.playNext();
                break;

            case 7:
                playlist.playPrevious();
                break;

            case 8:
                playlist.reversePlaylist();
                break;

            case 9:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 9);

    return 0;
}