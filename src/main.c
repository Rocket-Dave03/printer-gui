#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <math.h>

#include "buffer.h"
#include "gui/gui_box.h"
#include "pixel.h"
#include "gui/gui_element.h"

#include "stb_image_write.h"

struct GuiElement *main_element;


int main() {
	struct Buffer *render_buffer = create_buffer(240, 320);
	if (render_buffer == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		return 1;
	}

	struct GuiElement *box = gui_box_create(NULL,100,100);

	float h = 0.0;
	while (1) {
		fill_buffer(render_buffer, (struct Pixel){51,51,51,255});
		
		stbi_write_png("/run/user/1000/test.png", render_buffer->width, render_buffer->height, 4, (render_buffer->pixels), render_buffer->width * sizeof(struct Pixel));
		h = fmod(h+5, 360.0);
		usleep(1000 * 1000/60);
	}
	delete_buffer(render_buffer);
	return 0;
}
