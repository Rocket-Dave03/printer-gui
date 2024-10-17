#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "buffer.h"
#include "gui/gui_types.h"
#include "gui/gui_element.h"

#define LAYOUT_INDEX_NOTFOUND UINT32_MAX

struct LayoutPos {
	uint32_t x;
	uint32_t y;
};

struct GuiLayout {
	struct GuiElement *parent;
	uint32_t _childCount;
	struct GuiElement **_children;

	struct LayoutPos(* get_child_position)(struct GuiLayout *self, uint32_t child_idx);
	struct GuiSize(* get_child_size)(struct GuiLayout *self, uint32_t child_idx);
};

void layout_delete(struct GuiLayout *self);
void layout_show(struct GuiLayout *self, struct Buffer *buf, uint32_t x, uint32_t y);

void layout_add_child(struct GuiLayout *self, struct GuiElement *child);
void layout_remove_child_ptr(struct GuiLayout *self, struct GuiElement *child);
void layout_remove_child_idx(struct GuiLayout *self, uint32_t child_idx);
struct GuiElement *layout_get_child(struct GuiLayout *self, uint32_t index);

uint32_t layout_get_child_index(struct GuiLayout *self, struct GuiElement *child);

struct LayoutPos layout_get_child_position(struct GuiLayout *self, uint32_t child_idx);
struct GuiSize layout_get_child_size(struct GuiLayout *self, uint32_t child_idx);

void layout_send_update(struct GuiLayout *self);
