#include "fantome_behavior_2d.h"

void FantomeBehavior2D::set_active(const bool p_value) {
    _active = p_value;

    set_process(_active);
    set_process_internal(_active);
    set_physics_process(_active);
    set_physics_process_internal(_active);
}

bool FantomeBehavior2D::get_active() const {
    return _active;
}

void FantomeBehavior2D::set_character(FantomeCharacter2D* p_value) {
    character = p_value;
}

FantomeCharacter2D* FantomeBehavior2D::get_character() const {
    return character;
}

PackedStringArray FantomeBehavior2D::get_configuration_warnings() const {
    PackedStringArray warnings = Node::get_configuration_warnings();

    if (character == nullptr)
        warnings.push_back(RTR("This state isn't registered to a character. Consider parenting this node to a FantomeCharacter2D."));
    
    return warnings;
}

void FantomeBehavior2D::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_PARENTED: {
            character = Object::cast_to<FantomeCharacter2D>(get_parent());
            if (character)
                GDVIRTUAL_CALL(_enter_character);
        } break;
        case NOTIFICATION_UNPARENTED: {
            if (character)
                GDVIRTUAL_CALL(_exit_character);
            
            character = nullptr;
        } break;
        case NOTIFICATION_READY: {
            if (Engine::get_singleton()->is_editor_hint())
                return;

            set_active(_active);
        } break;
    }
}

void FantomeBehavior2D::_bind_methods() {
    // Getters and Setters
    ClassDB::bind_method(D_METHOD("set_active", "value"), &FantomeBehavior2D::set_active);
    ClassDB::bind_method("get_active", &FantomeBehavior2D::get_active);

    // Properties
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "active"), "set_active", "get_active");

    // Methods
    ClassDB::bind_method("get_character", &FantomeBehavior2D::get_character);

    GDVIRTUAL_BIND(_enter_character);
    GDVIRTUAL_BIND(_exit_character);
}