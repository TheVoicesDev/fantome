#include "fantome_state_set_2d.h"

TypedArray<FantomeState2D> FantomeStateSet2D::get_states() const {
    return states.duplicate().create_read_only();
}

void FantomeStateSet2D::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_PARENTED: {
            _controller = Object::cast_to<FantomeStateController2D>(get_parent());
            if (_controller) {
                
            }
        } break;
        case NOTIFICATION_UNPARENTED: {

        } break;
    }
}