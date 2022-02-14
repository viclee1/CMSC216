#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calendar.h"
#include "event.h"

/* Victor Lee, UID 117213218, Directory ID vlee842 */

/* Initializes a Calendar struct based on the parameters. FAILURE is returned if
 * calendar and/or name are NULL, if the number of days is less than 1, or if
 * any memory allocation fails. Otherwise the function returns SUCCESS. */
int init_calendar(const char *name, int days,
		  int (*comp_func) (const void *ptr1, const void *ptr2),
		  void (*free_info_func) (void *ptr), Calendar ** calendar) {
	if (calendar == NULL || name == NULL || days < 1) {
		return FAILURE;
	} else {
		Calendar *new = malloc(sizeof(Calendar));
		if (new == NULL) {
			return FAILURE;
		}
		
		new->name = (char *) malloc(strlen(name) + 1);

		if (new->name == NULL) {
			return FAILURE;
		} else {
			strcpy(new->name, name);
		}

		new->events = calloc(days, sizeof(Event));
		if (new->events == NULL) {
			return FAILURE;
		}
		
		new->days = days;
		new->total_events = 0;
		
		new->comp_func = comp_func;
		new->free_info_func = free_info_func;
		*calendar = new;
		return SUCCESS;

	}
}

/* The function prints to the designated output stream, the calendar's name, days,
 * and total number of events if print_all is true; otherwise this information is
 * not printed. Information about each event name (name, start time and duration)
 * is printed regardless of the value print_all. Returns FAILURE if the calendar
 * and/or output_strean is NULL, otherwise returns SUCCESS.*/
int print_calendar(Calendar *calendar, FILE *output_stream, int print_all) {
	if (calendar == NULL || output_stream == NULL) {
		return FAILURE;
	} else {
		int i;
		Event *event;
		if (print_all) {
			fprintf(output_stream, "Calendar's Name: \"%s\"\n", 
				calendar->name);

			fprintf(output_stream, "Days: %d\n", calendar->days);
			fprintf(output_stream, "Total Events: %d\n", 
				calendar->total_events);
			fprintf(output_stream, "\n");
		}
		fprintf(output_stream, "**** Events ****\n");
		if(calendar->total_events != 0) {
			for (i = 0; i < calendar->days; i++) {
				fprintf(output_stream, "Day %d\n", i + 1);
				event = calendar->events[i];
				while (event != NULL) {
					fprintf(output_stream, "Event's Name: \"%s\", ", 
						event->name);
					fprintf(output_stream, "Start_time: %d, ", 
						event->start_time);
					fprintf(output_stream, "Duration: %d\n", 
						event->duration_minutes);
					event = event->next;
				}
			}
		}

		return SUCCESS;
	}
}

/* Adds the specified event to the event list associated with parameter day,
 * ensuring that the resulting event list is in increasing sorted order
 * according to the comparison function. Returns FAILURE if the calendar
 * and/or name are NULL, start time is not between 0 and 2400 (inclusive),
 * duration_minutes is less than or equal to 0, day is less than 1 or greater than
 * the number of calendar days, an event with the same name already exists in the
 * calendar, there is no comparison function (comp_func is NULL), or if any memory
 * allocation fails. Returns SUCCESS elsewise. */
int add_event(Calendar *calendar, const char *name, int start_time, 
		int duration_minutes, void *info, int day) {
	if (calendar == NULL || name == NULL || start_time < 0 || start_time > 2400
	    || duration_minutes <= 0 || day < 1 || day > calendar->days ||
	    calendar->comp_func == NULL) {
		return FAILURE;
	} else {
		Event *new = malloc(sizeof(Event)), *find = NULL,
			*curr = calendar->events[day - 1];
		if (new == NULL) {
			return FAILURE;
		}

		/* used to find if an event with that name already exists */
		if (find_event(calendar, name, &find) == SUCCESS) {
			return FAILURE;
		}

		new->name = (char *) malloc(strlen(name) + 1);
		if (new->name == NULL) {
			return FAILURE;
		} else {
			strcpy(new->name, name);
		}

		new->start_time = start_time;
		new->duration_minutes = duration_minutes;
		new->info = info;
		/* used for traversing linked lists and indicates the end */
		new->next = NULL;
		
		/* if the linked list is not empty, this while loop will not run,
                 * and the code after will add it to the beginning */
 		while (curr != NULL && calendar->comp_func(curr, new) < 0) {
			if (curr->next == NULL) {
				curr->next = new;					
				calendar->total_events++;
				return SUCCESS;
			} else if (calendar->comp_func(curr->next, new) >= 0) {
				new->next = curr->next;
				curr->next = new;
				calendar->total_events++;
				return SUCCESS;	
			} else {
				curr = curr->next;
			}
		}
		calendar->events[day - 1] = new;
		new->next = curr;
		calendar->total_events++;
		return SUCCESS;
	}
}

/* Function returns SUCCESS if the calendar has an event with the specified name.
 * In this case, it returns a pointer to that event via parameter event if and only
 * if the parameter is not NULL (no pointer is returned if parameter event is NULL.
 * The function returns FAILURE if the calendar and/or name are NULL, or if 
 * calendar does not have an event with the specified name. */
int find_event(Calendar *calendar, const char *name, Event **event) {
	if (calendar == NULL || name == NULL) {
		return FAILURE;
	} else {
		Event *curr;
		int i;
		for (i = 0; i < calendar->days; i++) {
			curr = calendar->events[i];

			if (curr != NULL) {
				if (strcmp(curr->name, name) == 0) {
					if (event != NULL) {
						*event = curr;
					}
					return SUCCESS;
				} else {
					curr = curr->next;
					while (curr != NULL) {
						if (strcmp(curr->name, name) == 0) {
							if (event != NULL) {
								*event = curr;
							}
							return SUCCESS;
						} else {
							curr = curr->next;
						}
					}
				}
			}
		}
		/* if the for loop does not find the event, FAILURE is returned */
		return FAILURE;
	}
}

/* The function returns SUCCESS if the calendar has an event with the specified
 * name in the specified day. In this case, it returns a pointer to that event
 * via parameter event if and only if the parameter is not NULL. The function
 * return FAILURE if calendar and/or name are NULL, if the day parameter is
 * less than 1 or greater than the number of calendar days, or if the event
 * is not found in the specified day */
int find_event_in_day(Calendar *calendar, const char *name, int day,
			Event **event) {
	if (calendar == NULL || name == NULL || day < 1 || day > calendar->days) {
		return FAILURE;
	} else {
		Event *curr = calendar->events[day - 1];
		while (curr != NULL) {
			if (strcmp(name, curr->name) == 0) {
				if (event != NULL) {
					*event = curr;
				}
				return SUCCESS;
			} else {
				curr = curr->next;
			}
		}
		return FAILURE;
	}
}

/* Function returns SUCCESS if the calendar has the sepcified event. In this case,
 * it removes the event from the calendar, updates the number of events, and frees
 * any memory allocated for the event. It calls the free_info_fun on the event's
 * info field if and only if both of these are non-NULL. Returns FAILURE if the
 * calendar and/or name are NULL, or if the event is not in the calendar */
int remove_event(Calendar *calendar, const char *name) {
	if (calendar == NULL || name == NULL) {
		return FAILURE;
	} else {
		Event *curr, *prev = NULL;
		int i;
		for (i = 0; i < calendar->days; i++) {
			curr = calendar->events[i];
			/* traverses through linked list to try to find the 
 			 * event to remove */
			while (curr != NULL) {
				if (strcmp(curr->name, name) == 0) {
					if (calendar->free_info_func != NULL &&
					    curr->info != NULL) {
						calendar->free_info_func(curr->info);
					}
					if (prev == NULL) {
						calendar->events[i] = curr->next;
					} else {
						prev->next = curr->next;
					}
					free(curr->name);
					free(curr);
					calendar->total_events--;
					return SUCCESS;	
				} else {
					prev = curr;
					curr = curr->next;
				}
			}
		}
		/* if the event did not exist, FAILURE is returned */
		return FAILURE;
	}
}

/* The function returns the info pointer associated with the specified event.
 * The function returns NULL if the event is not found */
void *get_event_info(Calendar *calendar, const char *name) {
	Event *event;
	if(find_event(calendar, name, &event) == SUCCESS) {
		return event->info;
	}
	return NULL;
}

/* The function returns SUCCESS if the calendar is not NULL. In this case, it
 * removes every event and sets every event list to empty. The array of pointers
 * to event lists is not removed */
int clear_calendar(Calendar *calendar) {
	if (calendar == NULL) {
		return FAILURE;
	} else {
		int i;
		/* calls clear_day in a for loop to go through each day in the array */
		for (i = 0; i < calendar->days; i++) {
			clear_day(calendar, i + 1);
		}
		return SUCCESS;
	}
}

/* This function returns FAILURE if the calendar is NULL or if day is less than
 * 1 or greater than the number of calender days. Otherwise it removes all the
 * events for the specified day, sets the day's event list to empty, and returns
 * SUCCESS; */
int clear_day(Calendar *calendar, int day) {
	if (calendar == NULL || day < 1 || day > calendar->days) {
		return FAILURE;
	} else {
		Event *event = calendar->events[day - 1], *next;
		if (event != NULL) {
			next = event->next;
	        	while (next != NULL) { 
	        		/* keeps track of traversal so when freeing memory 
	 			*  the next event in the link is not lost */
				event->next = next->next;
				free(next->name);
				if (next->info != NULL &&
                            	    calendar->free_info_func != NULL) {
                        		calendar->free_info_func(next->info);
                        	}
				free(next);
				calendar->total_events--;
                        	next = event->next; 
	        	}
			free(event->name);
			free(event);
			calendar->total_events--;
		}
	        calendar->events[day - 1] = NULL; 
	        return SUCCESS; 
	} 
}

/* The function returns FAILURE if the calendar is NULL. Otherwise it removes
 * every event, frees all the memory that was dynamically allocated for the
 * calendar, and returns SUCCESS. */
int destroy_calendar(Calendar *calendar) {
	if (calendar == NULL) {
		return FAILURE;
	} else {
		/* calls clear calendar to free each event and then frees
 		 * the allocated elements in its own struct */
		clear_calendar(calendar);
		free(calendar->events);
		free(calendar->name);
		free(calendar);
		return SUCCESS;
	}
}
