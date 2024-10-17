#pragma once

#include "gui/layout/gui_layout.h"
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>


struct GuiElement {
	struct GuiLayout *parent;
	struct GuiLayout *layout;

	GuiUpdateType update_type;
	bool selectable;
	bool selected;
	void (*delete)(struct GuiElement *self);
	void (*update)(struct GuiElement *self); // Only for GUI_DYNAMIC
	void (*send_input)(struct GuiElement *self);
		
	void *data;
	struct GuiStyle style;
	struct Buffer *buf;

	struct GuiSize _size;
};


void gui_delete_element(struct GuiElement *self);

void gui_propogate_update(struct GuiElement *self, GuiUpdateType type);
void gui_add_child(struct GuiElement *self, struct GuiElement *child);
void gui_remove_child(struct GuiElement *self, struct GuiElement *child);

void gui_set_style_padding_all(struct GuiElement *self, uint32_t size);
void gui_set_style_margin_all(struct GuiElement *self, uint32_t size);
void gui_set_style_padding(struct GuiElement *self, struct Padding padding);
void gui_set_style_margin(struct GuiElement *self, struct Padding margin);

struct GuiSize gui_get_max_internal_size(struct GuiElement *self);

void gui_show(struct GuiElement *self, struct Buffer *buf, uint32_t x, uint32_t y);
