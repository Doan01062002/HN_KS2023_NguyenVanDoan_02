#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DoublyLinkedList {
    Node* head;
    Node* tail;
} DoublyLinkedList;

void init(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void addToHead(DoublyLinkedList* list, int value) {
    Node* newNode = createNode(value);
    if (list->head == NULL) {
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    printf("->Da them %d vào dau danh sach<-\n", value);
}

void addToTail(DoublyLinkedList* list, int value) {
    Node* newNode = createNode(value);
    if (list->tail == NULL) {
        list->head = list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    printf("->Da them %d vao cuoi danh sach<-\n", value);
}

void insertAtPosition(DoublyLinkedList* list, int value, int position) {
    if (position < 0) {
        printf("->Vi tri khong hop le<-\n");
        return;
    }
    Node* newNode = createNode(value);
    if (position == 0) {
        addToHead(list, value);
        return;
    }

    Node* current = list->head;
    int index = 0;
    while (current != NULL && index < position - 1) {
        current = current->next;
        index++;
    }

    if (current == NULL) { 
        printf("->Vi tri vuot qua chieu dai danh sach<-\n");
        return;
    } else {
        newNode->next = current->next;
        if (current->next != NULL) {
            current->next->prev = newNode;
        }
        newNode->prev = current;
        current->next = newNode;
        if (newNode->next == NULL) {
            list->tail = newNode;
        }
        printf("->Da chen %d vao vi tri %d<-\n", value, position);
    }
}

void deleteFromHead(DoublyLinkedList* list) {
    if (list->head == NULL) {
        printf("->Danh sach rong, khong the xoa<-\n");
        return;
    }
    Node* temp = list->head;
    list->head = list->head->next;
    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    free(temp);
    printf("->Da xoa phan tu dau danh sach<-\n");
}

void deleteFromTail(DoublyLinkedList* list) {
    if (list->tail == NULL) {
        printf("->Danh sach rong, khong the xoa<-\n");
        return;
    }
    Node* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    free(temp);
    printf("->Da xoa phan tu cuoi danh sach<-\n");
}

void deleteByValue(DoublyLinkedList* list, int value) {
    Node* current = list->head;
    while (current != NULL && current->data != value) {
        current = current->next;
    }
    if (current == NULL) {
        printf("->Khong tim thay gia tri %d trong danh sach<-\n", value);
        return;
    }
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        list->tail = current->prev;
    }
    free(current);
    printf("->Da xoa gia tri %d khoi danh sach<-\n", value);
}

void traverseForward(DoublyLinkedList* list) {
    Node* current = list->head;
    printf("->Danh sach tu dau den cuoi: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("<-\n");
}

void traverseBackward(DoublyLinkedList* list) {
    Node* current = list->tail;
    printf("->Danh sach tu cuoi den dau: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("<-\n");
}

void menu() {
    DoublyLinkedList list;
    init(&list);
    int choice, value, position;

    do {
        printf("\n==================MENU=================\n");
        printf("1. Them phan tu vao dau danh sach\n");
        printf("2. Them phan tu vao cuoi danh sach\n");
        printf("3. Chen phan tu vao vi tri cu the\n");
        printf("4. Xoa phan tu dau danh sach\n");
        printf("5. Xoa phan tu cuoi danh sach\n");
        printf("6. Xoa phan tu theo gia tri\n");
        printf("7. Duyet danh sach tu dau den cuoi\n");
        printf("8. Duyet danh sach tu cuoi den dau\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Nhap gia tri: ");
                scanf("%d", &value);
                addToHead(&list, value);
                break;
            case 2:
                printf("Nhap gia tri: ");
                scanf("%d", &value);
                addToTail(&list, value);
                break;
            case 3:
                printf("Nhap gia tri: ");
                scanf("%d", &value);
                printf("Nhap vi tri: ");
                scanf("%d", &position);
                insertAtPosition(&list, value, position);
                break;
            case 4:
                deleteFromHead(&list);
                break;
            case 5:
                deleteFromTail(&list);
                break;
            case 6:
                printf("Nhap gia tri can xoa: ");
                scanf("%d", &value);
                deleteByValue(&list, value);
                break;
            case 7:
                traverseForward(&list);
                break;
            case 8:
                traverseBackward(&list);
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("->Lua chon khong hop le<-\n");
        }
    } while (choice != 9);
}

int main() {
    menu();
    return 0;
}

