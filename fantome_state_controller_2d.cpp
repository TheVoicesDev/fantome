#include "fantome_state_controller_2d.h"
#include "core/variant/array.h"

void FantomeStateController2D::set_initial_state(FantomeState2D* p_value) {
    initial_state = p_value;
}

FantomeState2D* FantomeStateController2D::get_initial_state() const {
    return initial_state;
}

void FantomeStateController2D::set_state_queue(const TypedArray<String> &p_value) {
    state_queue = p_value;
}

TypedArray<String> FantomeStateController2D::get_state_queue() const {
    return state_queue;
}

FantomeCharacter2D* FantomeStateController2D::get_character() const {
    return _character;
}

FantomeState2D* FantomeStateController2D::get_state(const StringName &p_name) const {
    ERR_FAIL_COND_V_MSG(_state_map.has(p_name), nullptr, "State " + p_name + " does not exist.");

    return Object::cast_to<FantomeState2D>(_state_map[p_name]);
}

bool FantomeStateController2D::has_state(const StringName &p_name) const {
    return _state_map.has(p_name);
}

Array FantomeStateController2D::get_state_names() const {
    return _state_map.keys();
}

Array FantomeStateController2D::get_registered_states() const {
    return _state_map.values();
}

Array FantomeStateController2D::get_all_states() const {
    Array list = _state_list.duplicate();
    list.make_read_only();

    return list;
}

void FantomeStateController2D::update_states() {
    TypedArray<FantomeState2D> was_active;
    int i;
    for (i = 0; i < _state_list.size(); i++) {
        FantomeState2D* state = Object::cast_to<FantomeState2D>(_state_list[i]);
        if (state && state->get_active())
            was_active.append(state);
    }

    _state_map.clear();
    _state_list.clear();

    TypedArray<Node> children = get_children();
    for (i = 0; i < children.size(); i++) {
        FantomeStateSet2D* state_set = Object::cast_to<FantomeStateSet2D>(children[i]);
        if (state_set) {
            for (int s = 0; s < state_set->states.size(); s++) {
                FantomeState2D* cur_state = Object::cast_to<FantomeState2D>(state_set->states[s]);
                if (!cur_state)
                    continue;

                _state_list.append(cur_state);
                cur_state->set_active(false);
            }
        }

        FantomeState2D* state = Object::cast_to<FantomeState2D>(children[i]);
        if (state) {
            _state_list.append(state);
            state->set_active(false);
        }
    }

    _state_list = _sort_states(_state_list); // uses merge sort for priority stuff
    for (i = 0; i < _state_list.size(); i++) {
        FantomeState2D* state = Object::cast_to<FantomeState2D>(_state_list[i]);
        if (!state || _state_map.has(state->get_name()))
            continue;
        
        _state_map.set(state->get_name(), state);
        state->set_active(was_active.has(state));
    }
}

void FantomeStateController2D::change_current_state(const StringName &p_state_name) {
    ERR_FAIL_COND_MSG(!_state_map.has(p_state_name), "State " + p_state_name + " does not exist.");
    FantomeState2D *previous_state, *next_state;

    previous_state = _current_state;
    next_state = Object::cast_to<FantomeState2D>(_state_map[p_state_name]);

    if (previous_state) {
        _state_parameters.set("previous_state", Variant());
        _state_parameters.set("next_state", next_state);

        previous_state->end(_state_parameters);
        previous_state->set_active(false);
    }
    
    _current_state = next_state;
    _state_parameters.set("previous_state", previous_state);
    _state_parameters.set("next_state", Variant());
    _current_state->begin(_state_parameters);
    _current_state->create_queue();

    _current_state->set_active(true);
}

void FantomeStateController2D::set_current_state(const StringName &p_state_name) {
    if (get_current_state_name() == p_state_name)
        return;
    
    change_current_state(p_state_name);
}

FantomeState2D* FantomeStateController2D::get_current_state() const {
    return _current_state;
}

StringName FantomeStateController2D::get_current_state_name() const {
    return _current_state ? _current_state->get_name() : StringName();
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
        case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
            if (Engine::get_singleton()->is_editor_hint() || state_queue.size() == 0)
                return;

            StringName next_state;
            if (!_current_state || (_current_state && _current_state->is_finished()))
                next_state = StringName(state_queue.pop_front());

            if (next_state.is_empty())
                return;

            change_current_state(next_state);
        } break;
        case NOTIFICATION_READY: {
            if (Engine::get_singleton()->is_editor_hint())
                return;
            
            set_physics_process(true);
            set_physics_process_internal(true);
            
            ERR_FAIL_COND_MSG(initial_state == nullptr, "No initial state set for this controller!");
            change_current_state(initial_state->get_name());
        } break;
    }
}

void FantomeStateController2D::_bind_methods() {
    // Getters and Setters
    ClassDB::bind_method(D_METHOD("set_initial_state", "value"), &FantomeStateController2D::set_initial_state);
    ClassDB::bind_method("get_initial_state", &FantomeStateController2D::get_initial_state);
    ClassDB::bind_method(D_METHOD("set_state_queue", "value"), &FantomeStateController2D::set_state_queue);
    ClassDB::bind_method("get_state_queue", &FantomeStateController2D::get_state_queue);

    // Properties
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "initial_state", PROPERTY_HINT_NODE_TYPE, "FantomeState2D"), "set_initial_state", "get_initial_state");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "state_queue", PROPERTY_HINT_ARRAY_TYPE, "String"), "set_state_queue", "get_state_queue");

    // Methods
    ClassDB::bind_method("get_character", &FantomeStateController2D::get_character);

    ClassDB::bind_method(D_METHOD("get_state", "name"), &FantomeStateController2D::get_state);
    ClassDB::bind_method(D_METHOD("has_state", "name"), &FantomeStateController2D::has_state);

    ClassDB::bind_method("get_state_names", &FantomeStateController2D::get_state_names);
    ClassDB::bind_method("get_registered_states", &FantomeStateController2D::get_registered_states);
    ClassDB::bind_method("get_all_states", &FantomeStateController2D::get_all_states);

    ClassDB::bind_method("update_states", &FantomeStateController2D::update_states);

    ClassDB::bind_method(D_METHOD("change_current_state", "state_name"), &FantomeStateController2D::change_current_state);
    ClassDB::bind_method(D_METHOD("set_current_state", "state_name"), &FantomeStateController2D::set_current_state);
    ClassDB::bind_method("get_current_state", &FantomeStateController2D::get_current_state);
    ClassDB::bind_method("get_current_state_name", &FantomeStateController2D::get_current_state_name);
}