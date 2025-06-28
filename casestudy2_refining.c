// For printf(), scanf(), etc. - Includes the standard input/output library for console operations.
#include <stdio.h>
// for malloc() - Includes the standard library, which is necessary for dynamic memory allocation.
#include <stdlib.h>
// for ????
#include <string.h>

// Initialization of struct Node - Defines the structure for a node in the linked list.
struct Node
{
    // Holds the integer value for the node.
    int data;
    // A pointer to the next node in the sequence.
    struct Node *next;
};

// Global variable for *head (to be accessible for every function) - 'head' will always point to the first node of the list.
struct Node *head = NULL;

// Function Prototypes - Declares the functions that will be defined later in the code.
void createList();    // Prototype for the function that creates the list.
void displayList();   // Prototype for the function that displays the list.
void sortList();      // Prototype for the function that sorts the list.
void searchNumber();  // Prototype for the function that searches for a number in the list.

// Main function - The entry point of the program.
int main()
{
    // 'choice' will store the user's menu selection.
    char choice[100];

    // while (1) keeps the main menu showing - This creates an infinite loop to keep the program running until the user exits.
    while (1)
    {
        // Displaying the MAIN MENU - Prints the options available to the user.
        printf("\n===== MAIN MENU =====\n");
        printf("(a) Create a Linear Linked List\n");
        printf("(b) Display a Linear Linked List\n");
        printf("(c) Sort a Linear Linked List - Ascending\n");
        printf("(d) Search a number\n");
        printf("(e) Exit\n");
        while (1)
        {
            printf("Enter choice: ");
            if (fgets(choice, sizeof(choice), stdin) == NULL)
            {
                printf("Input error! Try again.\n");
                continue;
            }    
            choice[strscpn]
            if (strlen(choice) != 2)
            

        }

        // A switch statement to execute code based on the user's 'choice'.
        switch (tolower(choice))
        {

        // If the choice is 'a', create a linear linked list.
        case 'a':
            // Calls the function to create the list.
            createList();
            // Exits the switch statement.
            break;

        // If the choice is 'b', display the linear linked list.
        case 'b':
            // Checks if the list is empty (if 'head' is NULL).
            if (head == NULL)
            {
                // Prompts the user to create a list first.
                printf("Please create a linear linked list first! (Option a)\n");
            }
            // If the list is not empty.
            else
            {
                // Calls the function to display the list's contents.
                displayList();
            }
            // Exits the switch statement.
            break;

        // If the choice is 'c', sort the list.
        case 'c':
            // Checks if the list is empty.
            if (head == NULL)
            {
                // Prompts the user to create a list first.
                printf("Please create a linear linked list first! (Option a)\n");
            }
            // If the list is not empty.
            else
            {
                // Calls the function to sort the list.
                sortList();
                // Informs the user that the sort is complete.
                printf("List sorted in ascending order! Check the updated list. (option b)\n");
            }
            // Exits the switch statement.
            break;

        // If the choice is 'd', search for a number.
        case 'd':
            // Checks if the list is empty.
            if (head == NULL)
            {
                // Prompts the user to create a list first.
                printf("Please create a linear linked list first! (Option a)\n");
            }
            // If the list is not empty.
            else
            {
                // Calls the function to search for a number.
                searchNumber();
            }
            // Exits the switch statement.
            break;

        // If the choice is 'e', exit the program.
        case 'e':
            // Prints a goodbye message.
            printf("Exiting the program...\n");
            // Terminates the program with a success code (0).
            return 0;

        // If the choice is none of the above.
        default:
            // Informs the user of an invalid choice.
            printf("Invalid choice! Please try again\n");
        } // End of the switch statement.
    } // End of the while loop.
} // End of the main function.

// This function creates a linked list based on user input.
void createList()
{
    // 'n' stores the number of elements, 'val' stores the value for each node.
    int n, val;
    // 'newNode' points to the newly created node, 'temp' is a utility pointer for accessing the nodes on the list.
    struct Node *newNode, *temp;
    // Checks if a list has already been created.
    if (head != NULL)
    {
        // Prevents overwriting an existing list.
        printf("You have already added a linked list! Restart the program to create a new one.\n");
        // Exits the function.
        return;
    }
    // A loop to ensure the user enters a valid number of elements.
    while (1)
    {
        // Prompts the user for the number of elements.
        printf("Enter how many elements you want: ");
        // Checks if the input is a single integer between 1 and 100.
        if (scanf("%d", &n) == 1 && n > 0 && n <= 100)
            // If valid, exit the validation loop.
            break;
        // If the input is invalid.
        else
        {
            // Prints an error message.
            printf("Invalid input! Please enter a positive number only. (up to 100)\n");
            // Clears the input buffer.
            while (getchar() != '\n');
        }
    } // End of the validation while loop.

    // Loops 'n' times to create 'n' nodes.
    for (int i = 0; i < n; i++)
    {
        // Allocates memory for one 'Node' structure. the *newNode now points to that new created node
        newNode = malloc(sizeof(struct Node));
        // Checks if memory allocation failed.
        if (newNode == NULL)
        {
            // Prints an error and exits the function if malloc fails.
            printf("Error! Memory not allocated!\n");
            return;
        }
        // A loop to get a valid integer value for the node.
        while (1)
        {
            // Prompts the user for the node's value.
            printf("Enter value for node %d: ", i + 1);
            // Checks if the input is a single integer.
            if (scanf("%d", &val) == 1)
                // If valid, exit the validation loop.
                break;
            // If the input is not a valid integer.
            else
            {
                // Prints an error message.
                printf("Invalid input! Please enter a number only.\n");
                // Clears the input buffer.
                while (getchar() != '\n');
            }
        } // End of the value validation loop.

        // Assigns the user's value to the new node's data field.
        newNode->data = val;
        // Sets the 'next' pointer of the new node to NULL, as it will be the last node for now.
        newNode->next = NULL;

        // Checks if this is the first node being added (i.e., the list is empty).
        if (head == NULL)
        {
            // If so, the 'head' pointer is made to point to this new node.
            head = newNode;
        }
        // If the list is not empty.
        else
        {
            // Start a temporary pointer at the beginning of the list.
            temp = head;
            // Traverse the list until the last node is reached (its 'next' will be NULL).
            while (temp->next != NULL)
                // Move the temporary pointer to the next node.
                temp = temp->next;
            // Link the last node's 'next' pointer to the new node.
            temp->next = newNode;
        }
    } // End of the for loop for creating nodes.

    // Clears the input buffer one last time to be safe.
    while (getchar() != '\n');
    // Informs the user that the list was created.
    printf("Linked list created successfully!\n");
} // End of the createList function.

// This function displays all the elements in the linked list.
void displayList()
{
    // Create a temporary pointer and start it at the head of the list.
    struct Node *temp = head;
    // Prints the start of the list display.
    printf("Linked List: ");
    // Loop as long as the temporary pointer is not NULL (hasn't reached the end).
    while (temp != NULL)
    {
        // Print the data of the current node (where *temp points), followed by an arrow.
        printf("%d -> ", temp->data);
        // Move the temporary pointer to the next node in the list.
        temp = temp->next;
    }
    // After the loop, print "NULL" to signify the end of the list.
    printf("NULL (End of list)\n");
} // End of the displayList function.

// This function sorts the list in ascending order using a bubble sort algorithm.
void sortList()
{
    // 'i' and 'j' are pointers used to iterate through the list for comparison.
    struct Node *i, *j;
    // 'temp' is an integer used for swapping data values.
    int temp;

    // The outer loop iterates through each node with pointer 'i'.
    for (i = head; i != NULL; i = i->next)
    {
        // The inner loop iterates through the nodes after 'i' with pointer 'j'.
        for (j = i->next; j != NULL; j = j->next)
        {
            // Compares the data of the two nodes.
            if (i->data > j->data)
            {
                // If i's data is greater than j's data, swap them.
                // Step 1: Store i's data in the temporary variable (int temp).
                temp = i->data;
                // Step 2: Copy j's data into i's data field.
                i->data = j->data;
                // Step 3: Copy the stored value from temp into j's data field.
                j->data = temp;
            }
        }
    }
    // This message is now in the main function to avoid confusion.
} // End of the sortList function.

// This function searches for a number in the list and reports its occurrences and positions.
void searchNumber()
{
    // 'num' stores the number to search for.
    int num;
    // 'choice' stores the user's decision to search again.
    char choice;

    // A do-while loop allows the user to perform multiple searches without returning to the main menu.
    do
    {
        // A validation loop to ensure the user enters a valid integer.
        while (1)
        {
            // Prompts the user for the number to search.
            printf("Enter number to search: ");
            // Checks if the input is a valid integer.
            if (scanf("%d", &num) == 1)
                // If valid, break out of the validation loop.
                break;
            // If the input is not a valid integer.
            else
            {
                // Prints an error message.
                printf("Invalid input! Must be an integer.\n");
                // Clears the input buffer.
                while (getchar() != '\n');
            }
        } // End of the validation loop.

        // 'temp' is a pointer to traverse the list, starting from the head.
        struct Node *temp = head;
        // 'index' tracks the position of each node (starting from 0).
        int index = 0;
        // 'foundCount' counts how many times the number is found.
        int foundCount = 0;
        // 'nodes' is an array to store the indices where the number is found (stores the given value of [int index]).
        int nodes[100];

        // Traverse the entire list.
        while (temp != NULL)
        {
            // Checks if the current node's data matches the search number.
            if (temp->data == num)
            {
                // If it matches, store the current index in the 'nodes' array (node[100]).
                nodes[foundCount] = index;
                // Increment the int foundCount to keep track how many were found.
                foundCount++;
            }
            // Move to the next node.
            temp = temp->next;
            // Increment the index for the next position.
            index++;
        } // End of the traversal loop.

        // Show result: Check if the number was found at least once.
        if (foundCount > 0)
        {
            // Prints how many times the number appeared, using a ternary operator for correct grammar ("time" or "times").
            printf("%d appeared %d %s in the list\n",
                   num, foundCount, (foundCount == 1 ? "time" : "times"));

            // Prints the header for the node positions, using a ternary operator for "Node" or "Nodes".
            printf("Found at %s", foundCount == 1 ? "Node" : "Nodes");
            // Loops through the found indices.
            for (int i = 0; i < foundCount; i++)
            {
                // Prints the node position (adding 1 because indices are 0-based[starts from 0]).
                printf(" %d", nodes[i] + 1);
                // Prints a comma and space if it's not the last found position. Prevents printing comma at the end of list.
                if (i != foundCount - 1)
                    printf(",");
            }
            // Prints a newline character at the end.
            printf("\n");
        }
        // If the number was not found (int foundCount == 0).
        else
        {
            // Informs the user that the number is not in the list.
            printf("%d is not in the list.\n", num);
        }

        // Asks if the user wants to repeat the search.
        printf("Do you want to search another number? (Y/N): ");
        // Reads the user's 'Y' or 'N' choice.
        scanf(" %c", &choice);
        // Clears the input buffer.
        while (getchar() != '\n');

    // The condition to continue the loop: if the user enters 'y' or 'Y'.
    } while (choice == 'y' || choice == 'Y');
} // End of the searchNumber function.
