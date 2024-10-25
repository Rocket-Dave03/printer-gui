#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#include "buffer.h"
#include "freetype/fttypes.h"
#include "gui/gui_box.h"
#include "gui/layout/gui_layout_vertical.h"
#include "gui/layout/gui_layout_horizontal.h"
#include "pixel.h"
#include "gui/gui_element.h"

#include "stb_image_write.h"

#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library freetype;
FT_Face font;

struct GuiElement *main_element;


int main() {

	// Setup freetype
	FT_Error err = FT_Init_FreeType(&freetype);
	if (err != FT_Err_Ok) {
		fprintf(stderr, "Failed to init freetype: %s", FT_Error_String(err));
		return 1;
	}
	

	struct Buffer *render_buffer = create_buffer(240, 320);
	if (render_buffer == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		return 1;
	}
	struct GuiElement *box = gui_box_create(NULL,(struct Pixel){51,51,51,255});
	gui_layout_vertical_create(box);
	{ 
		box->style.padding.left = 5;
		box->style.padding.right = 5;

		struct GuiElement *row_1 = gui_box_create(box, (struct Pixel){150,100,100,255});
		gui_layout_horizontal_create(row_1);
		gui_box_create(row_1, (struct Pixel){150, 50, 50,255});
		gui_box_create(row_1, (struct Pixel){150, 90, 90,255});
		// gui_box_create(row_1, (struct Pixel){150,120,120,255});

		struct GuiElement *row_2 = gui_box_create(box, (struct Pixel){100,150,100,255});
		gui_layout_horizontal_create(row_2);
		gui_box_create(row_2, (struct Pixel){ 50,150, 50,255});
		// gui_box_create(row_2, (struct Pixel){ 90,150, 90,255});
		// gui_box_create(row_2, (struct Pixel){120,150,120,255});

		struct GuiElement *row_3 = gui_box_create(box, (struct Pixel){100,100,150,255});
		gui_layout_horizontal_create(row_3);
		gui_box_create(row_3, (struct Pixel){ 50, 50,150,255});
		gui_box_create(row_3, (struct Pixel){ 90, 90,150,255});
		gui_box_create(row_3, (struct Pixel){120,120,150,255});
	}
	gui_propogate_update(box, GUI_UPDATE_STATIC);



	while (1) {
		fill_buffer(render_buffer, (struct Pixel){0,0,0,255});
		gui_show(box, render_buffer, 0, 0);
		
		stbi_write_png("/run/user/1000/test.png", render_buffer->width, render_buffer->height, 4, (render_buffer->pixels), render_buffer->width * sizeof(struct Pixel));
		usleep(1000 * 1000/60);
		break;
	}
	gui_delete_element(box);
	delete_buffer(render_buffer);
	return 0;
}
