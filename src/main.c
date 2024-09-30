#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <math.h>

#include "buffer.h"
#include "pixel.h"

#include "stb_image_write.h"




int main() {
	struct Buffer *buf = create_buffer(240, 320);
	if (buf == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		return 1;
	}
	float h = 0.0;
	while (1) {
		fill_buffer(buf, (struct Pixel){
			255*(0.5*sin((h+  0)*(M_PI/180.0))+0.5),
			255*(0.5*sin((h+120)*(M_PI/180.0))+0.5),
			255*(0.5*sin((h+240)*(M_PI/180.0))+0.5),
			255
		});
		stbi_write_png("test.png", buf->width, buf->height, 4, (uint8_t *)(buf->pixels), buf->width * sizeof(struct Pixel));
		h =  fmod(h+5, 360.0);
		usleep(1000 * 1000/60);
	}
	return 0;
}
