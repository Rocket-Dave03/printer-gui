#include "gui/gui_element.h"
#include <stdlib.h>
#include <assert.h>

void gui_delete_element(struct GuiElement *elem) {
	if (elem == NULL) {
		return;
	}
	free(elem->data);
	elem->data = NULL;
	free(elem);
}

void gui_propogate_update(struct GuiElement *elem, GuiUpdateType type) {
	assert(type != GUI_UPDATE_STATIC);
	
}
