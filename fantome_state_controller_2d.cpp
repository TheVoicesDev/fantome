#include "fantome_state_controller_2d.h"
#include "core/variant/array.h"

FantomeCharacter2D* FantomeStateController2D::get_character() const {
    return _character;
}

void FantomeStateController2D::update_states() {
    _states.clear();

    TypedArray<Node> children = get_children();
    for (int c = 0; c < children.size(); c++) {
    FantomeStateSet2D* state_set = Object::cast_to<FantomeStateSet2D>(children[c]);
    if (state_set) {
        for (int s = 0; s < state_set->states.size(); s++) {
            FantomeState2D* cur_state = Object::cast_to<FantomeState2D>(state_set->states[s]);
            if (!cur_state)
                continue;

            _states.set(cur_state->get_name(), cur_state);
        }
    }

    FantomeState2D* state = Object::cast_to<FantomeState2D>(children[c]);
        if (state) 
            _states.set(state->get_name(), state);
    }
}

PackedStringArray FantomeStateController2D::get_configuration_warnings() const {
    PackedStringArray warnings = Node::get_configuration_warnings();

    if (_character == nullptr)
        warnings.push_back(RTR("This state controller isn't parented to a character so it can't process states properly. Consider parenting this state controller to a character."));
    
    return warnings;
}

void FantomeStateController2D::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_PARENTED: {
            _character = Object::cast_to<FantomeCharacter2D>(get_parent());
            if (_character)
                _character->set_controller(this);
        } break;
        case NOTIFICATION_UNPARENTED: {
            if (_character)
                _character->set_controller(nullptr);

            _character = nullptr;
        } break;
        case NOTIFICATION_CHILD_ORDER_CHANGED: {
            update_states();
        } break;
    }
}