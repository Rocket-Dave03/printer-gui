#include "gui/layout/gui_layout.h"
#include "buffer.h"
#include "gui/gui_element.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void layout_delete(struct GuiLayout *self) {
	if (self == NULL) {
		return;
	}
	for (int i = 0; i < self->_childCount; i++) {
		free(self->_children[i]);
	}
	free(self->_children);
	free(self);
}

void layout_show(struct GuiLayout *self, struct Buffer *buf, uint32_t x, uint32_t y) {
	for (uint32_t i = 0; i < self->_childCount; i++) {
		struct GuiElement *child = self->_children[i];
		struct LayoutPos child_pos = self->get_child_position(self, i);
		uint32_t child_x = child_pos.x;
		uint32_t child_y = child_pos.y;
		gui_show(
			child,
			buf, 
			x + child_x, 
			y + child_y
		);
	}
}


void layout_add_child(struct GuiLayout *self, struct GuiElement *child) {
	struct GuiElement ** new_children = reallocarray(self->_children, self->_childCount+1, sizeof(struct GuiElement *));
	if (new_children == NULL) {
		fprintf(stderr, "Failed to reallocarray for to add layout children");
		return;
	}
	self->_children = new_children;
	self->_children[self->_childCount] = child;
	self->_childCount += 1;
	child->parent = self;
	layout_send_update(self);
}

void layout_remove_child_ptr(struct GuiLayout *self, struct GuiElement *child) {
	layout_remove_child_idx(
		self, 
		layout_get_child_index(self, child)
	);
}

void layout_remove_child_idx(struct GuiLayout *self, uint32_t child_idx) {
	if (self->_childCount == 0) {
		return;
	}
	if (child_idx >= self->_childCount) {
		return;
	}

	if (self->_childCount == 1) {
		self->_children[0] = NULL;
	} else {
		memmove(
			self->_children[child_idx+1], 
			self->_children[child_idx], 
			sizeof(struct GuiElement *) * (self->_childCount - 1 - child_idx) 
		); 
	}
	self->_childCount -= 1;
	self->_children = reallocarray(self->_children, sizeof(struct GuiElement *), self->_childCount);
	layout_send_update(self);
}

struct GuiElement *layout_get_child(struct GuiLayout *self, uint32_t index) {
	return self->_children[index];
}

uint32_t layout_get_child_index(struct GuiLayout *self, struct GuiElement *child) {
	if (child != NULL) {
		for (uint32_t i = 0; i < self->_childCount; i++) {
			if (self->_children[i] == child) {
				return i;
			}
		}
	}
	return LAYOUT_INDEX_NOTFOUND;
}


struct LayoutPos layout_get_child_position(struct GuiLayout *self, uint32_t child_idx) {
	return self->get_child_position(self, child_idx);
}

struct GuiSize layout_get_child_size(struct GuiLayout *self, uint32_t child_idx) {
	return self->get_child_size(self, child_idx);
}


void layout_send_update(struct GuiLayout *self) {
	for(uint32_t i = 0; i < self->_childCount; i++) {
		struct GuiElement *child = self->_children[i];
		if (child->update != NULL) {
			child->update(child);
		}
	}
}
