#pragma once

#include "pixel.h"
#include <sys/types.h>

struct Buffer {
	uint width;
	uint height;
	struct Pixel *pixels;	
};

struct Buffer *create_buffer(uint width, uint height);
void delete_buffer(struct Buffer *);

int resize_buffer(struct Buffer *buf, uint width, uint height);

void clear_buffer(struct Buffer *buf);
void fill_buffer(struct Buffer *buf, struct Pixel p);
