#pragma once

#include "pixel.h"
#include <sys/types.h>
#include <stdbool.h>

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

bool is_in_buffer(struct Buffer *buf, uint x, uint y);

struct Pixel read_pixel_from_buffer(struct Buffer *buf, uint x, uint y);

void write_buffer(struct Buffer *self, struct Buffer *other, uint x, uint y);
void write_pixel_to_buffer(struct Buffer *buf, uint x, uint y, struct Pixel p);

void read_to_buffer(struct Buffer *src_buf, struct Buffer *dst_buf, uint x, uint y);
