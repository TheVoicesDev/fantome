#include "fantome_character_2d.h"

void FantomeCharacter2D::set_controller(FantomeStateController2D* p_value) {
    _controller = p_value;
}

FantomeStateController2D* FantomeCharacter2D::get_controller() const {
    return _controller;
}

PackedStringArray FantomeCharacter2D::get_configuration_warnings() const {
    PackedStringArray warnings = CharacterBody2D::get_configuration_warnings();

    if (_controller == nullptr)
        warnings.push_back(RTR("This node has no controller, so it won't have any functionality beyond a regular CharacterBody2D.\nConsider adding a FantomeStateController2D."));
    
    return warnings;
}

void FantomeCharacter2D::_bind_methods() {
    ClassDB::bind_method("get_controller", &FantomeCharacter2D::get_controller);
}

