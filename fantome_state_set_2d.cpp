#include "fantome_state_set_2d.h"

TypedArray<FantomeState2D> FantomeStateSet2D::get_states() const {
    return states;
}

void FantomeStateSet2D::update_states() {
    TypedArray<FantomeState2D> new_states;

    TypedArray<Node> children = get_children();
    for (int c = 0; c < children.size(); c++) {
        FantomeState2D* state = Object::cast_to<FantomeState2D>(children[c]);
        if (!state)
            continue;
        
        new_states.push_back(state);
    }

    new_states.make_read_only();
    states = new_states;

    if (_controller)
        _controller->update_states();
}

void FantomeStateSet2D::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_PARENTED: {
            _controller = Object::cast_to<FantomeStateController2D>(get_parent());
            for (int s = 0; s < states.size(); s++) {
                FantomeState2D* state = Object::cast_to<FantomeState2D>(states[s]);
                state->enter_controller(_controller);
            }
        } break;
        case NOTIFICATION_UNPARENTED: {
            if (!_controller)
                break;
            
            for (int s = 0; s < states.size(); s++) {
                FantomeState2D* state = Object::cast_to<FantomeState2D>(states[s]);
                state->exit_controller();
            }

            _controller = nullptr;
        } break;
        case NOTIFICATION_CHILD_ORDER_CHANGED: {
            update_states();
        } break;
    }
}