#include<stdio.h>
#include<stdlib.h>

#define SIZE 6

/* *********************************************** Declarations + structs ************************************************/

// Define struct for client registration
struct enregist_client {
    int ID;
    float T_arrival, T_service, T_start;
};

// Define struct for event
struct Event {
    int type;
    float time;
    struct Event* next;
};

// Function prototypes
struct Event* createNode(int type, float time);
void enQueue(struct enregist_client*);
void deQueue();
void display();
void Schedual_event(struct Event** headRef, int type, float time);
void printList(struct Event* head);
void Init();
void P_arrival();
void Pstart_service();
void P_Departure();
struct Event* Get_Event();
void Stats();

// Global variables
struct enregist_client items[SIZE];
struct Event* head = NULL;
int front = -1, rear = -1;
float Tnow;
int server;
float T_start;
float T_arrival, TService, Mean_response, Mean_WaintingTime;
int Served_client;

/* ****************************************** QUEUE PROCEDURES for client registration ***************************************************/

// Function to create a new node
struct Event* createNode(int type, float time) {
    struct Event* newNode = (struct Event*)malloc(sizeof(struct Event));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->type = type;
    newNode->time = time;
    newNode->next = NULL;
    return newNode;
}

// Function to enqueue a client
void enQueue(struct enregist_client* Client) {
    if (rear == SIZE - 1)
        printf("\n");
    else {
        if (front == -1)
            front = 0;
        rear++;
        items[rear] = *Client;
    }
}

// Function to dequeue a client
void deQueue() {
    if (front == -1)
        printf("\nQueue is Empty!!");
    else {
        printf("\nDeleted : %d", items[front].ID);
        front++;
        if (front > rear)
            front = rear = -1;
    }
}

// Function to display the queue
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
        printf("__________________________________________\n");
    }
}

// Function to schedule an event
void Schedual_event(struct Event** headRef, int type, float time) {
    struct Event* newNode = createNode(type, time);
    newNode->next = *headRef;
    *headRef = newNode;
}

// Function to print the elements of the event list
void printList(struct Event* head) {
    printf("\n[TEST NODES >>>>>>>  EVENTS ENREGISTRE] \n");
    struct Event* temp = head;
    while (temp != NULL) {
        printf("\ntype : %d ", temp->type);
        printf("time : %f ", temp->time);
        temp = temp->next;
    }
    printf("\n");
}

// Function to initialize simulation parameters
void Init() {
    printf("\n >>>>>>>>>   INIT TEST \n");
    Tnow = 0;
    server = 0;
    T_arrival = 6;
    TService = 5;
    Schedual_event(&head, 1, Tnow);
    printList(head);
}

/* _________________________________ Main work _____________________________________________________________*/

// Function for client arrival event
void P_arrival() {
    struct enregist_client Client;
    printf("\n >>>>>>>>>   P ARRIVAL TIME \n");
    Client.T_arrival = T_arrival;
    Client.T_service = TService;
    Client.ID = Served_client;
    Client.T_start = T_start;
    enQueue(&Client);
    if (server == 0) {
        Schedual_event(&head, 2, Tnow + T_arrival);
        printf("event 2 registered \n");
    }
    else {
        Schedual_event(&head, 1, Tnow);
        printf("event 1 registered \n");
    }
    
   
}

// Function for starting service event
void Pstart_service() {
    printf("\n >>>>>>>>>   Start service TIME \n");
    server = 1;
    items[front].T_start = Tnow;

    Schedual_event(&head, 3, Tnow + items[front].T_service);
}

// Function for client departure event
void P_Departure() {
    printf("\n >>>>>>>>>   P DEPARTURE TIME \n");
    server = 0;
    Mean_response = Mean_response + (Tnow + items[front].T_arrival);
    Mean_WaintingTime = Mean_WaintingTime + (items[front].T_start - items[front].T_arrival);
    deQueue();

    if (front != -1) {
        Schedual_event(&head, 2, Tnow);
    }
    Served_client = Served_client + 1;
    printf("c served :%d\n", Served_client);
    head ->next;
}

// Function to get the next event
struct Event* Get_Event() {
    struct Event* temp = head;
    if (temp != NULL) {
        printf("DEBUG: Event fetched - Type: %d, Time: %f\n", temp->type, temp->time); // Debug print
        
    } else {
        printf("DEBUG: No events in the list\n"); // Debug print
    }
    
    
    return temp;
}

// Function to calculate and print statistics
void Stats() {
    printf("\nMean response TIME >>> %f\n", Mean_response / Served_client);
    printf("\nMean Waiting  TIME >>> %f\n", Mean_WaintingTime / Served_client);
    printf("\nThroughput >>> %f\n", Served_client / Tnow);
}

/* __________________________________________END OF MAIN ___________________________________________________*/

int main() {
    int type;
    printf("Simulation complete.\n");
    Init();
    
    
    while (Served_client <= 2) {
        struct Event* temp = Get_Event();
        Tnow = temp->time;
        type = temp->type;
        printf("TEST TNOW: %f, Type: %d\n", Tnow, type);
        P_arrival();
        switch (type) {
        case 1:
            P_arrival();
           
            break;
        case 2:
            Pstart_service();
           
            break;
        case 3:
            P_Departure();
            
            break;
        }
       
    }
    // Calculate and print statistics
    Stats();
    printf("Simulation complete.\n");
    return 0;
}
