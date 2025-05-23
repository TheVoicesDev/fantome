#include "fantome_state_2d.h"

void FantomeState2D::set_priority(const int64_t p_priority) {
    priority = p_priority;
}

int64_t FantomeState2D::get_priority() const {
    return priority;
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

bool FantomeState2D::can_switch() {
    bool ret = false;
    GDVIRTUAL_CALL(_can_switch, ret);
    return ret;
}

void FantomeState2D::begin() {
    GDVIRTUAL_CALL(_begin);
}

void FantomeState2D::end() {
    GDVIRTUAL_CALL(_end);
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
        case NOTIFICATION_PARENTED: {
            _controller = Object::cast_to<FantomeStateController2D>(get_parent());
            if (_controller)
                enter_controller(_controller);
        } break;
        case NOTIFICATION_UNPARENTED: {
            exit_controller();
        } break;
    }
}