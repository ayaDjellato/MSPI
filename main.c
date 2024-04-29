#include<stdio.h>
#include<stdlib.h>

#define SIZE 6

/* *********************************************** Declarations + structs ************************************************/

// Define struct for client registration
typedef struct enregist_client {
    int ID;
    float T_arrival, T_service, T_start;
    struct enregist_client *next;


}enregist_client;

// Define struct for event
typedef struct Event {
    int type;
    float time;
    struct Event* next;
}Event;


// Global variables
struct enregist_client items[SIZE];
int server;
float T_start, Tnow;
float T_arrival, TService, Mean_response, Mean_WaintingTime;
int Served_client;


enregist_client *ClientQueue, *currentclient;
Event *EventList, *currentevent;

/* ****************************************** QUEUE PROCEDURES for client registration ***************************************************/

// Function to create a new node
void addevent( Event *ev) {
    if (EventList == NULL || (EventList)->time >= ev->time) {
        ev->next = EventList;
        EventList = ev;
    } else {
        Event *current = EventList;
        while (current->next && (current->next->time < ev->time)) {
            current = current->next;
        }
        ev->next = current->next;
        current->next = ev;
    }
}

// Function to enqueue a client
void addclient(enregist_client **cl ) {
    if (ClientQueue == NULL) {
        ClientQueue = *cl;
    } else {
        enregist_client *current = ClientQueue;
        while (current->next!=NULL) {
            current = current->next;
        }
        current->next = *cl;

    }
}

void CreateClient(int Served,float T_arrival,float ts,float start) {
    enregist_client *Client = (enregist_client *) malloc(sizeof(enregist_client));
    Client->T_arrival = T_arrival;
    Client->T_service = ts;
    Client->ID = Served;
    Client->T_start = start;
    Client->next = NULL;
    addclient(&Client);

    
}
enregist_client *getclient() {
    enregist_client *current = ClientQueue;
    ClientQueue = ClientQueue->next;
    return current;
}



// Function to schedule an event
void Schedual_event(int type, float time) {
    Event *ev = (Event *) malloc(sizeof(Event));
    ev->type = type;
    ev->time = time;
    ev->next = NULL;
    addevent(ev);
}

// Function to print the elements of the event list
void printList(struct Event* head) {
    //printf("\n[TEST NODES >>>>>>>  EVENTS ENREGISTRE] \n");
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
    //printf("\n >>>>>>>>>   INIT TEST \n");
    Tnow = 0;
    server = 0;
    T_arrival = 5;
    TService = 25;
   
    
    ClientQueue = NULL;
    EventList = NULL;
   Schedual_event( 1, Tnow); 
   Mean_WaintingTime = 0;
    Mean_response = 0;
}

/* _________________________________ Main work _____________________________________________________________*/

// Function for client arrival event
void P_arrival() {
   

    CreateClient(Served_client,Tnow,TService,T_start);


    if (server == 0) {
        Schedual_event(2, Tnow );
        //printf("event 2 registered \n");
    }
 
        Schedual_event( 1, Tnow + T_arrival);
        //printf("event 1 registered \n");
    
   
}

// Function for starting service event
void Pstart_service() {
    //printf("\n >>>>>>>>>   Start service TIME \n");
    server = 1;
    currentclient = getclient();
    currentclient->T_start = Tnow;

    Schedual_event( 3, Tnow + currentclient->T_service);
   
}

// Function for client departure event
void P_Departure() {
    //printf("\n >>>>>>>>>   P DEPARTURE TIME \n");
    server = 0;
    Mean_response = Mean_response + (Tnow - currentclient->T_arrival);
    Mean_WaintingTime = Mean_WaintingTime + (currentclient->T_start - currentclient->T_arrival);
     //printf("\n %f Mean response TIME >>> %f\n", currentclient->T_arrival,  Mean_response);
    // printf("\n %f Mean Waiting  TIME >>> %f\n",currentclient->T_start, Mean_WaintingTime);

    Served_client = Served_client + 1;
    free(currentclient);
    if (ClientQueue != NULL) {
        Schedual_event( 2, Tnow);
    }
    
    //printf("c served :%d\n", Served_client);  
    
  

    
}

// Function to get the next event
struct Event* Get_Event() {
    Event *current = EventList;
    EventList = EventList->next;
    return current;
}

// Function to calculate and print statistics
void Stats() {
    printf("\nMean response TIME >>> %f\n", Mean_response / Served_client);
    printf("\nMean Waiting  TIME >>> %f\n", Mean_WaintingTime / Served_client);
    printf("\nThroughput >>> %f\n", Served_client / Tnow);

 
 
 } 
 ;

/* __________________________________________END OF MAIN ___________________________________________________*/

int main() {
    int type;
    printf("Simulation complete.\n");
    Init();
    
    
    while (Served_client <= 1000) {
        currentevent = Get_Event();
        Tnow = currentevent->time;
        type = currentevent->type;
        //printf("TEST TNOW: %f, Type: %d\n", Tnow, type);
      
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