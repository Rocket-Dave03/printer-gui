#include "gui/gui_box.h"
#include "buffer.h"
#include "gui/gui_element.h"

#include <stdio.h>
#include <stdlib.h>

struct GuiElement *gui_box_create(struct GuiElement *parent, uint width, uint height, struct Pixel fill_color) {
	struct GuiElement *elem = malloc(sizeof(struct GuiElement));
	if (elem == NULL) {
		fprintf(stderr, "Failed to create gui_box");
		return NULL;
	}
	elem->parent = parent;
	elem->selectable = false;
	elem->selected = false;
	elem->update = NULL;
	elem->send_input = NULL;
	elem->data = NULL;
	elem->childCount = 0;
	elem->children = NULL;

	struct Buffer *buf = create_buffer(width, height);
	if (buf == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		free(elem);
		return  NULL;
	}
	fill_buffer(buf, fill_color);
	elem->buf = buf;
	return elem;
}
