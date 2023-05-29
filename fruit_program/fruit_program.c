#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element[20];  

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    strcpy(p->data, value);
    p->link = head;
    head = p;
    return head;
}

ListNode* search_list(ListNode* head, element value) {
    ListNode* p = head;
    while (p != NULL) {
        if (strcmp(p->data, value) == 0)
            return p;
        p = p->link;
    }
    return NULL;
}


ListNode* delete(ListNode* head, ListNode* prev, ListNode* target) {
    if (prev == NULL)
        head = target->link;
    else
        prev->link = target->link;
    free(target);
    return head;
}

void print_fruits(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%s -> ", p->data);
    printf("NULL\n");
}

void print_deleted_fruits(ListNode* deleted_list) {
    if (deleted_list == NULL) {
        printf(" NULL\n");
        return;
    }
    for (ListNode* p = deleted_list; p != NULL; p = p->link) {
        printf(" %s ->", p->data);
    }
    printf(" NULL\n");
    
}
ListNode* insert_last(ListNode* head, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    strcpy(p->data, value);
    p->link = NULL;

    if (head == NULL) {
        head = p;
    }
    else {
        ListNode* curr = head;
        while (curr->link != NULL) {
            curr = curr->link;
        }
        curr->link = p;
    }

    return head;
}
int main(void) {
    ListNode* head = NULL;  
    ListNode* deleted_list = NULL;  

    char initial_fruits[][20] = {
        "Mango", "Orange", "Apple", "Grape", "Cherry",
        "Plum", "Guava", "Raspberry", "Banana", "Peach"
    };
    int initial_fruits_count = sizeof(initial_fruits) / sizeof(initial_fruits[0]);

    
    for (int i = initial_fruits_count - 1; i >= 0; i--)
        head = insert_first(head, initial_fruits[i]);

    int choice;
    char fruit[20];

    while (1) {
        printf("1. Insert new fruit\n");
        printf("2. Delete the fruit\n");
        printf("3. Print the deleted fruits\n");
        printf("4. Exit\n");
        printf("Enter the menu: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter the fruit name: ");
            scanf("%s", fruit);

            if (search_list(head, fruit) != NULL) {
                printf("The fruit already exists.\n");
            }
            else {
                head = insert_last(head, fruit);
                printf("%s has been added.\n", fruit);
            }
            printf("\n");
            print_fruits(head);
            break;
        case 2:
            printf("Enter the fruit name: ");
            scanf("%s", fruit);

            ListNode* prev = NULL;
            ListNode* current = head;
            ListNode* target = search_list(head, fruit);
            while (current != NULL && current != target) {
                prev = current;
                current = current->link;
            }

            if (target != NULL) {
                head = delete(head, prev, target);
                deleted_list = insert_last(deleted_list, fruit);
                printf("%s has been deleted.\n", fruit);
            }
            else {
                printf("%s is not on the list.\n", fruit);
            }
            printf("\n");
            printf("Fruit list:\n");
            print_fruits(head);
            break;
        case 3:
            printf("List of deleted fruits:");
            print_deleted_fruits(deleted_list);
            printf("\n");
            printf("Fruit list:\n");
            print_fruits(head);
            printf("\n");
            break;
        case 4:
            printf("Exiting the program.\n");
            while (head != NULL) {
                ListNode* temp = head;
                head = head->link;
                free(temp);
            }
            while (deleted_list != NULL) {
                ListNode* temp = deleted_list;
                deleted_list = deleted_list->link;
                free(temp);
            }
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}
