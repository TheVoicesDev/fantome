#include "fantome_state_2d.h"

void FantomeState2D::set_active(const bool p_active) {
    _active = p_active;

    set_process(p_active);
    set_process_internal(p_active);
    set_physics_process(p_active);
    set_physics_process_internal(p_active);
}

bool FantomeState2D::get_active() const {
    return _active;
}

void FantomeState2D::set_priority(const int64_t p_priority) {
    priority = p_priority;
}

int64_t FantomeState2D::get_priority() const {
    return priority;
}

void FantomeState2D::set_relative_to_set(const bool p_value) {
    relative_to_set = p_value;
}

bool FantomeState2D::get_relative_to_set() const {
    return relative_to_set;
}

void FantomeState2D::enter_controller(FantomeStateController2D* p_controller) {
    if (!p_controller)
        return;
    
    _controller = p_controller;
    GDVIRTUAL_CALL(_enter_controller);
}

void FantomeState2D::exit_controller() {
    if (!_controller)
        return;

    GDVIRTUAL_CALL(_exit_controller);
    _controller = nullptr;
}

FantomeStateController2D* FantomeState2D::get_controller() const {
    return _controller;
}

FantomeCharacter2D* FantomeState2D::get_character() const {
    return _controller->get_character();
}

FantomeStateSet2D* FantomeState2D::get_state_set() const {
    return _state_set;
}

bool FantomeState2D::can_switch() {
    bool ret = false;
    GDVIRTUAL_CALL(_can_switch, ret);
    return ret;
}

bool FantomeState2D::is_finished() {
    bool ret = false;
    GDVIRTUAL_CALL(_is_finished, ret);
    return ret;
}

void FantomeState2D::begin(const Dictionary &p_states) {
    GDVIRTUAL_CALL(_begin, p_states);
}

void FantomeState2D::end(const Dictionary &p_states) {
    GDVIRTUAL_CALL(_end, p_states);
}

PackedStringArray FantomeState2D::get_configuration_warnings() const {
    PackedStringArray warnings = Node::get_configuration_warnings();

    if (_controller == nullptr && _state_set == nullptr)
        warnings.push_back(RTR("This state isn't registered to a state set OR a controller. Consider parenting this node to a FantomeStateSet2D or FantomeStateController3D."));
    
    return warnings;
}

bool FantomeState2D::compare_by_priority(const Variant &p_a, const Variant &p_b) {
    FantomeState2D* state_a = Object::cast_to<FantomeState2D>(p_a);
    FantomeState2D* state_b = Object::cast_to<FantomeState2D>(p_b);
    if (state_a != nullptr && state_b != nullptr)
        return state_a->priority < state_b->priority;
    
    return p_a < p_b;
}

void FantomeState2D::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_READY: {
            set_active(get_active());
        } break;
        case NOTIFICATION_PARENTED: {
            _controller = Object::cast_to<FantomeStateController2D>(get_parent());
            if (_controller) {
                enter_controller(_controller);
                return;
            }
            
            _state_set = Object::cast_to<FantomeStateSet2D>(get_parent());
        } break;
        case NOTIFICATION_UNPARENTED: {
            exit_controller();
            _state_set = nullptr;
        } break;
    }
}

void FantomeState2D::_bind_methods() {
    // Getters and Setters
    ClassDB::bind_method(D_METHOD("set_active", "active"), &FantomeState2D::set_active);
    ClassDB::bind_method("get_active", &FantomeState2D::get_active);
    ClassDB::bind_method(D_METHOD("set_priority", "priority"), &FantomeState2D::set_priority);
    ClassDB::bind_method("get_priority", &FantomeState2D::get_priority);
    ClassDB::bind_method(D_METHOD("set_relative_to_set", "value"), &FantomeState2D::set_relative_to_set);
    ClassDB::bind_method("get_relative_to_set", &FantomeState2D::get_relative_to_set);

    // Properties
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "active"), "set_active", "get_active");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "priority"), "set_priority", "get_priority");
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "relative_to_set"), "set_relative_to_set", "get_relative_to_set");

    // Methods
    ClassDB::bind_method("get_controller", &FantomeState2D::get_controller);
    ClassDB::bind_method("get_character", &FantomeState2D::get_character);
    ClassDB::bind_method("get_state_set", &FantomeState2D::get_state_set);

    ClassDB::bind_static_method("FantomeState2D", D_METHOD("compare_by_priority", "a", "b"), &FantomeState2D::compare_by_priority);

    // Virtual Methods
    GDVIRTUAL_BIND(_enter_controller)
    GDVIRTUAL_BIND(_exit_controller)

    GDVIRTUAL_BIND(_can_switch)
    GDVIRTUAL_BIND(_is_finished)

    GDVIRTUAL_BIND(_begin, "states")
    GDVIRTUAL_BIND(_end, "states")
}