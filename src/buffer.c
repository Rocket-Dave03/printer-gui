#include "buffer.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "pixel.h"

struct Buffer *create_buffer(uint32_t width, uint32_t height) {
	struct Buffer *buf = malloc(sizeof(struct Buffer));
	memset(buf, 0, sizeof(struct Buffer));

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
	if (buf == NULL) {
		return;
	}
	free(buf->pixels);
	buf->pixels = NULL;
	free(buf);
}

int resize_buffer(struct Buffer *buf, uint32_t width, uint32_t height) {
	struct Pixel *new_data = realloc(buf->pixels, sizeof(struct Pixel) * width * height);
	if (new_data == NULL) {
		fprintf(stderr, "Failed to resize buffer: width: %d, height: %d\n", width, height);

		perror("resize_buffer");
		return -1;
	}
	buf->pixels = new_data;
	buf->width = width;
	buf->height = height;

	return 0;
}

void clear_buffer(struct Buffer *buf) {
	memset(buf, 0x00, sizeof(struct Pixel) * buf->width * buf->height);
	for (int i = 0; i < buf->width * buf->height; i++) {
		((uint8_t *)buf->pixels)[i * 4 + 3] = 0xFF;
	}
}

void fill_buffer(struct Buffer *buf, struct Pixel p) {
	for (int i = 0; i < buf->width * buf->height; i++) {
		buf->pixels[i] = p;
	}
}

bool is_in_buffer(struct Buffer *buf, uint32_t x, uint32_t y) {
	if (x >= 0 && x < buf->width && y >= 0 && y < buf->height) {
		return true;
	} else {
		return false;
	}
}

struct Pixel read_pixel_from_buffer(struct Buffer *buf, uint32_t x, uint32_t y) {
	if (is_in_buffer(buf, x, y)) {
		return buf->pixels[y * buf->width + x];
	} else {
		return (struct Pixel){0, 0, 0, 0xFF};
	}
}

void write_buffer(struct Buffer *self, struct Buffer *other, uint32_t x, uint32_t y) {
	if (x >= self->width || y >= self->height) {
		return;
	}
	if ((x + other->width - 1) < 0 || (y + other->height - 1) < 0) {
		return;
	}
	for (int col = 0; col < other->width; col++) {
		for (int row = 0; row < other->height; row++) {
			int cur_x = x + col;
			int cur_y = y + row;
			struct Pixel a = read_pixel_from_buffer(other, col, row);
			struct Pixel b = read_pixel_from_buffer(self, x + col, y + row);
			float ra = a.r / 255.0;
			float ga = a.g / 255.0;
			float ba = a.b / 255.0;
			float aa = a.a / 255.0;
			float rb = b.r / 255.0;
			float gb = b.g / 255.0;
			float bb = b.b / 255.0;
			float ab = b.a / 255.0;

			float alpha_o = aa + ab * (1 - aa);
			float ro = (ra * aa + rb * ab * (1 - aa)) / alpha_o;
			float go = (ga * aa + gb * ab * (1 - aa)) / alpha_o;
			float bo = (ba * aa + bb * ab * (1 - aa)) / alpha_o;
			// clang-format off
			write_pixel_to_buffer(self, cur_x, cur_y,
			(struct Pixel){
				  ro * 255,
				  go * 255,
				  bo * 255,
				  alpha_o * 255,
			});
			// clang-format on
		}
	}
}

void write_pixel_to_buffer(struct Buffer *buf, uint32_t x, uint32_t y, struct Pixel p) {
	if (is_in_buffer(buf, x, y)) {
		buf->pixels[y * buf->width + x] = p;
	}
}

void read_to_buffer(struct Buffer *src_buf, struct Buffer *dst_buf, uint32_t x, uint32_t y) {
	if (src_buf == NULL || dst_buf == NULL) {
		return;
	}

	for (int cur_x = x; cur_x < dst_buf->width; cur_x++) {
		for (int cur_y = y; cur_y < dst_buf->height; cur_y++) {
			if (is_in_buffer(src_buf, cur_x + x, cur_y + y)) {
				struct Pixel p = read_pixel_from_buffer(src_buf, cur_x + x, cur_y + y);
				write_pixel_to_buffer(dst_buf, cur_x, cur_y, p);
			} else {
				write_pixel_to_buffer(dst_buf, cur_x, cur_y, (struct Pixel){0, 0, 0, 0});
			}
		}
	}
}
