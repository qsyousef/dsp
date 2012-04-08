#ifndef FILTERS_H
#define FILTERS_H

#include <stdlib.h>

void warp(char *rawpic, char *warpedpic, size_t width, size_t height,
						int num_components);
void thresholding(char *rawpic, char *warpedpic, size_t width, size_t height,
						int num_components);
void shift(char *rawpic, char *warpedpic, size_t width, size_t height,
						int num_components);

#endif /* FILTERS_H */
