#include <stdlib.h>
#include <assert.h>

#include "buffer.h"
#include "gui/gui_element.h"
#include "gui/layout/gui_layout.h"

void gui_delete_element(struct GuiElement *self) {
	if (self == NULL) {
		return;
	}
	layout_delete(self->layout);
	if (self->parent != NULL) {
		layout_remove_child_ptr(self->parent, self);
	}

	if (self->delete != NULL) {
		self->delete(self);
	}
	free(self->data); 
	self->data = NULL;
	delete_buffer(self->buf);
	self->buf = NULL;
	free(self);
}

void gui_propogate_update(struct GuiElement *elem, GuiUpdateType type) {
	if (elem->update != NULL) {
		elem->update(elem);
	}
	if (elem->layout != NULL) {
		layout_send_update(elem->layout, type);
	}
}




void gui_set_style_padding_all(struct GuiElement *self, uint32_t size) {
	gui_set_style_padding(self, (struct Padding){size,size,size,size});
}

void gui_set_style_margin_all(struct GuiElement *self, uint32_t size) {
	gui_set_style_margin(self, (struct Padding){size,size,size,size});
}


void gui_set_style_padding(struct GuiElement *self, struct Padding padding) {
	self->style.padding = padding;
}

void gui_set_style_margin(struct GuiElement *self, struct Padding margin) {
	self->style.margin = margin;
}


struct GuiSize gui_get_max_internal_size(struct GuiElement *self) {
	uint32_t width = self->_size.width -
		self->style.padding.left -
		self->style.padding.right;

	uint32_t height = self->_size.height - 
		self->style.padding.top - 
		self->style.padding.bottom;

	return (struct GuiSize) {
		width,
		height
	};
}


void gui_show(struct GuiElement *self, struct Buffer *buf, uint32_t x, uint32_t y) {
	write_buffer(
		buf, 
		self->buf, 
		x+self->style.margin.left,
		y+self->style.margin.top
	);
	if (self->layout != NULL) {
		layout_show(
			self->layout, 
			buf, 
			x+self->style.margin.left+self->style.padding.left, 
			y+self->style.margin.top+self->style.padding.top
		);
	}
}
