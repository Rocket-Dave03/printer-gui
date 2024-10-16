#pragma once

#include "gui/gui_element.h"
#include "pixel.h"
#include <sys/types.h>

struct GuiElement *gui_box_create(struct GuiElement *parent, uint32_t width, uint32_t height, struct Pixel);
// Only to be run on creation
void gui_box_update(struct GuiElement *self);
