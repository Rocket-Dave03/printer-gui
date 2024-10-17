#pragma once

#include "gui/gui_element.h"
#include "gui/layout/gui_layout.h"


struct GuiLayout *gui_layout_vertical_create(struct GuiElement *parent);
struct LayoutPos gui_layout_vertical_get_child_position(struct GuiLayout *self, uint32_t child_idx);
struct GuiSize gui_layout_vertical_get_child_size(struct GuiLayout *self, uint32_t child_idx);
