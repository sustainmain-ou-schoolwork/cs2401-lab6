/*************************************************************************
    Lab Assignment 6: This is another lab assignment in working with 
    linked lists. We will be using a struct node, for its simplicity,
    and working with non-member functions here. The main point is to 
    work with the logic of a linked list. Do not be afraid to make 
    drawings on scrap paper.
    The prototypes for the functions that you are to implement are
    included. You should uncomment them when you are ready to write 
    the implementation.
    John Dolan                   Spring 2014
    Patricia Lindner             Fall 2021
*************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

struct node
{
    int data;
    node *next;
};

// These are the three I have implemented for you
void build_list(node *&head); // note that we are passing by reference
void show_list(const node *head);
int size(const node *head);

//These are the two that you are to write, as described in the
//instructions page.

void remove_repeats(node *&head);
void split_list(const node* original, node*& lesser, node*& greater, int split_value);

int main()
{
    int start, stop;
    int split;
    node *head = NULL;
    node *lesser = NULL;
    node *greater = NULL;

    // build list
    start = time(NULL);
    build_list(head);
    stop = time(NULL);
    cout << "Time to build list = " << stop - start << " seconds.\n" << endl;

    // print list
    start = time(NULL);
    show_list(head);
    stop = time(NULL);
    cout << "Time to print list = " << stop - start << " seconds.\n";
    cout << "Size of the list = " << size(head) << '\n' << endl;

    // remove repeats and print list
    start = time(NULL);
    remove_repeats(head);
    show_list(head);
    stop = time(NULL);
    cout << "Time to print list = " << stop - start << " seconds.\n";
    cout << "Size of the list = " << size(head) << '\n' << endl;

    // get split value
    do {
        cout << "Enter the split value, between 1 and 500: ";
        cin >> split;
    } while (!(split >= 1 && split <= 500));

    // split list into lesser and greater and print them
    start = time(NULL);
    split_list(head, lesser, greater, split);
    show_list(lesser);
    cout << '\n';
    show_list(greater);
    stop = time(NULL);
    cout << "Time to print lists = " << stop - start << " seconds.\n";
    cout << "Size of the lesser list = " << size(lesser) << '\n' << endl;
    cout << "Size of the greater list = " << size(greater) << '\n' << endl;

    return 0;
}

// builds a linked list of 2000 random integers, all in the range 1 - 500
void build_list(node *&head)
{
    const int HIGHEST_INT = 500;
    const int NUMBER_OF_INTS = 2000;

    node *cursor;

    head = new node;
    head -> data = rand() % HIGHEST_INT + 1;

    cursor = head;
    for (int i = 0; i < (NUMBER_OF_INTS - 1); ++i) {
        cursor -> next = new node;
        cursor = cursor -> next;
        cursor -> data = rand() % HIGHEST_INT + 1;
    }
    cursor -> next = NULL;
}

// outputs the contents of a linked list to the screen
void show_list(const node *head)
{
    const int INTS_PER_ROW = 20;
    const node *cursor = head;

    int i = 0;
    while (cursor != NULL) {
        cout << setw(4) << cursor -> data;
        if (i >= INTS_PER_ROW) {
            cout << endl;
            i = 0;
        }
        else {
            i++;
        }

        cursor = cursor->next;
    }
    cout << endl;
}

// returns the number of nodes in a linked list
int size(const node *head)
{
    const node *cursor = head;
    int count = 0;
    while (cursor != NULL) {
        count++;
        cursor = cursor -> next;
    }
    return count;
}

/**
 * @brief Removes any duplicate ints in a linked list, saving the first appearance of any given number.
 * 
 * @param head the head of the linked list
 */
void remove_repeats(node *&head) {
    node* majorNode = head;

    while (majorNode != NULL) {
        node* cursor = majorNode -> next;
        node* previous = majorNode;
        while (cursor != NULL) {
            if (cursor -> data == majorNode -> data) {
                // remove the node pointed to by cursor
                node* tmp;
                tmp = cursor -> next;
                previous -> next = tmp;
                delete cursor;

                cursor = tmp;
            }
            else {
                // shift previous and cursor down the list
                previous = cursor;
                cursor = cursor -> next;
            }
        }

        // shift majorNode down the list
        majorNode = majorNode -> next;
    }
}

/**
 * @brief Puts each int in a linked list into one of two other linked lists, depending on a split value. 
 * 
 * @param original the head of the original linked list
 * @param lesser the head of the linked list that will be filled with ints less than split_value
 * @param greater the head of the linked list will be filled with ints greater than split_value
 * @param split_value the value to compare each int inside original to
 */
void split_list(const node* original, node*& lesser, node*& greater, int split_value) {
    const node* cursorOriginal = original;
    node* cursorLesser = lesser;
    node* cursorGreater = greater;

    while (cursorOriginal != NULL) {
        // if the current node is less than the split value, put it in lesser
        // if the current node is greater than the split value, put it in greater
        if (cursorOriginal -> data < split_value) {
            // make a new node
            if (lesser == NULL) {
                lesser = new node;
                cursorLesser = lesser;
            }
            else {
                cursorLesser -> next = new node;
                cursorLesser = cursorLesser -> next;
            }

            // set the values of the node
            cursorLesser -> data = cursorOriginal -> data;
            cursorLesser -> next = NULL;
        }
        else if (cursorOriginal -> data > split_value) {
            // make a new node
            if (greater == NULL) {
                greater = new node;
                cursorGreater = greater;
            }
            else {
                cursorGreater -> next = new node;
                cursorGreater = cursorGreater -> next;
            }

            // set the values of the node
            cursorGreater -> data = cursorOriginal -> data;
            cursorGreater -> next = NULL;
        }

        // point the cursor to the next node
        cursorOriginal = cursorOriginal -> next;
    }
}