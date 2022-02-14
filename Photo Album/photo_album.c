#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "photo_album.h"
#include "my_memory_checker_216.h"

/* Returns a dynamically-allocated Photo struct initialized based on the 
 * provided parameters. If parameter description is NULL, no memory 
 * allocation takes place and the Photo struct’s description 
 * field is initialized to NULL. The function returns NULL if a memory allocation
 * fails. */
Photo *create_photo(int id, const char *description) {
	Photo *photo;
	photo = malloc(sizeof(Photo));
	if (photo == NULL) {
		return NULL;
	}

	photo->id = id;
	if (description != NULL) {
		photo->description = malloc(strlen(description) + 1);
		if (photo->description == NULL) {
			return NULL;
		}
		strcpy(photo->description, description);
	} else {
		photo->description = NULL;
	}
	return photo;
}

/* Prints the photo’s id and description. If the description is NULL, the 
 * message description message is ”None”. The function does nothing if 
 * the photo parameter is NULL. */
void print_photo(Photo *photo) {
	if (photo != NULL) {
		if (photo->description == NULL) {
			printf("Photo ID: %d, Description: None\n", photo->id);
		} else {
			printf("Photo ID: %d, Description: %s\n", 
				photo->id, photo->description);
		}
	}
}

/*Deallocates all dynamically-allocated memory associated with parameter photo. 
 * The function does nothing if parameter photo is NULL.*/
void destroy_photo(Photo *photo) {
	if(photo != NULL) {
		if (photo->description != NULL) {
			free(photo->description);
		}
		free(photo);
	}
}

/* Initializes the album size to 0. The function does nothing if parameter 
 * album is NULL. */
void initialize_album(Album *album) {
	if (album != NULL) {
		album->size = 0;
	}
}

/* Prints the contents of the album. If the album has no photos, the message 
 * ”Album has no photos.” is printed. The function does nothing if parameter 
 * album is NULL.*/
void print_album(const Album *album) {
	if (album != NULL) {
		if (album->size == 0) {
			printf("Album has no photos.\n");
		} else {
			int i;
			for (i = 0; i < album->size; i++) {
				print_photo(album->all_photos[i]);
			}
		}
	}
}

/* Deallocates all dynamically-allocated memory associated with parameter album
 * and sets the album’s size to 0. The function does nothing if parameter
 * album is NULL.*/
void destroy_album(Album *album) {
	if (album != NULL) {
		int i;
		for (i = 0; i < album->size; i++) {
			destroy_photo(album->all_photos[i]);
		}
		album->size = 0;
	}
}

/* Appends (to the end of the array) a photo if there is space (if the album size 
 * is less than MAX ALBUM SIZE). Photo is not added if a photo cannot be created. 
 * The function does nothing if parameter album is NULL or the album has no 
 * space for the photo. */
void add_photo_to_album(Album *album, int id, const char *description) {
	if(album != NULL && album->size < MAX_ALBUM_SIZE) {
		Photo *photo = create_photo(id, description);
		if (photo != NULL) {
			album->all_photos[album->size] = photo;
			album->size++;
		}
	}
}
