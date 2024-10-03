#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <math.h>

#include "buffer.h"
#include "pixel.h"

#include "stb_image_write.h"

void make_checkerboard(struct Buffer *bg) {
	struct Pixel a = {51,51,51,255};
	struct Pixel b = {255, 255, 255, 255};
	
	struct Buffer *buf_a = create_buffer(8, 8);
	if (buf_a == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		return;
	}
	fill_buffer(buf_a, a);
	struct Buffer *buf_b = create_buffer(8, 8);
	if (buf_b == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		return;
	}
	fill_buffer(buf_b, b);
	
	for (int x = 0; x < bg->width/8; x++) {
		for (int y = 0; y < bg->height/8; y++) {
			if ( (x%2 ^ y%2 ) == 1) {
				write_buffer(bg, buf_a, x*8, y*8);
			} else {
				write_buffer(bg, buf_b, x*8, y*8);
			}
		}
	}
	delete_buffer(buf_a);
	delete_buffer(buf_b);
}

int main() {
	struct Buffer *buf = create_buffer(240, 320);
	if (buf == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		return 1;
	}
	struct Buffer *box = create_buffer(32, 32);
	if (box == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		return 1;
	}
	struct Buffer *bg = create_buffer(240, 320);
	if (bg == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		return 1;
	}
	make_checkerboard(bg);
	float h = 0.0;
	while (1) {
		fill_buffer(buf, (struct Pixel){51,51,51,255});
		fill_buffer(box, (struct Pixel){
			255*(0.5*sin((h+  0)*(M_PI/180.0))+0.5),
			255*(0.5*sin((h+120)*(M_PI/180.0))+0.5),
			255*(0.5*sin((h+240)*(M_PI/180.0))+0.5),
			50
		});
		write_buffer(buf, bg, 0, 0);
		write_buffer(buf, box, (int)(25+h) % 240, 25);
		stbi_write_png("/run/user/1000/test.png", buf->width, buf->height, 4, (buf->pixels), buf->width * sizeof(struct Pixel));
		h = fmod(h+5, 360.0);
		usleep(1000 * 1000/60);
	}
	return 0;
}
