#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t GuiUpdateType;

#define GUI_UPDATE_STATIC		((GuiUpdateType)1)
#define GUI_UPDATE_INPUT		((GuiUpdateType)2)
#define GUI_UPDATE_PER_FRAME	((GuiUpdateType)3)
#define GUI_UPDATE_PER_SECOND	((GuiUpdateType)4)


enum GuiInput {
	WHEEL_LEFT,
	WHEEL_RIGHT,
	WHEEL_PRESS,
};

struct GuiElement {
	struct GuiElement *parent;

	GuiUpdateType update_type;
	bool selectable;
	bool selected;
	void (*update)(struct GuiElement *self); // Only for GUI_DYNAMIC
	void (*send_input)(struct GuiElement *self);
		
	void *data;

	struct Buffer *buf;
	uint32_t childCount;
	struct GuiElement *children;
};


void gui_delete_element(struct GuiElement *elem);

void gui_propogate_update(struct GuiElement *elem, GuiUpdateType type);
