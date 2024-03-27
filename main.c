#include<stdio.h>

#define SIZE 5

/* ***********************************************Declarations + structs ************************************************/

struct enregist_client {
    int ID;
    float T_arrival , T_service, T_start;
}enregist_client;



struct Event {
    int type;
    float time;
    struct Event* next;
};

struct Event* createNode(int type, float time) {
    struct Event* newNode = (struct Event*)malloc(sizeof(struct Event));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }  newNode->type = type;
      newNode ->time = time;
    newNode->next = NULL;
    return newNode;
}

void enQueue(struct enregist_client*);
void deQueue();
void display();


struct enregist_client items[SIZE];

int front = -1, rear = -1;
int Tnow = 0, TService = 2, T_start, T_arrival;
int server = 0, num = 0;

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
    printf("\nInserted -> %d\n", Client);
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
       
        for (int i = front; i <= rear; i++) {
            printf("__________________________________________\n");
            printf("Id >>  %d \n", items[i].ID);
            printf("Arrival >>  %f \n", items[i].T_arrival);
            printf("Service >>  %f \n", items[i].T_service);
            printf("Start >>  %f \n", items[i].T_start);
            

        }
    }
}

void insertAtBeguinning_Event(struct Event** headRef, int type, float time) {
    struct Event* newNode = createNode(type, time);
    newNode->next = *headRef;
    *headRef = newNode;
}




// Function to print the elements of the list
void printList(struct Event* head) {
    struct Event* temp = head;
    while (temp != NULL) {
        printf("\ntype : %d ", temp->type);
        printf("time : %f ", temp->time);
        temp = temp->next;
    }
    printf("\n");
}


/* ///////////////////////////////END OF QUEUE PROCEDURES //////////////////////////////////////////////////// */


/* ___________________________________Main work _____________________________________________________________*/
void P_arrival(){
    struct enregist_client Client;
    struct Event* head = NULL;


    /*Client enters the queue */

    Client.T_arrival = Tnow;
    Client.T_service = TService;
    Client.ID = num;
    Client.T_start = T_start;

    enQueue(&Client);


    /*Event Creation*/
    /*Type of event 1: arrival , 2: start , 3: end*/
    if(server == 0){

    insertAtBeguinning_Event(&head, 2, Tnow+T_arrival);

    }
    
    
    insertAtBeguinning_Event(&head, 1, Tnow);

    num = num +1;
 
}

/* __________________________________________END OF MAIN ___________________________________________________*/

int main() {

    printf("[TEST QUEUE >>>>>>>  CLIENTS ENREGISTRE] \n");

    struct enregist_client client1 = {1, 10.0, 2.0, 0.0};
    P_arrival();

    printf("Enqueuing clients...\n");
    enQueue(&client1);
    

    display();


    printf("\n[TEST NODES >>>>>>>  EVENTS ENREGISTRE] \n");

    struct Event* head2 = NULL;

    // Insert some elements into the list
    //insertAtBeguinning_Event(&head, 1, 0.13);
    

    // Print the elements of the list
    printf("List: ");
    printList(head2);

    return 0;
}