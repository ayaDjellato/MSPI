#include<stdio.h>
#include <stdlib.h>

#define SIZE 6

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
struct Event* head = NULL;


// system vars
int front = -1, rear = -1;
int Tnow;
// 0: idle 1: active
int server = 0;
int T_start;

// Workload for 
int T_arrival, TService;

//stats
int Served_client , Mean_response, Mean_WaintingTime;


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

        printf("__________________________________________\n");
    }
}

void Schedual_event(struct Event** headRef, int type, float time) {
    struct Event* newNode = createNode(type, time);
    newNode->next = *headRef;
    *headRef = newNode;
}




// Function to print the elements of the list
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


void Init(){

printf("\n >>>>>>>>>   INIT TEST \n");

// system vars
Tnow = 0;
// 0: idle 1: active
server = 0;


// Workload for D/D/1
T_arrival = 6;
TService = 5;

Schedual_event(&head, 1, Tnow);}

/* ///////////////////////////////END OF QUEUE PROCEDURES //////////////////////////////////////////////////// */


/* ___________________________________Main work _____________________________________________________________*/


int num = 0;

void P_arrival(){
    struct enregist_client Client;
    
    printf("\n >>>>>>>>>   P ARRIVAL TIME /\n");
    printf("[TEST QUEUE >>>>>>>  CLIENTS ENREGISTRE] \n");

    /*Client enters the queue */
    Client.T_arrival = T_arrival;
    Client.T_service = TService;
    Client.ID = num;
    Client.T_start = T_start;

    enQueue(&Client);
    display();

    /*Event Creation*/
    /*Type of event 1: arrival , 2: start , 3: end*/
    if(server == 0){
   
          Schedual_event(&head, 2, Tnow+T_arrival);

    }else { 

    Schedual_event(&head, 1, Tnow);}

    //printList(head);

    num = num +1;
 
}

void Pstart_service(){

    printf("\n >>>>>>>>>   Start service TIME \n");

    server = 1;
    items[front].T_start = Tnow;
    printf("test TNOW : %f", Tnow);

    Schedual_event(&head, 3, Tnow+items[front].T_service);

    printList(head);

}

void P_Departure(){


  //printf("/n >>>>>>>>>   P DEPARTURE TIME /n");
  server = 0;
  Mean_response = Mean_response + (Tnow + items[front].T_arrival);
  Mean_WaintingTime = Mean_WaintingTime + (items[front].T_start - items[front].T_arrival);
  

  deQueue();

  if (front != -1)
  {
    Schedual_event(&head, 2, Tnow);
  }
  

  Served_client = Served_client + 1;
  printList(head);
  printf("c served :%d\n", Served_client);
  printf("TNOW  %d\n", Tnow);
  display();


}


void Get_Event(){
    struct Event* temp = head;
    float min = 100;

    while (temp != NULL) {
        if (min >= temp->time) {
            min = temp->time;
        }
        temp = temp->next;
    }

    printf("\nminimum time event %f\n", min);
}


void Stats(){

  printf("\nMean responce TIME >>> %f\n", Mean_response/Served_client);
  printf("\nMean Wainting  TIME >>> %f\n", Mean_WaintingTime/Served_client);
  printf("\nThroughput >>> %f\n", Served_client/Tnow);


}

/* __________________________________________END OF MAIN ___________________________________________________*/

int main() {

  printf("Starting simulation...\n");
    
    // Initialize simulation
    Init();

    P_arrival();
    Pstart_service();
    P_Departure();
    //Stats();

    // Run simulation loop
    /*
    while (Served_client <= 3) {
        Get_Event();
        Tnow = head->time;
        int type = head->type;

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
    Stats();*/
    
    printf("Simulation complete.\n");

    return 0;
}