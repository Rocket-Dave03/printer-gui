
enum GuiElementFlags {
	GUI_STATIC = 1,
	GUI_INPUT = 2,
	GUI_DYNAMIC = 4,
};

enum GuiElementType {
	BOX,
	TOGGLE_BUTTON,
	LABEL,
	PUSH_BUTTON,
};

enum GuiInput {
	WHEEL_LEFT,
	WHEEL_RIGHT,
	WHEEL_PRESS,
}

struct GuiElement {
	struct GuiElement *parent;
	enum GuiElementFlags flags;
	void (*update)(); // Only for GUI_DYNAMIC
	
};
