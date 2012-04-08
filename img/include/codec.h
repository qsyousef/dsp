#ifndef CODEC_H
#define CODEC_H

unsigned char * read_jpeg (const char *filename, size_t *width, size_t *height,
					int *num_components, int *color_space);
void write_jpeg (const char *filename, unsigned char *rawpic, size_t width,
			size_t height, int num_components, int color_space);

#endif /* CODEC_H */
