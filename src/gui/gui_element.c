#include "gui/gui_element.h"
#include <stdlib.h>
#include <assert.h>

void gui_delete_element(struct GuiElement *self) {
	if (self == NULL) {
		return;
	}
	for(int i = 0; i < self->_childCount; i++) {
		gui_delete_element(self->_children[i]);
	}
	free(self->data);
	self->data = NULL;
	free(self);
}

void gui_propogate_update(struct GuiElement *elem, GuiUpdateType type) {
	assert(type != GUI_UPDATE_STATIC);
	// TODO: Complete	
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
