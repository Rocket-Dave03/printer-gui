#include "gui/gui_lable.h"
#include "buffer.h"
#include "font.h"
#include "gui/gui_element.h"
#include "gui/layout/gui_layout.h"
#include "pixel.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct GuiLableData {
	struct Pixel color;
	const char *text;
};

struct GuiElement *gui_lable_create(struct GuiElement *parent, struct Pixel fill_color, const char *text) {
	struct GuiElement *elem = malloc(sizeof(struct GuiElement));
	memset(elem, 0, sizeof(struct GuiElement));

	if (elem == NULL) {
		fprintf(stderr, "Failed to create gui_box");
		return NULL;
	}

	elem->selectable = false;
	elem->selected = false;
	elem->send_input = NULL;
	elem->layout = NULL;

	elem->update_type = GUI_UPDATE_STATIC;
	elem->update = gui_lable_update;
	elem->delete = NULL; // No special cleanup needed

	elem->data = malloc(sizeof(struct GuiLableData));
	if (elem->data == NULL) {
		fprintf(stderr, "Failed to allocate memory");
	}
	((struct GuiLableData *)elem->data)->color = fill_color;
	((struct GuiLableData *)elem->data)->text = text;

	elem->style = (struct GuiStyle){
		{5, 5, 5, 5},
		{0, 0, 0, 0},
	};

	int text_len = strlen(text);
	FontSize size = get_font_size();
	struct Buffer *buf = create_buffer(size.width * text_len, size.height);
	elem->_size = (struct GuiSize){32, 32};
	if (buf == NULL) {
		fprintf(stderr, "Failed to create_buffer");
		free(elem);
		return NULL;
	}
	elem->buf = buf;
	if (parent != NULL) {
		elem->parent = parent->layout;
		layout_add_child(parent->layout, elem);
	}

	struct Buffer *char_buf = create_buffer(size.width, size.height);
	for (int i = 0; i < text_len; i++) {
		write_glyph_to_buffer(text[i], char_buf);
		write_buffer(buf, char_buf, size.width * i, 0);
	}
	delete_buffer(char_buf);

	return elem;
}

void gui_lable_update(struct GuiElement *self) {
	if (self->parent == NULL) {
		self->style.margin = (struct Padding){0, 0, 0, 0};
		resize_buffer(self->buf, 240 - (self->style.margin.left + self->style.margin.right),
					  320 - (self->style.margin.top + self->style.margin.bottom));
	} else {
		uint32_t child_idx = layout_get_child_index(self->parent, self);
		if (child_idx == LAYOUT_INDEX_NOTFOUND) {
			fprintf(stderr, "Couln't get child index from pointer\n");
		}
		struct GuiSize size = layout_get_child_size(self->parent, child_idx);
		int ret = resize_buffer(self->buf, size.width - (self->style.margin.left + self->style.margin.right),
								size.height - (self->style.margin.top + self->style.margin.bottom));
		if (ret == -1) {
			gui_delete_element(self);
			fprintf(stderr, "Failed to resize buffer\n");
			return;
		}
	}
	fill_buffer(self->buf, ((struct GuiLableData *)self->data)->color);
	self->_size.width = self->buf->width;
	self->_size.height = self->buf->height;

	FontSize size = get_font_size();
	const char *text = ((struct GuiLableData *)self->data)->text;
	int text_len = strlen(text);
	struct Buffer *char_buf = create_buffer(size.width, size.height);
	for (int i = 0; i < text_len; i++) {
		write_glyph_to_buffer(text[i], char_buf);
		write_buffer(self->buf, char_buf, size.width * i, 0);
	}
	delete_buffer(char_buf);
}
