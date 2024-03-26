#include<stdio.h>

#define SIZE 5

/* ***********************************************Declarations + structs ************************************************/

struct enregist_client {
    int ID;
    float T_arrival , T_service, T_start;
}enregist_client;

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }  newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enQueue(struct enregist_client*);
void deQueue();
void display();


struct enregist_client items[SIZE];

int front = -1, rear = -1;
int Tnow = 0, TService = 2;

/* ///////////////////////////////////////////END OF DECLARATIONS ///////////////////////////////////////////////////*/


/* ****************************************** QUEUE PROCEDURES for client enregistrement ***************************************************/

void enQueue(struct enregist_client *Client) {
  if (rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else {
    if (front == -1)
      front = 0;
    rear++;
    items[rear] = *Client;
    printf("\nInserted -> %d", Client);
  }
}


void deQueue() {
  if (front == -1)
    printf("\nQueue is Empty!!");
  else {
    printf("\nDeleted : %d", items[front]);
    front++;
    if (front > rear)
      front = rear = -1;
  }
}

void display() {
    if (front == -1)
        printf("\nQueue is Empty!!");
    else {
        printf("\nQueue elements: ");
        for (int i = front; i <= rear; i++) {
            printf(" Id >>  %d ", items[i].ID);
            printf("Arrival >>  %f ", items[i].T_arrival);
            printf("Service >>  %f ", items[i].T_service);
            printf("Start >>  %f ", items[i].T_start);
        }
    }
}

void insertAtBeginning(struct Node** headRef, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *headRef;
    *headRef = newNode;
}




// Function to print the elements of the list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


/* ///////////////////////////////END OF QUEUE PROCEDURES //////////////////////////////////////////////////// */


/* ___________________________________Main work _____________________________________________________________*/
void P_arrival(){
    struct enregist_client Client;
    Client.T_arrival = Tnow;
    Client.T_service = TService;
    

}

/* __________________________________________END OF MAIN ___________________________________________________*/

int main() {

    printf("[TEST QUEUE >>>>>>>  CLIENTS ENREGISTRE] \n");

    struct enregist_client client1 = {1, 10.0, 2.0, 0.0};
    struct enregist_client client2 = {2, 12.0, 3.0, 0.0};
    struct enregist_client client3 = {3, 15.0, 1.0, 0.0};


    printf("Enqueuing clients...\n");
    enQueue(&client1);
    enQueue(&client2);
    enQueue(&client3);

    display();


    printf("[TEST NODES >>>>>>>  EVENTS ENREGISTRE] \n");

   struct Node* head = NULL;

    // Insert some elements into the list
    insertAtBeginning(&head, 3);
    insertAtBeginning(&head, 7);
    insertAtBeginning(&head, 11);

    // Print the elements of the list
    printf("List: ");
    printList(head);

    return 0;
}