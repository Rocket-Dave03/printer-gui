#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "buffer.h"
#include "font.h"
#include "gui/gui_box.h"
#include "gui/gui_element.h"
#include "gui/gui_lable.h"
#include "gui/layout/gui_layout_horizontal.h"
#include "gui/layout/gui_layout_vertical.h"
#include "pixel.h"

#include "3rdparty/stb_image_write.h"

struct GuiElement *main_element;
struct termios initial_state;

#include <assert.h>
#include <termios.h>

void reset_terminal() { tcsetattr(0, TCSAFLUSH, &initial_state); }

void prepare_term() {
	struct termios term = {};
	memcpy(&term, &initial_state, sizeof(struct termios));

	term.c_lflag &= ~(ECHO | ICANON);

	tcsetattr(0, TCSANOW, &term);
}

char read_char() {
	char c;
	read(0, &c, 1);
	return c;
}

int main() {
	tcgetattr(0, &initial_state);
	atexit(reset_terminal);

	prepare_term();

	init_freetype();
	load_font(get_font_file());
	struct Buffer *render_buffer = create_buffer(240, 320);
	if (render_buffer == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		return 1;
	}
	struct GuiElement *box = gui_box_create(NULL, (struct Pixel){51, 51, 51, 255});
	gui_layout_vertical_create(box);
	{
		box->style.padding.left = 5;
		box->style.padding.right = 5;

		struct GuiElement *row_1 = gui_box_create(box, (struct Pixel){150, 100, 100, 255});
		gui_layout_horizontal_create(row_1);
		gui_box_create(row_1, (struct Pixel){150, 50, 50, 255});
		gui_box_create(row_1, (struct Pixel){150, 90, 90, 255});
		// gui_box_create(row_1, (struct Pixel){150,120,120,255});

		struct GuiElement *row_2 = gui_box_create(box, (struct Pixel){100, 150, 100, 255});
		gui_layout_horizontal_create(row_2);
		gui_lable_create(row_2, (struct Pixel){50, 150, 50, 255}, "C'est bonne`s");
		// gui_box_create(row_2, (struct Pixel){ 90,150, 90,255});
		// gui_box_create(row_2, (struct Pixel){120,150,120,255});

		struct GuiElement *row_3 = gui_box_create(box, (struct Pixel){100, 100, 150, 255});
		gui_layout_horizontal_create(row_3);
		gui_box_create(row_3, (struct Pixel){50, 50, 150, 255});
		gui_box_create(row_3, (struct Pixel){90, 90, 150, 255});
		gui_box_create(row_3, (struct Pixel){120, 120, 150, 255});
	}
	gui_propogate_update(box, GUI_UPDATE_STATIC);

	while (1) {
		char c = read_char();
		// printf("char: %c = %d\n\r", c, (int)c);
		if (c == 3) {
			return 0;
		}
		if (c == '\n' || c == ' ') {
			printf("CLICK!\n");
		}

		if (c == 27) {
			c = read_char();
			if (c == '[') {
				c = read_char();
				if (c == 'A') {
					printf("UP!\n");
				}
				if (c == 'B') {
					printf("DOWN!\n");
				}
			}
		}

		fill_buffer(render_buffer, (struct Pixel){0, 0, 0, 255});
		gui_show(box, render_buffer, 0, 0);

		stbi_write_png("/run/user/1000/test.png", render_buffer->width, render_buffer->height, 4,
					   (render_buffer->pixels), render_buffer->width * sizeof(struct Pixel));
		usleep(1000 * 1000 / 60);
		// break;
	}
	gui_delete_element(box);
	delete_buffer(render_buffer);
	return 0;
}
