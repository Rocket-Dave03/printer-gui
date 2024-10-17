#include "gui/gui_box.h"
#include "buffer.h"
#include "gui/gui_element.h"
#include "gui/layout/gui_layout.h"
#include "pixel.h"

#include <stdio.h>
#include <stdlib.h>


struct GuiBoxData {
	struct Pixel color;
};


struct GuiElement *gui_box_create(struct GuiElement *parent, struct Pixel fill_color) {
	struct GuiElement *elem = malloc(sizeof(struct GuiElement));
	if (elem == NULL) {
		fprintf(stderr, "Failed to create gui_box");
		return NULL;
	}

	elem->selectable = false;
	elem->selected = false;
	elem->send_input = NULL;
	elem->layout = NULL;

	elem->update_type = GUI_UPDATE_STATIC;
	elem->update = gui_box_update;
	elem->delete = NULL;

	elem->data = malloc(sizeof(struct GuiBoxData));
	if (elem->data == NULL) {
		fprintf(stderr, "Failed to allocat memory");
	}
	((struct GuiBoxData*)elem->data)->color = fill_color;

	elem->style = (struct GuiStyle){
		{5,5,5,5},
		{0,0,0,0},
	};

	struct Buffer *buf = create_buffer(32, 32);
	elem->_size = (struct GuiSize){32,32};
	if (buf == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		free(elem);
		return  NULL;
	}
	elem->buf = buf;
	if (parent != NULL) {
		elem->parent = parent->layout;
		layout_add_child(parent->layout, elem);
	}
	return elem;
}

void gui_box_update(struct GuiElement *self) {
	if (self->parent == NULL) {
		self->style.margin = (struct Padding){0,0,0,0};
		resize_buffer(
			self->buf,
			240 - (self->style.margin.left + self->style.margin.right),
			320 - (self->style.margin.top + self->style.margin.bottom)
		);
	} else {
		uint32_t child_idx = layout_get_child_index(self->parent, self);
		if (child_idx == LAYOUT_INDEX_NOTFOUND) {
			fprintf(stderr, "Couln't get child index from pointer\n");
		}
		struct GuiSize size = layout_get_child_size(self->parent, child_idx);
		int ret = resize_buffer(
			self->buf,
			size.width - (self->style.margin.left + self->style.margin.right),
			size.height - (self->style.margin.top + self->style.margin.bottom)
		);
		if (ret == -1) {
			gui_delete_element(self);
			fprintf(stderr, "Failed to resize buffer\n");
			return;
		}
	}
	fill_buffer(self->buf, ((struct GuiBoxData *)self->data)->color);
	self->_size.width = self->buf->width;
	self->_size.height = self->buf->height;
}
