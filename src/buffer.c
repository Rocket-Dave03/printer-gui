#include "buffer.h"


#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stddef.h>

#include "pixel.h"


struct Buffer *create_buffer(uint width, uint height) {
	struct Buffer *buf = malloc(sizeof(struct Buffer));
	if (buf == NULL) {
		goto free_buf;
	}
	
	buf->width = width;
	buf->height = height;
	
	struct Pixel *data = malloc(sizeof(struct Pixel) * width * height);
	if (data == NULL) {
		goto free_data;
	}
	
	buf->pixels = data;

	
	return buf;
free_data:
	free(data);
free_buf:
	free(buf);
	return NULL;
}

void delete_buffer(struct Buffer *buf) {
	free(buf->pixels);
	buf->pixels = NULL;
	free(buf);
}

int resize_buffer(struct Buffer *buf, uint width, uint height) {
	struct Pixel *new_data = realloc(buf->pixels, sizeof(struct Pixel) * width * height);
	if (new_data == NULL) {
		return -1;
	}
	buf->pixels = new_data;
	buf->width = width;
	buf->height = height;
	
	return 0;
}


void clear_buffer(struct Buffer *buf) {
	memset(buf, 0x00, sizeof(struct Pixel) * buf->width * buf->height);
	for (int i = 0; i < buf->width * buf->height;i++) {
		((uint8_t *)buf->pixels)[i*4+3] = 0xFF;
	}
}

void fill_buffer(struct Buffer *buf, struct Pixel p) {
	for (int i = 0; i < buf->width * buf->height;i++) {
		buf->pixels[i] = p;	
	}
}
