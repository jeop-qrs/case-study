// For printf(), scanf(), etc. - Includes the standard input/output library for console operations.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_NODES 100
#define MAX_INPUT 256


struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void createList();
void freeList();
void appendList();
void displayList();
void sortList();
void searchNumber();

int main() {
    char choice[MAX_INPUT];
    while (1) {
        printf("\n===== MAIN MENU =====\n");
        printf("(a) Create a Linear Linked List\n");
        printf("(b) Display a Linear Linked List\n");
        printf("(c) Sort a Linear Linked List - Ascending\n");
        printf("(d) Search a number\n");
        printf("(e) Exit\n");
        while (1) {
            printf("Enter choice: ");
            if (fgets(choice, sizeof(choice), stdin) == NULL) {
                printf("Input error! Try again.\n");
                continue;
            }
            choice[strcspn(choice, "\n")] = '\0';
            if (strlen(choice) != 1) {
                printf("Invalid input! Please only enter one character (a-z)\n");
                continue;
            }
            if (!isalpha(choice[0])) {
                printf("Invalid input! Please enter a valid alphabetic letter (a-z)\n");
                continue;
            }
            break;
        }
        switch (tolower(choice[0])) {
            case 'a': createList(); break;
            case 'b':
                if (head == NULL)
                    printf("Please create a linear linked list first! (Option a)\n");
                else
                    displayList();
                break;
            case 'c':
                if (head == NULL)
                    printf("Please create a linear linked list first! (Option a)\n");
                else {
                    sortList();
                    printf("List sorted in ascending order! Check the updated list. (option b)\n");
                }
                break;
            case 'd':
                if (head == NULL)
                    printf("Please create a linear linked list first! (Option a)\n");
                else
                    searchNumber();
                break;
            case 'e':
                printf("Exiting the program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again\n");
        }
    }
}

void freeList() {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    head = NULL;
    printf("Memory freed. The list is now empty.\n");
}

void appendList() {
    int n, val;
    struct Node *newNode, *temp = head;
    int i = 1;

    while (temp->next != NULL) {
        temp = temp->next;
        i++;
    }
    i++;

    while (1) {
        printf("Enter how many elements you want to append: ");
        if (scanf("%d", &n) == 1 && n > 0 && n <= (MAX_NODES - i))
            break;
        else {
            printf("Invalid input! Please enter a positive number only. (up to %d)\n", MAX_NODES - i);
            while (getchar() != '\n');
        }
    }

    for (int j = 0; j < n; j++) {
        newNode = malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Error! Memory not allocated!\n");
            return;
        }
        while (1) {
            printf("Enter value for node %d: ", i);
            if (scanf("%d", &val) == 1)
                break;
            else {
                printf("Invalid input! Please enter a number only.\n");
                while (getchar() != '\n');
            }
        }
        newNode->data = val;
        newNode->next = NULL;
        temp->next = newNode;
        temp = newNode;
        i++;
    }
    while (getchar() != '\n');
    printf("List appended successfully!\n");
}

void createList() {
    int n, val;
    char choice[MAX_NODES];
    struct Node *newNode, *temp;
    if (head != NULL) {
        printf("There is already existing linked list!\n");
        printf("Choose the options below:\n");
        printf("(a) Rewrite the whole linked list\n");
        printf("(b) Append on the existing linked list\n");
        printf("(c) Return to Main Menu\n");
        while (1) {
            printf("Enter choice: ");
            if (fgets(choice, sizeof(choice), stdin) == NULL) {
                printf("Input error! Try again.\n");
                continue;
            }
            choice[strcspn(choice, "\n")] = '\0';
            if (strlen(choice) != 1 || !isalpha(choice[0])) {
                printf("Invalid input! Please only enter one character (a-z)\n");
                continue;
            }
            break;
        }
        switch (tolower(choice[0])) {
            case 'a': freeList(); break;
            case 'b': appendList(); return;
            case 'c': return;
            default: printf("Invalid choice! Please try again.\n"); return;
        }
    }
input_nodes:
    while (1) {
        printf("Enter how many elements you want: ");
        if (scanf("%d", &n) == 1 && n > 0 && n <= MAX_NODES)
            break;
        else {
            printf("Invalid input! Please enter a positive number only. (1 to %d)\n", MAX_NODES);
            while (getchar() != '\n');
        }
    }
    for (int i = 0; i < n; i++) {
        newNode = malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Error! Memory not allocated!\n");
            return;
        }
        while (1) {
            printf("Enter value for node %d: ", i + 1);
            if (scanf("%d", &val) == 1)
                break;
            else {
                printf("Invalid input! Please enter a number only.\n");
                while (getchar() != '\n');
            }
        }
        newNode->data = val;
        newNode->next = NULL;
        if (head == NULL)
            head = newNode;
        else {
            temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }
    while (getchar() != '\n');
    printf("Linked list created successfully!\n");
}

void displayList() {
    struct Node *temp = head;
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL (End of list)\n");
}

void sortList() {
    struct Node *i, *j;
    int temp;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

void searchNumber() {
    int num;
    char choice;
    do {
        while (1) {
            printf("Enter number to search: ");
            if (scanf("%d", &num) == 1) break;
            else {
                printf("Invalid input! Must be an integer.\n");
                while (getchar() != '\n');
            }
        }
        struct Node *temp = head;
        int index = 0, foundCount = 0;
        int nodes[MAX_NODES];
        while (temp != NULL) {
            if (temp->data == num) {
                nodes[foundCount] = index;
                foundCount++;
            }
            temp = temp->next;
            index++;
        }
        if (foundCount > 0) {
            printf("%d appeared %d %s in the list\n", num, foundCount, (foundCount == 1 ? "time" : "times"));
            printf("Found at %s", foundCount == 1 ? "Node" : "Nodes");
            for (int i = 0; i < foundCount; i++) {
                printf(" %d", nodes[i] + 1);
                if (i != foundCount - 1) printf(",");
            }
            printf("\n");
        } else {
            printf("%d is not in the list.\n", num);
        }
        printf("Do you want to search another number? (Y/N): ");
        scanf(" %c", &choice);
        while (getchar() != '\n');
    } while (choice == 'y' || choice == 'Y');
}
