#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */ 
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {
   return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

typedef struct task_info {
  double age;
  char *name;
} Task_info;

static Task_info *create_task_info(double age, const char *name) {
   Task_info *task_info = malloc(sizeof(Task_info));

   if (task_info) {
      task_info->name = malloc(strlen(name) + 1);
      if (task_info->name) {
         task_info->age = age;
         strcpy(task_info->name, name);
         return task_info;
      }
   }

   return NULL;
}

static void free_task_info(void *ptr) {
   Task_info *task_info = (Task_info *)ptr;

   free(task_info->name);
   free(task_info);
}

/* Description here: This test checks ...  */
static int test1() {
   int days = 7;
   Calendar *calendar;

   if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      if (print_calendar(calendar, stdout, 1) == SUCCESS) {
         return destroy_calendar(calendar);
      }
   }
    
   return FAILURE;
}

/* This test checks if init_calendar returns FAILURE when calendar or name is 
null*/
static int test2() {
    Calendar *calendar;
    int days = 3;
    
    printf("TEST 2\n");
    if(init_calendar("2", days, comp_minutes, NULL, NULL) == FAILURE &&
    init_calendar(NULL, days, comp_minutes, NULL, &calendar) == FAILURE){
        return SUCCESS;
    }
    return FAILURE;
}

/* checks if init_calendar returns SUCCESS when all parameters are valid and
checks if total_events is 0 */
static int test3() {
    Calendar *calendar;
    int days = 10000;
    
    printf("TEST 3\n");
    if(init_calendar("3", days, comp_minutes, NULL, &calendar) == SUCCESS
    && calendar->total_events == 0){
        return destroy_calendar(calendar);
    }
    return FAILURE;
}

/* checks if init_calendar returns FAILURE when number of days is less than 1 */
static int test4() {
    Calendar *calendar;
    int days = 0;
    
    printf("TEST 4\n");
    if(init_calendar("4", days, comp_minutes, NULL, &calendar) == FAILURE
    && init_calendar("4", -1723, comp_minutes, NULL, &calendar) == FAILURE){
        return SUCCESS;
    }
    return FAILURE;
}

/* testing print_calendar's print_all parameter */
static int test5() {
    Calendar *calendar;
    int days = 5, start = 400, duration = 100, activity_day = 1;
    void *info = NULL;
    
    printf("TEST 5\n");
    if(init_calendar("5", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        if(print_calendar(calendar, stdout, 1) == SUCCESS && 
        print_calendar(calendar, stdout, 0) == SUCCESS &&
        print_calendar(calendar, stdout, 56) == SUCCESS &&
        print_calendar(calendar, stdout, -12) == SUCCESS){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if print_calendar returns FAILURE when calendar is null */
static int test6() {  
    printf("TEST 6\n");
    if(print_calendar(NULL, stdout, 1) == FAILURE){
        return SUCCESS;
    }
    return FAILURE;
}

/* checks if print_calendar returns FAILURE when output_stream is null */
static int test7() {
    Calendar *calendar;
    int days = 5, start = 400, duration = 100, activity_day = 1;
    void *info = NULL;
     
    printf("TEST 7\n");
    if(init_calendar("7", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        if(print_calendar(calendar, NULL, 1) == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if add_event returns failure when calendar is null */
static int test8() {
    Calendar *calendar;
    int days = 5, start = 400, duration = 100, activity_day = 1;
    void *info = NULL;
     
    printf("TEST 8\n");
    if(init_calendar("8", days, comp_minutes, NULL, &calendar) == SUCCESS){
        if(add_event(NULL, "Activity 1", start, duration, info, activity_day)
        == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if add_event returns failure when name is null */
static int test9() {
    Calendar *calendar;
    int days = 5, start = 400, duration = 100, activity_day = 1;
    void *info = NULL;
     
    printf("TEST 9\n");
    if(init_calendar("9", days, comp_minutes, NULL, &calendar) == SUCCESS){
        if(add_event(calendar, NULL, start, duration, info, activity_day)
        == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if add_event returns failure when start_time is invalid 
(greater than 2400 or less than 0) */
static int test10() {
    Calendar *calendar;
    int days = 5, start = -1, duration = 100, activity_day = 1;
    void *info = NULL;
     
    printf("TEST 10\n");
    if(init_calendar("10", days, comp_minutes, NULL, &calendar) == SUCCESS){
        if(add_event(calendar, "Activity1", start, duration, info, activity_day)
        == FAILURE && 
        add_event(calendar, "Activity 2", 2401, duration, info, activity_day)
        == FAILURE && 
        add_event(calendar, "Activity 2", 3728713, duration, info, activity_day)
        == FAILURE && 
        add_event(calendar, "Activity 2", -271312, duration, info, activity_day)
        == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if add_event returns failure when duration is <= 0 */
static int test11() {
    Calendar *calendar;
    int days = 5, start = 0, duration = 0, activity_day = 1;
    void *info = NULL;
     
    printf("TEST 11\n");
    if(init_calendar("11", days, comp_minutes, NULL, &calendar) == SUCCESS){
        if(add_event(calendar, "Activity1", start, duration, info, activity_day)
        == FAILURE && 
        add_event(calendar, "Activity 2", 100, -23813721, info, activity_day)
        == FAILURE &&
        add_event(calendar, "Activity 3", 100, -37218, info, activity_day)
        == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if add_event returns failure when day is <1 or >calendar->days */
static int test12() {
    Calendar *calendar;
    int days = 5, start = 0, duration = 100, activity_day = 0;
    void *info = NULL;
     
    printf("TEST 12\n");
    if(init_calendar("12", days, comp_minutes, NULL, &calendar) == SUCCESS){
        if(add_event(calendar, "Activity1", start, duration, info, activity_day)
        == FAILURE && 
        add_event(calendar, "Activity 2", 100, duration, info, days + 1)
        == FAILURE &&
        add_event(calendar, "Activity 3", 100, duration, info, -100)
        == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if add_event returns failure when there already exists an event with
the same name */
static int test13() {
    Calendar *calendar;
    int days = 5, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
     
    printf("TEST 13\n");
    if(init_calendar("13", days, comp_minutes, NULL, &calendar) == SUCCESS){
        if(add_event(calendar, "Activity1", start, duration, info, activity_day)
        == SUCCESS && 
        add_event(calendar, "Activity1", 100, 500, info, 2) == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if find_event returns failure when calendar or name is null */
static int test14() {
    Calendar *calendar;
    int days = 5;
    Event *event;
    
    printf("TEST 14\n");
    if(init_calendar("14", days, comp_minutes, NULL, &calendar) == SUCCESS){
        if(find_event(NULL, "Activity 1", &event) == FAILURE && 
        find_event(calendar, NULL, &event) == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if find_event returns failure when event is not found vs when it is */
static int test15() {
    Calendar *calendar;
    int days = 5, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    Event *event;
    
    printf("TEST 15\n");
    if(init_calendar("15", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        
        if(find_event(calendar, "Activity 2", &event) == FAILURE && 
        find_event(calendar, "Activity 1", &event) == SUCCESS){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if find_event returns success when event is found, but event parameter
is null, 
and checks if find_event returns failure when event isn't found, but event 
parameter is null */
static int test16() {
    Calendar *calendar;
    int days = 5, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    
    printf("TEST 16\n");
    if(init_calendar("16", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        
        if(find_event(calendar, "Activity 1", NULL) == SUCCESS && 
        find_event(calendar, "Activity 2", NULL) == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if find_event_in_day returns success when event is found, but event 
parameter is null, 
and checks if find_event returns failure when event isn't found, but event 
parameter is null */
static int test17() {
    Calendar *calendar;
    int days = 5, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    
    printf("TEST 17\n");
    if(init_calendar("17", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        add_event(calendar, "Activity 2", start, duration, info, 1);
        add_event(calendar, "Activity 3", start, duration, info, 1);
        add_event(calendar, "Activity 4", start, duration, info, 4);
        add_event(calendar, "Activity 5", start, duration, info, 5);
        
        if(find_event_in_day(calendar, "Activity 2", 1, NULL) == SUCCESS && 
        find_event_in_day(calendar, "Activity 2", 2, NULL) == FAILURE &&
        find_event_in_day(calendar, "Activity 5", 3, NULL) == FAILURE &&
        find_event_in_day(calendar, "Activity 5", 5, NULL) == SUCCESS){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if find_event_in_day returns failure when calendar or name is null */
static int test18() {
    Calendar *calendar;
    int days = 5;
    Event *event;
    
    printf("TEST 18\n");
    if(init_calendar("18", days, comp_minutes, NULL, &calendar) == SUCCESS){
        if(find_event_in_day(NULL, "Activity 1", 1, &event) == FAILURE && 
        find_event_in_day(calendar, NULL, 1, &event) == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if find_event_in_day returns failure when day <1 or >calendar->days */
static int test19() {
    Calendar *calendar;
    int days = 100, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    Event *event;
    
    printf("TEST 19\n");
    if(init_calendar("19", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        add_event(calendar, "Activity 2", start, duration, info, 1);
        add_event(calendar, "Activity 3", start, duration, info, 1);
        add_event(calendar, "Activity 4", start, duration, info, 4);
        add_event(calendar, "Activity 5", start, duration, info, 5);
        
        if(find_event_in_day(calendar, "Activity 2", 0, &event) == FAILURE && 
        find_event_in_day(calendar, "Activity 2", -12372, &event) == FAILURE &&
        find_event_in_day(calendar, "Activity 5", 101, &event) == FAILURE &&
        find_event_in_day(calendar, "Activity 5", 379238, &event) == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if find_event_in_day returns failure when event is not found vs when 
it is */
static int test20() {
    Calendar *calendar;
    int days = 5, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    Event *event;
    
    printf("TEST 20\n");
    if(init_calendar("20", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        
        if(find_event_in_day(calendar, "Activity 1", 1, &event) == SUCCESS && 
        find_event_in_day(calendar, "Activity 1", 2, &event) == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks if remove_event removes each event correctly (at the tail, head, and
in between) */
static int test21() {
    Calendar *calendar;
    int days = 10, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    
    printf("TEST 21\n");
    if(init_calendar("21", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        add_event(calendar, "Activity 2", start, duration, info, 1);
        add_event(calendar, "Activity 3", start, duration, info, 1);
        add_event(calendar, "Activity 4", start, duration, info, 4);
        add_event(calendar, "Activity 5", start, duration, info, 4);
        add_event(calendar, "Activity 6", start, duration, info, 5);
        print_calendar(calendar, stdout, 1);
        
        remove_event(calendar, "Activity 2"); /* removing in between */
        remove_event(calendar, "Activity 1"); /* removing at tail */
        remove_event(calendar, "Activity 5");
        remove_event(calendar, "Activity 6"); /* removing at head */
        
        print_calendar(calendar, stdout, 1);
        return destroy_calendar(calendar);
        
    }
    return FAILURE;
}

/* checks if remove_event returns failure when calendar or name is null, and
when event can't be found */
static int test22() {
    Calendar *calendar;
    int days = 10, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    
    printf("TEST 22\n");
    if(init_calendar("22", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        add_event(calendar, "Activity 2", start, duration, info, 1);
        add_event(calendar, "Activity 3", start, duration, info, 1);
        add_event(calendar, "Activity 4", start, duration, info, 4);
        add_event(calendar, "Activity 5", start, duration, info, 4);
        add_event(calendar, "Activity 6", start, duration, info, 5);
        print_calendar(calendar, stdout, 1);
        
        if(remove_event(calendar, "Activity 7") == FAILURE && 
            remove_event(NULL, "Activity 1") == FAILURE &&
            remove_event(calendar, NULL) == FAILURE){
            
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks clear_day */
static int test23() {
    Calendar *calendar;
    int days = 10, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    
    printf("TEST 23\n");
    if(init_calendar("23", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        add_event(calendar, "Activity 2", start, duration, info, 1);
        add_event(calendar, "Activity 3", start, duration, info, 1);
        add_event(calendar, "Activity 4", start, duration, info, 4);
        add_event(calendar, "Activity 5", start, duration, info, 4);
        add_event(calendar, "Activity 6", start, duration, info, 5);
        print_calendar(calendar, stdout, 1);
        
        clear_day(calendar, 1);
        clear_day(calendar, 3);
        clear_day(calendar, 4);
        print_calendar(calendar, stdout, 1);
        return destroy_calendar(calendar);
        
    }
    return FAILURE;
}

/* checks if clear_day returns failure when calendar is null, or day <1 or
day > calendar->days */
static int test24() {
    Calendar *calendar;
    int days = 10, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    
    printf("TEST 24\n");
    if(init_calendar("24", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        add_event(calendar, "Activity 2", start, duration, info, 1);
        add_event(calendar, "Activity 3", start, duration, info, 1);
        add_event(calendar, "Activity 4", start, duration, info, 4);
        add_event(calendar, "Activity 5", start, duration, info, 4);
        add_event(calendar, "Activity 6", start, duration, info, 5);
        
        if(clear_day(NULL, 1) == FAILURE && 
        clear_day(calendar, -4) == FAILURE &&
        clear_day(calendar, 842) == FAILURE){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks clear_calendar and checks if it returns failure when calendar=null */
static int test25() {
    Calendar *calendar;
    int days = 10, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    
    printf("TEST 25\n");
    if(init_calendar("25", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        add_event(calendar, "Activity 2", start, duration, info, 1);
        add_event(calendar, "Activity 3", start, duration, info, 1);
        add_event(calendar, "Activity 4", start, duration, info, 4);
        add_event(calendar, "Activity 5", start, duration, info, 4);
        add_event(calendar, "Activity 6", start, duration, info, 5);
        print_calendar(calendar, stdout, 1);
        if(clear_calendar(NULL) == FAILURE && 
        clear_calendar(calendar) == SUCCESS){
            print_calendar(calendar, stdout, 1);
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

/* checks destroy_calendar and checks if it returns failure when calendar=null*/
static int test26() {
    Calendar *calendar;
    int days = 10, start = 0, duration = 100, activity_day = 1;
    void *info = NULL;
    
    printf("TEST 26\n");
    if(init_calendar("26", days, comp_minutes, NULL, &calendar) == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        add_event(calendar, "Activity 2", start, duration, info, 1);
        add_event(calendar, "Activity 3", start, duration, info, 1);
        add_event(calendar, "Activity 4", start, duration, info, 4);
        add_event(calendar, "Activity 5", start, duration, info, 4);
        add_event(calendar, "Activity 6", start, duration, info, 5);
        print_calendar(calendar, stdout, 1);
        if(destroy_calendar(NULL) == FAILURE && 
        destroy_calendar(calendar) == SUCCESS){
            return SUCCESS;
        }
    }
    return FAILURE;
}


/* testing get_event_info */
static int test27() {
    Calendar *calendar;
    int days = 10, start = 0, duration = 100, activity_day = 1;
    void *info = create_task_info(20, "John");
    
    printf("TEST 27\n");
    if(init_calendar("Test 27", days, comp_minutes, free_task_info, &calendar) 
    == SUCCESS){
        add_event(calendar, "Activity 1", start, duration, info, activity_day);
        add_event(calendar, "Activity 2", start, duration, NULL, 1);
        add_event(calendar, "Activity 3", start, duration, NULL, 1);
        add_event(calendar, "Activity 4", start, duration, NULL, 4);
        add_event(calendar, "Activity 5", start, duration, NULL, 4);
        add_event(calendar, "Activity 6", start, duration, NULL, 5);
        if(get_event_info(calendar, "Activity 7") == NULL && 
        get_event_info(calendar, "Activity 1") == info &&
        get_event_info(calendar, "Activity 2") == NULL){
            return destroy_calendar(calendar);
        }
    }
    return FAILURE;
}

int main() {
   int result = SUCCESS;

   /***** Starting memory checking *****/
   start_memory_check();
   /***** Starting memory checking *****/

   if (test1() == FAILURE) result = FAILURE;
   if (test2() == FAILURE) result = FAILURE;
   if (test3() == FAILURE) result = FAILURE;
   if (test4() == FAILURE) result = FAILURE;
   if (test5() == FAILURE) result = FAILURE;
   if (test6() == FAILURE) result = FAILURE;
   if (test7() == FAILURE) result = FAILURE;
   if (test8() == FAILURE) result = FAILURE;
   if (test9() == FAILURE) result = FAILURE;
   if (test10() == FAILURE) result = FAILURE;
   if (test11() == FAILURE) result = FAILURE;
   if (test12() == FAILURE) result = FAILURE;
   if (test13() == FAILURE) result = FAILURE;
   if (test14() == FAILURE) result = FAILURE;
   if (test15() == FAILURE) result = FAILURE;
   if (test16() == FAILURE) result = FAILURE;
   if (test17() == FAILURE) result = FAILURE;   
   if (test18() == FAILURE) result = FAILURE;
   if (test19() == FAILURE) result = FAILURE;
   if (test20() == FAILURE) result = FAILURE;
   if (test21() == FAILURE) result = FAILURE; 
   if (test22() == FAILURE) result = FAILURE; 
   if (test23() == FAILURE) result = FAILURE;
   if (test24() == FAILURE) result = FAILURE;   
   if (test25() == FAILURE) result = FAILURE;   
   if (test26() == FAILURE) result = FAILURE;   
   if (test27() == FAILURE) result = FAILURE; 
   
   /****** Gathering memory checking info *****/
   stop_memory_check();
   /****** Gathering memory checking info *****/
   
   if (result == FAILURE) {
      exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
