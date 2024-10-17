#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#include "buffer.h"
#include "gui/gui_box.h"
#include "gui/layout/gui_layout_vertical.h"
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

	struct GuiElement *box = gui_box_create(NULL,(struct Pixel){51,51,51,255});
	gui_layout_vertical_create(box);
	gui_propogate_update(box, GUI_UPDATE_STATIC);
	gui_box_create(box, (struct Pixel){100,150,100,255});
	gui_box_create(box, (struct Pixel){150,100,100,255});
	gui_box_create(box, (struct Pixel){100,100,150,255});


	while (1) {
		fill_buffer(render_buffer, (struct Pixel){0,0,0,255});
		gui_show(box, render_buffer, 0, 0);
		
		stbi_write_png("/run/user/1000/test.png", render_buffer->width, render_buffer->height, 4, (render_buffer->pixels), render_buffer->width * sizeof(struct Pixel));
		usleep(1000 * 1000/60);
	}
	gui_delete_element(box);
	delete_buffer(render_buffer);
	return 0;
}
