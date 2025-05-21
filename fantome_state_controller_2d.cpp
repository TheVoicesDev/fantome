#include "fantome_state_controller_2d.h"

FantomeCharacter2D* FantomeStateController2D::get_character() const {
    return _character;
}

void FantomeStateController2D::register_state(FantomeState2D* p_state) {
    _states.append(p_state);
    _states.sort_custom(callable_mp_static(&FantomeState2D::compare_by_priority));
}

void FantomeStateController2D::deregister_state(FantomeState2D* p_state) {
    int index = _states.find(p_state);
    ERR_FAIL_COND_MSG(index < 0, "Tried to deregister a state not registered in the state controller.");

    _states.remove_at(index);
}

void FantomeStateController2D::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_PARENTED: {
            _character = Object::cast_to<FantomeCharacter2D>(get_parent());
            if (_character)
                _character->set_controller(this);
        } break;
        case NOTIFICATION_UNPARENTED: {
            if (_character) {
                _character->set_controller(nullptr);
            }

            _character = nullptr;
        } break;
    }
}