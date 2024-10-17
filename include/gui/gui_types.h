#pragma once

#include "stdint.h"

#ifndef GUI_TYPES_H
#define GUI_TYPES_H

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
	uint32_t left;
	uint32_t right;
	uint32_t top;
	uint32_t bottom;
};

struct GuiStyle {
	struct Padding padding;
	struct Padding margin;
};

struct GuiSize {
	uint32_t width;
	uint32_t height;
};


#endif //GUI_TYPES_H
