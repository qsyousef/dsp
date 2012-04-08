#include <stdio.h>
#include <stdlib.h>
#include "codec.h"
#include "filters.h"

int main (int argc, char *argv[])
{
	unsigned char *rawpic = NULL;
	unsigned char *warpedpic = NULL;
	size_t width, height;
	int num_components, color_space;

	/* Get raw data */
	rawpic = read_jpeg ("shrek_cat_eyes.jpg", &width, &height, &num_components, &color_space);
	if (!rawpic)
		goto out;
	warpedpic = calloc(1, width*height*num_components);
	if (!warpedpic) 
		goto out;
	
	/* do some processing here */
	warp(rawpic, warpedpic, width, height, num_components);
	//thresholding(rawpic, warpedpic, width, height, num_components);
	//shift(rawpic, warpedpic, width, height, num_components);

	/* write it back as jpeg */
	write_jpeg ("out.jpg", warpedpic, width, height, num_components, color_space);
	printf("Done :)\n");
out:
	if (rawpic)
		free(rawpic);
	if (warpedpic)
		free(warpedpic);
	return 0;
}
