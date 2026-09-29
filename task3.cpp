#include <iostream>
#include <string>
using namespace std;

struct Node
{
    int bit;

    Node* next;
    Node* prev;
};

class BinaryNumber
{
private:
    Node* head;
    Node* tail;

public:

    BinaryNumber()
    {
        head = NULL;
        tail = NULL;
    }

    // Add bit at the end
    void addBit(int bit)
    {
        Node* newNode = new Node;

        newNode->bit = bit;
        newNode->next = NULL;
        newNode->prev = NULL;

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Store binary number
    void inputBinary(string binary)
    {
        for (int i = 0; i < binary.length(); i++)
        {
            if (binary[i] == '0')
                addBit(0);

            else if (binary[i] == '1')
                addBit(1);
        }
    }

    // Display binary number
    void display()
    {
        Node* temp = head;

        while (temp != NULL)
        {
            cout << temp->bit;
            temp = temp->next;
        }

        cout << endl;
    }

    // 1's complement
    void onesComplement()
    {
        Node* temp = head;

        while (temp != NULL)
        {
            if (temp->bit == 0)
                temp->bit = 1;
            else
                temp->bit = 0;

            temp = temp->next;
        }
    }

    // Convert DLL to string
    string toString()
    {
        string result = "";

        Node* temp = head;

        while (temp != NULL)
        {
            result += char(temp->bit + '0');
            temp = temp->next;
        }

        return result;
    }

    // Clear list
    void clear()
    {
        Node* temp = head;

        while (temp != NULL)
        {
            Node* nextNode = temp->next;

            delete temp;

            temp = nextNode;
        }

        head = NULL;
        tail = NULL;
    }

    // Set this number equal to another binary number
    void copyFrom(BinaryNumber& other)
    {
        clear();

        Node* temp = other.head;

        while (temp != NULL)
        {
            addBit(temp->bit);
            temp = temp->next;
        }
    }

    // Add one to binary number
    void addOne()
    {
        Node* temp = tail;

        int carry = 1;

        while (temp != NULL && carry == 1)
        {
            if (temp->bit == 0)
            {
                temp->bit = 1;
                carry = 0;
            }
            else
            {
                temp->bit = 0;
                carry = 1;
            }

            temp = temp->prev;
        }

        // If carry is still 1, add new bit at front
        if (carry == 1)
        {
            Node* newNode = new Node;

            newNode->bit = 1;
            newNode->prev = NULL;
            newNode->next = head;

            if (head != NULL)
                head->prev = newNode;
            else
                tail = newNode;

            head = newNode;
        }
    }

    // 2's complement
    void twosComplement()
    {
        // First do 1's complement
        onesComplement();

        // Then add 1
        addOne();
    }

    // Get number of bits
    int length()
    {
        int count = 0;

        Node* temp = head;

        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }

        return count;
    }

    // Binary addition
    static BinaryNumber add(BinaryNumber& a, BinaryNumber& b)
    {
        BinaryNumber result;

        Node* p = a.tail;
        Node* q = b.tail;

        int carry = 0;

        while (p != NULL || q != NULL || carry != 0)
        {
            int bitA = 0;
            int bitB = 0;

            if (p != NULL)
            {
                bitA = p->bit;
                p = p->prev;
            }

            if (q != NULL)
            {
                bitB = q->bit;
                q = q->prev;
            }

            int sum = bitA + bitB + carry;

            int resultBit = sum % 2;

            carry = sum / 2;

            // Add to front
            Node* newNode = new Node;

            newNode->bit = resultBit;
            newNode->prev = NULL;
            newNode->next = result.head;

            if (result.head != NULL)
                result.head->prev = newNode;
            else
                result.tail = newNode;

            result.head = newNode;
        }

        return result;
    }

    // Convert binary to decimal
    long long toDecimal()
    {
        long long decimal = 0;

        Node* temp = head;

        while (temp != NULL)
        {
            decimal = decimal * 2 + temp->bit;

            temp = temp->next;
        }

        return decimal;
    }

    // Destructor
    ~BinaryNumber()
    {
        clear();
    }
};

int main()
{
    string input1;
    string input2;

    cout << "Enter first binary number: ";
    cin >> input1;

    cout << "Enter second binary number: ";
    cin >> input2;

    BinaryNumber num1;
    BinaryNumber num2;

    num1.inputBinary(input1);
    num2.inputBinary(input2);

    cout << "\nFirst binary number: ";
    num1.display();

    cout << "Second binary number: ";
    num2.display();

    // 1's complement
    BinaryNumber ones;
    ones.copyFrom(num1);

    ones.onesComplement();

    cout << "\n1's Complement of first number: ";
    ones.display();

    // 2's complement
    BinaryNumber twos;
    twos.copyFrom(num1);

    twos.twosComplement();

    cout << "2's Complement of first number: ";
    twos.display();

    // Addition
    BinaryNumber sum = BinaryNumber::add(num1, num2);

    cout << "\nBinary Addition: ";
    sum.display();

    // Decimal conversion
    cout << "\nFirst number in decimal: "
         << num1.toDecimal() << endl;

    cout << "Second number in decimal: "
         << num2.toDecimal() << endl;

    cout << "Sum in decimal: "
         << sum.toDecimal() << endl;

    return 0;
}