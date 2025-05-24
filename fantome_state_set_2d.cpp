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

FantomeStateController2D* FantomeStateSet2D::get_controller() const {
    return _controller;
}

PackedStringArray FantomeStateSet2D::get_configuration_warnings() const {
    PackedStringArray warnings = Node::get_configuration_warnings();

    if (states.size() <= 0)
        warnings.push_back(RTR("This state set doesn't have any states registered as children, so it will do nothing by itself. Consider adding nodes inheriting FantomeStateSet2D as children."));
    
    return warnings;
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

void FantomeStateSet2D::_bind_methods() {
    ClassDB::bind_method("get_states", &FantomeStateSet2D::get_states);
    ClassDB::bind_method("update_states", &FantomeStateSet2D::update_states);

    ClassDB::bind_method("get_controller", &FantomeStateSet2D::get_controller);
}