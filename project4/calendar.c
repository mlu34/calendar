/* Michelle Lu, 117800524, mlu34 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calendar.h"


/* This function initializes a Calendar struct based on the parameters provided.
The function allocates memory for the following items: 
a) Calender struct
b) name field is assigned memory necessary to store a copy of the name
paremeter. The name represents the calendar's name.
c) events field is assigned memory necessary to represent an array of pointers
to Event structs. The size of this array corresponds to the days parameter.
The out parameter calendar provides access to the new Calendar struct. The total
number of events is set to zero. 
The function returns FAILURE if calendar and/or name are NULL, if the number of 
days is less than 1, or if any memory allocation fails. Otherwise the function 
returns SUCCESS. */
int init_calendar(const char *name, int days, 
int (*comp_func) (const void *ptr1, const void *ptr2), 
void (*free_info_func) (void *ptr), Calendar ** calendar){
    Calendar *cp;
    
    if(!calendar || !name || days < 1){
        return FAILURE;
    }
    cp = malloc(sizeof(Calendar));
    
    if(cp){ /* memory allocation for cp didn't fail */
        cp->name = malloc(strlen(name) + 1);
        cp->events = calloc(days, sizeof(Event));
    }else{ /* returns FAILURE if memory allocation for cp fails */
        free(cp);
        return FAILURE;
    }

    if(!cp->name || !cp->events){
        free(cp->name);
        free(cp->events);
        free(cp);
        return FAILURE;
    }
    
    /* Initializing the calendar */
    strcpy(cp->name, name);
    cp->total_events = 0;
    cp->days = days;
    cp->comp_func = comp_func;
    cp->free_info_func = free_info_func;
    
    *calendar = cp;
    return SUCCESS;
}

/* This function prints, to the designated output stream, the calendar's name,
days, and total number of events if print_all is true; otherwise this 
information is not printed. Information about each event (name, start time, and
duration) is printed regardless the value of print_all. 
This function returns FAILURE if calendar and/or output_stream are NULL; 
otherwise the function returns SUCCESS. */
int print_calendar(Calendar *calendar, FILE *output_stream, int print_all){
    Event *curr;
    int i;
    
    if(!calendar || !output_stream){
        return FAILURE;
    }
    
    /* If print_all is true, prints calendar's name, days, and total events */
    if(print_all){
        fprintf(output_stream, "Calendar's Name: \"%s\"\n", calendar->name);
        fprintf(output_stream, "Days: %d\n", calendar->days);
        fprintf(output_stream, "Total Events: %d\n", calendar->total_events);
    }
    
    /* Prints information about each event */
    fputs("\n**** Events ****\n", output_stream);
    if(calendar->total_events != 0){
        curr = *(calendar->events);
        for(i = 0; i < calendar->days; i++){
            fprintf(output_stream, "Day %d\n", i + 1);
            
            while(curr){
                fprintf(output_stream, "Event's Name: \"%s\", ", curr->name);
                fprintf(output_stream, "Start_time: %d, ", curr->start_time);
                fprintf(output_stream, "Duration: %d\n",curr->duration_minutes);
                curr = curr->next;
            }
            curr = *(calendar->events + i + 1);
        }
    }
    return SUCCESS;
}

/* This function adds the specified event to the list associated with the day 
parameter. The event is added in increasing sorted order using the comparison
function (comp_func) that allows comparison of two events. The function 
allocates memory for the new event and for the event's name. Other fields of the
event struct are initialized based on the parameter values. 
This function returns FAILURE if calendar and/or name are NULL, start time is 
invalid (must be a value between 0 and 2400, inclusive), duration_minutes is 
less than or equal to 0, day is less than 1 or greater than the number of 
calendar days, if the event already exist, or if any memory allocation fails. 
Otherwise the function will return SUCCESS. */
int add_event(Calendar *calendar, const char *name, int start_time, 
int duration_minutes, void *info, int day){
    Event *curr, *prev, *event_to_add, *temp, **head;
    
    if(!calendar || !name || start_time < 0 || start_time > 2400 || 
    duration_minutes <= 0 || day < 1 || day > calendar->days || 
    find_event(calendar, name, &temp) == SUCCESS){
        return FAILURE;
    }
    /* checking for failing memory allocation */
    if(!(event_to_add = malloc(sizeof(Event)))){
        free(event_to_add);
        return FAILURE;
        
    }else if(!(event_to_add->name = malloc(strlen(name) + 1))){
        free(event_to_add->name);
        free(event_to_add);
        return FAILURE;
        
    }else{ /* initializing the event */
        strcpy(event_to_add->name, name);
        event_to_add->start_time = start_time;
        event_to_add->duration_minutes = duration_minutes;
        event_to_add->info = info;
    }
    head = (calendar->events + day - 1);
    curr = *head;
    prev = NULL;
    
    while(curr && calendar->comp_func(event_to_add, curr) > 0){
        prev = curr;
        curr = curr->next;
    }
    event_to_add->next = curr;
    
    if(!prev){ /* insert at head */
        *head = event_to_add;
    }else{ /* insert in between */
        prev->next = event_to_add;
    }
    calendar->total_events++;
    
    return SUCCESS;        
}

/* This function returns a pointer (via the out parameter event) to the event
with the specified name (if any). If the event parameter is NULL, no pointer
is returned. Notice the out parameter should not be modified unless the event
is found. 
The function returns FAILURE if calendar or name are NULL. The function returns
SUCCESS if the event was found and FAILURE otherwise. */ 
int find_event(Calendar *calendar, const char *name, Event **event){
    Event *temp_event;
    int i;

    if(!calendar || !name){
        return FAILURE;
    }
    
    for(i = 0; i < calendar->days; i++){ /* iterates through the days */
        if(find_event_in_day(calendar, name, i + 1, &temp_event) == SUCCESS){
            if(event){ /* assigns event if event is not NULL */
                *event = temp_event;
            }
            break;
        }
    }
    if(i < calendar->days){
        return SUCCESS;
    }
    return FAILURE;
}

/* This function returns a pointer (via the out parameter event) to the event
with the specified name in the specified day (if such event exists). If the 
event parameter is NULL, no pointer is returned. Notice the out parameter event
should not be modified unless the event is found. 
The function returns FAILURE if calendar or name are NULL, or if the day 
parameter is less than 1 or greater than the number of calendar days. The 
function returns SUCCESS if the event is found and FAILURE otherwise. */
int find_event_in_day(Calendar *calendar, const char *name, int day, 
Event **event){
    Event *curr, **head;
    
    if(!calendar || !name || day < 1 || day > calendar->days){
        return FAILURE;
    }
    head = (calendar->events) + day - 1;
    curr = *head;
    
    while(curr){ /* iterates through the events on the specified day */
        if(strcmp(name, curr->name) == 0){ /* comparing event names */
            if(event){
                *event = curr;
            }
            return SUCCESS;
        }
        curr = curr->next;
    }
    return FAILURE;             
}


/* This function removes the specified event from the calendar, returning any
memory allocated for the event. If the event has an info field other than NULL
and a free_info_func exists, the function is called on the info field. The 
number of calendar events is adjusted accordingly. 
This function returns FAILURE if calendar or name are NULL, or if the event
cannot be found; otherwise the function returns SUCCESS. */
int remove_event(Calendar *calendar, const char *name){
    Event *event_to_remove, *curr, **head, *prev = NULL;
    int i;

    if(!calendar || !name){
        return FAILURE;
    }
    head = calendar->events;
    curr = *head;

    if(find_event(calendar, name, &event_to_remove) == SUCCESS){ /*event found*/
        for(i = 0; i < calendar->days; i++){ /* iterating through every day */
            head = (calendar->events + i + 1);
            while(curr){ /* iterating through every event */
                if(strcmp(name, curr->name) == 0){ /* removing node */
                    if(prev && curr->next){ /* remove between nodes */
                        prev->next = curr->next;
                        
                    }else if(prev && !curr->next){ /* remove at tail */
                        prev->next = NULL;
                    }else{ /* remove at head */
                        head = (calendar->events + i);
                        *head = (*head)->next;
                    }
                    
                    /* freeing memory */
                    if(event_to_remove->info && calendar->free_info_func){
                        calendar->free_info_func(event_to_remove->info);
                    }
                    calendar->total_events--;
                    free(event_to_remove->name);
                    free(event_to_remove);
                    return SUCCESS;
                }
                prev = curr;
                curr = curr->next;
            }
            prev = NULL;
            curr = *head;
        }
    }
    return FAILURE;
}

/* This function returns the info pointer associated with the specified event. 
The function returns NULL if the event is not found. Assume the calendar and
name parameters are different than NULL. */
void *get_event_info(Calendar *calendar, const char *name){
    Event *event;

    find_event(calendar, name, &event);
    if(!event){
        return NULL;
    }
    
    return event->info;
}

/* This function removes all of the event lists associated with the calendar
and set them to empty lists. Notice that the array holding the event lists will
not be removed. The total number of events is set to 0. If an event has an info
field other than NULL and a free_info_func exists the function is called on the
info field. 
This function returns FAILURE if calendar is NULL; otherwise the function
returns SUCCESS. */
int clear_calendar(Calendar *calendar){
    int i = 0;
    
    if(!calendar){
        return FAILURE;
    }

    for(i = 0; i < calendar->days; i++){ /* iterating through the days */
        clear_day(calendar, i + 1);
    }
    return SUCCESS;
}   

/* This function removes all the events for the specified day, setting the event
list to empty. The total number of events is adjusted accordingly. If an event
has an info field other than NULL and a free_info_func exists, the function is
called on the info field. 
This function returns FAILURE if calendar is NULL, or if the day is less than 1 
or greater than the calendar days; otherwise the function returns SUCCESS. */
int clear_day(Calendar *calendar, int day){
    Event **head, *curr, *prev = NULL;
    
    if(!calendar || day < 1 || day > calendar->days){
        return FAILURE;
    }
    head = (calendar->events + day - 1);
    curr = *head;
    while(curr){ /* iterating through every event on the day */
        prev = curr;
        curr = curr->next;
        if(calendar->free_info_func != NULL && prev->info != NULL){
            calendar->free_info_func(prev->info);
        }
        calendar->total_events--;
        free(prev->name);
        free(prev);
        *head = NULL;
    }  

    return SUCCESS;
}

/* This function frees memory that was dynamically-allocated for the calendar. 
If an event has an info field other than NULL and a free_info_func exists, the
function is called on the info field. 
This function returns FAILURE if calendar is NULL; otherwise the function 
returns SUCCESS. */
int destroy_calendar(Calendar *calendar){
    if(!calendar){
        return FAILURE;
    }
    clear_calendar(calendar);
    
    free(calendar->name);
    free(calendar->events);
    free(calendar);
    return SUCCESS;
}



