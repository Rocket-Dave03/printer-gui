#pragma once

#include "gui/gui_element.h"
#include "pixel.h"

struct GuiElement *gui_lable_create(struct GuiElement *parent, struct Pixel, const char *text);
void gui_lable_update(struct GuiElement *self);

