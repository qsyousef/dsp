#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include "codec.h"

unsigned char * read_jpeg (const char *filename, size_t *width, size_t *height,
					int *num_components, int *color_space)
{
	FILE *pic;
	struct jpeg_decompress_struct a;
	struct jpeg_error_mgr jerr;
	j_decompress_ptr cinfo = &a;
	int ret, j = 0;
	unsigned char *rawpic;
	JSAMPROW scanline[1];
	

	/* Open the picture and decode it */
	cinfo->err = jpeg_std_error (&jerr);
	jpeg_create_decompress (cinfo);
	pic = fopen (filename, "r");
	if (!pic) {
		perror("fopen");
		return NULL;
	}
	jpeg_stdio_src (cinfo, pic);
	ret = jpeg_read_header (cinfo, TRUE);
	if (ret != JPEG_HEADER_OK) {
		printf ("Not supported jpeg file, unknown header info\n");
		return NULL;
	}
	jpeg_start_decompress (cinfo);
	/* Read raw data */
	rawpic = malloc (cinfo->output_width*cinfo->output_height*cinfo->num_components);
	if (!rawpic) {
		printf("Can't allocate memory to rawbuffer\n");
		return NULL;
	}
	scanline[0] = malloc (cinfo->output_width*cinfo->num_components);
	if (!scanline[0]) {
		printf("Can't allocate memory to scanline\n");
		free (rawpic);
		return NULL;
	}
	while (cinfo->output_scanline < cinfo->output_height) {
		int i;
		jpeg_read_scanlines (cinfo, scanline, 1);
		for (i = 0; i < cinfo->output_width*cinfo->num_components; i++)
			rawpic[j++] = scanline[0][i];
	}
	*width = cinfo->output_width;
	*height = cinfo->output_height;
	*num_components = cinfo->num_components;
	*color_space = cinfo->out_color_space;
	/* Clean up */
	free (scanline[0]);
	jpeg_finish_decompress (cinfo);
	jpeg_destroy_decompress (cinfo);
	fclose (pic);

	return rawpic;
}
void write_jpeg (const char *filename, unsigned char *rawpic, size_t width, size_t height,
						int num_components, int color_space)
{
	FILE *pic;
	struct jpeg_compress_struct a;
	struct jpeg_error_mgr jerr;
	j_compress_ptr cinfo = &a;
	int ret;
	JSAMPROW scanline[1];
	

	/* Setup file and compression structs */
	cinfo->err = jpeg_std_error (&jerr);
	jpeg_create_compress (cinfo);
	pic = fopen (filename, "w");
	if (!pic) {
		perror("fopen");
		return;
	}
	jpeg_stdio_dest (cinfo, pic);
	/* Set some parameters */
	cinfo->image_width = width;
	cinfo->image_height = height;
	cinfo->input_components = num_components;
	cinfo->in_color_space = color_space;
	jpeg_set_defaults (cinfo);
 	/* start encoding */
	jpeg_start_compress (cinfo, TRUE);
	while (cinfo->next_scanline < cinfo->image_height) {
		scanline[0] = &rawpic[cinfo->next_scanline*cinfo->image_width*cinfo->input_components];
		jpeg_write_scanlines (cinfo, scanline, 1);
	}
	/* Clean up */
	jpeg_finish_compress (cinfo);
	jpeg_destroy_compress (cinfo);
	fclose (pic);
}
