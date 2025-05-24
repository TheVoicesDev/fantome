#include "fantome_state_controller_2d.h"
#include "core/variant/array.h"

FantomeCharacter2D* FantomeStateController2D::get_character() const {
    return _character;
}

void FantomeStateController2D::update_states() {
    _state_map.clear();
    _state_list.clear();

    TypedArray<Node> children = get_children();
    int i;

    for (i = 0; i < children.size(); i++) {
        FantomeStateSet2D* state_set = Object::cast_to<FantomeStateSet2D>(children[i]);
        if (state_set) {
            for (int s = 0; s < state_set->states.size(); s++) {
                FantomeState2D* cur_state = Object::cast_to<FantomeState2D>(state_set->states[s]);
                if (!cur_state)
                    continue;

                _state_list.append(cur_state);
            }
        }

        FantomeState2D* state = Object::cast_to<FantomeState2D>(children[i]);
        if (state)
            _state_list.append(state);
    }

    _state_list = _sort_states(_state_list); // uses merge sort for priority stuff
    for (i = 0; i < _state_list.size(); i++) {
        FantomeState2D* state = Object::cast_to<FantomeState2D>(_state_list[i]);
        if (!state || _state_map.has(state->get_name()))
            continue;
        
        _state_map.set(state->get_name(), state);
    }
}

PackedStringArray FantomeStateController2D::get_configuration_warnings() const {
    PackedStringArray warnings = Node::get_configuration_warnings();

    if (_character == nullptr)
        warnings.push_back(RTR("This state controller isn't parented to a character so it can't process states properly. Consider parenting this state controller to a character."));
    
    return warnings;
}

TypedArray<FantomeState2D> FantomeStateController2D::_sort_states(const TypedArray<FantomeState2D> &p_array) const {
    if (p_array.size() <= 1)
        return p_array;
    
    int mid = p_array.size() / 2;
    TypedArray<FantomeState2D> left = _sort_states(p_array.slice(0, mid));
    TypedArray<FantomeState2D> right = _sort_states(p_array.slice(mid, p_array.size()));
    return _merge_state_array(left, right);
}

TypedArray<FantomeState2D> FantomeStateController2D::_merge_state_array(const TypedArray<FantomeState2D> &p_left, const TypedArray<FantomeState2D> &p_right) const {
    TypedArray<FantomeState2D> result;
    int i = 0; int j = 0;
    while (i < p_left.size() && j < p_right.size()) {
        FantomeState2D* left = Object::cast_to<FantomeState2D>(p_left[i]);
        FantomeState2D* right = Object::cast_to<FantomeState2D>(p_right[j]);
        if (left->priority < right->priority) {
            result.append(left);
            i++;
        } else {
            result.append(right);
            j++;
        }
    }

    while (i < p_left.size()) {
        FantomeState2D* left = Object::cast_to<FantomeState2D>(p_left[i]);
        result.append(left);
        i++;
    }   

    while (j < p_right.size()) {
        FantomeState2D* right = Object::cast_to<FantomeState2D>(p_right[j]);
        result.append(right);
        j++;
    }

    return result;
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