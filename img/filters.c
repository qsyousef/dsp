#include <math.h>
#include "filters.h"

void warp(char *rawpic, char *warpedpic, size_t width, size_t height,
						int num_components)
{
	int x, y, x_shift, y_shift, u, v, x_t;
	int src, dst;
	int widtht;
	int i;
	double r, a, rn;
	double x_norm, y_norm;
	widtht = width*num_components;
	x_shift = 0*num_components;
	y_shift = 0;
	for (v = y_shift, y = 0; y < height; y++, v++)
		for(u = x_shift, x = 0, x_t=0; (x+num_components-1) < widtht; x += num_components, u += num_components, x_t++) {
			x_norm = (double)x_t/width;
			y_norm = (double)y/height;
			r = pow(x_norm-0.5, 2) + pow(y_norm-0.5, 2);
			r = sqrt(r);
			a = atan2(y_norm-0.5, x_norm-0.5);
			rn = pow(r, 0.75)*0.5;
			u = (int)((rn*cos(a)+0.5)*widtht);
			u -= u%3;
			v = (int)((rn*sin(a)+0.5)*height);
			src = x+y*widtht;
			dst = (u+v*widtht);
			if (u < 0 || u > widtht)
				continue;
			if (v < 0 || v > height)
				continue;	
			if (dst+num_components >= widtht*height)
				continue;
			if (dst < 0)
				continue;
			//printf("%d %d\n", u, v);
			for (i = 0; i < num_components; i++)
				warpedpic[dst+i] = rawpic[src+i];
		}
}

void thresholding(char *rawpic, char *warpedpic, size_t width, size_t height,
						int num_components)
{
	int i;
	for (i = 0; i < width*height*num_components; i += num_components) {
		unsigned char pixel = 255;
		unsigned char Y = (0.2126*rawpic[i]) + (0.7152*rawpic[i+1]) + (0.0722*rawpic[i+2]);
		if (Y < 220)
			pixel = 0;
		warpedpic[i]   = pixel;
		warpedpic[i+1] = pixel;
		warpedpic[i+2] = pixel;
	}
}

void shift(char *rawpic, char *warpedpic, size_t width, size_t height,
						int num_components)
{
	int x, y, x_shift, y_shift, u, v;
	int src, dst;
	int widtht;
	int i;
	x_shift = 100*num_components;
	y_shift = 150;
	widtht = width*num_components;
	for (v = y_shift, y = 0; v < height; y++, v++)
		for(u = x_shift, x = 0; (u+num_components-1) < widtht; x += num_components, u += num_components) {
			src = x+y*widtht;
			dst = u+v*widtht;
			for (i = 0; i < num_components; i++)
				warpedpic[dst+i] = rawpic[src+i];
		}
}
