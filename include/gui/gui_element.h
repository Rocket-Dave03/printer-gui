#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

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

struct Padding {
	uint left;
	uint right;
	uint up;
	uint down;
};

struct GuiStyle {
	struct Padding padding;
	struct Padding margin;
};

struct GuiSize {
	uint width;
	uint height;
};

struct GuiElement {
	struct GuiElement *parent;

	GuiUpdateType update_type;
	bool selectable;
	bool selected;
	void (*update)(struct GuiElement *self); // Only for GUI_DYNAMIC
	void (*send_input)(struct GuiElement *self);
		
	void *data;
	struct GuiStyle style;
	struct Buffer *buf;

	uint32_t _childCount;
	struct GuiElement **_children;
	struct GuiSize _size;
};


void gui_delete_element(struct GuiElement *elem);

void gui_propogate_update(struct GuiElement *elem, GuiUpdateType type);
