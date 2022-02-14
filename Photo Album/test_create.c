#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "photo_album.h"

int main(){
	Photo *photo = create_photo(10, NULL);
	print_photo(photo);
	return 0;
}
