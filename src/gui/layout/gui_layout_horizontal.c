#include "gui/layout/gui_layout_horizontal.h"
#include "gui/layout/gui_layout.h"
#include "gui/gui_element.h"

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct GuiLayout *gui_layout_horizontal_create(struct GuiElement *parent) {
	struct GuiLayout *self = malloc(sizeof(struct GuiLayout));
	memset(self, 0, sizeof(struct GuiLayout));

	self->parent = parent;
	parent->layout = self;
	self->_children = 0;
	self->_childCount = 0;

	self->get_child_position = gui_layout_horizontal_get_child_position;
	self->get_child_size = gui_layout_horizontal_get_child_size;

	gui_propogate_update(parent, GUI_UPDATE_STATIC);
	return self;
}

struct LayoutPos gui_layout_horizontal_get_child_position(struct GuiLayout *self, uint32_t child_idx) {
	struct LayoutPos pos = {self->parent->style.padding.left, self->parent->style.padding.top};
	uint32_t current_idx = 0;
	while(current_idx <= child_idx) {
		struct GuiElement *child = self->_children[current_idx];
		if (current_idx == child_idx) {
			pos.x += child->style.margin.left;
			pos.y += child->style.margin.top;
		} else {
			struct GuiSize child_size = self->get_child_size(self,current_idx);
			pos.x += child->style.margin.left;
			pos.x += child->style.padding.left;
			pos.x += child_size.width;
			pos.x += child->style.padding.right;
			pos.x += child->style.margin.right;
		}
		current_idx += 1;
	}
	return pos;
}


struct GuiSize gui_layout_horizontal_get_child_size(struct GuiLayout *self, uint32_t child_idx) {
	struct GuiSize total_size = gui_get_max_internal_size(self->parent);
	struct GuiElement *child = self->_children[child_idx];
	struct Padding margin = child->style.margin;

	uint32_t padding_h = self->parent->style.padding.left + self->parent->style.padding.right;
	uint32_t padding_v = self->parent->style.padding.top + self->parent->style.padding.bottom;

	uint ret_x = (total_size.width / self->_childCount) - margin.left - margin.right - padding_h;
	uint ret_y = (total_size.height) - margin.top - margin.bottom - padding_v;
	return (struct GuiSize) {
		ret_x,
		ret_y,
	};
}
