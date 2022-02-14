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
  double cost;
  char *prog_language;
} Task_info;

static Task_info *create_task_info(double cost, const char *prog_language) {
   Task_info *task_info = malloc(sizeof(Task_info));

   if (task_info) {
      task_info->prog_language = malloc(strlen(prog_language) + 1);
      if (task_info->prog_language) {
         task_info->cost = cost;
         strcpy(task_info->prog_language, prog_language);
         return task_info;
      }
   }

   return NULL;
}

static void free_task_info(void *ptr) {
   Task_info *task_info = (Task_info *)ptr;

   free(task_info->prog_language);
   free(task_info);
}

/* if destroy_calendar works, both clear_day and clear_calendar should work
 * as destroy_calendar depends on clear_calendar, which that function depends 
 * on clear_day */

/* This test checks that the initialization of of calendar and printing it works  */
static int test1() {
   int days = 7;
   Calendar *calendar;	
   printf("TEST 1 STARTS HERE: \n");


   if (init_calendar("Spr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      if (print_calendar(calendar, stdout, 1) == SUCCESS) {
         return destroy_calendar(calendar);
      }
   }
    
   return FAILURE;
}

/* This test checks that the add_event function works as intended and what happens
 * when print_all is 0 */
static int test2() {
   int days = 3;
   Calendar *calendar;
   printf("\nTEST 2 STARTS HERE: \n");

   if (init_calendar("Smr", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      if(add_event(calendar, "second of the day", 1000, 60, NULL, 1) == SUCCESS &&
	 add_event(calendar, "third of the day", 1200, 30, NULL, 1) == SUCCESS &&
	 add_event(calendar, "first of the day", 900, 20, NULL, 1) == SUCCESS &&
         add_event(calendar, "third day", 900, 30, NULL, 3) == SUCCESS &&
	 add_event(calendar, "should fail1", 800, 40, NULL, 5) == FAILURE && 
         add_event(calendar, "should fail2", -1, 40, NULL, 2) == FAILURE &&
         add_event(calendar, "should fail3", 2600, 70, NULL, 2) == FAILURE) {

         if (print_calendar(calendar, stdout, 0) == SUCCESS) {
            return destroy_calendar(calendar);
         }
      }
   }

   return FAILURE;
}

/* This tests if find_event and find_event_in_day works */
static int test3() {
   int days = 7;
   Calendar *calendar;
   Event *find = NULL, *find_with_data;
   printf("\nTEST 3 STARTS HERE: \n");
   if (init_calendar("test3", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      add_event(calendar,  "second of the day", 1000, 60, NULL, 1);
      add_event(calendar,  "third of the day", 1200, 30, NULL, 1);
      add_event(calendar,  "first of the day", 900, 20, NULL, 1);
      add_event(calendar,  "third day", 900, 30, NULL, 3);
      if (find_event(calendar, "second of the day", &find) == SUCCESS && 
          find_event(calendar, "third day", &find_with_data) == SUCCESS &&
          find_event(calendar, "randome", &find) == FAILURE && 
          find_event_in_day(calendar, "third of the day", 1, &find) == SUCCESS
          && find_event_in_day(calendar, "third of the day", 3, &find) == FAILURE) {
         if (strcmp(find_with_data->name, "third day") == 0) {
            if (print_calendar(calendar, stdout, 1) == SUCCESS) {
               return destroy_calendar(calendar);
            }
         }
      }
   }

   return FAILURE;
}

/* This tests if remove_event works */
static int test4() {
   int days = 7;
   Calendar *calendar;
   printf("\nTEST 4 STARTS HERE: \n");

   if (init_calendar("test4", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      add_event(calendar,  "second of the day", 1000, 60, NULL, 1);
      add_event(calendar,  "third of the day", 1200, 30, NULL, 1);
      add_event(calendar,  "first of the day", 900, 20, NULL, 1);
      add_event(calendar,  "third day", 900, 30, NULL, 3);
      if (remove_event(calendar, "second of the day") == SUCCESS &&
	  remove_event(calendar, "second of the day") == FAILURE) {
         if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
         }
      }
   }

   return FAILURE;
}

/* This tests for get_event_info */
static int test5() {
   int days = 7;
   Calendar *calendar;
   Task_info *info, *found, *should_not_find;
   printf("\nTEST 5 STARTS HERE: \n");

   if (init_calendar("test5", days, comp_minutes, free_task_info, &calendar) == SUCCESS) {
      info = create_task_info(35000, "info");
      add_event(calendar,  "second of the day", 1000, 60, info, 1);
      add_event(calendar,  "third of the day", 1200, 30, NULL, 1);
      add_event(calendar,  "first of the day", 900, 20, NULL, 1);
      add_event(calendar,  "third day", 900, 30, NULL, 3);
      found = get_event_info(calendar, "second of the day");
      should_not_find = get_event_info(calendar, "does not exist");
      if (found != NULL && should_not_find == NULL) {
	 printf("info about found pointer: cost-%f name-%s", 
		found->cost, found->prog_language);
         if (print_calendar(calendar, stdout, 1) == SUCCESS) {
            return destroy_calendar(calendar);
         }
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



   /****** Gathering memory checking info *****/
   stop_memory_check();
   /****** Gathering memory checking info *****/
   
   if (result == FAILURE) {
      exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
