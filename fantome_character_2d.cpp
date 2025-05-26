#include "fantome_character_2d.h"

void FantomeCharacter2D::set_controller(FantomeStateController2D* p_value) {
    _controller = p_value;
}

FantomeStateController2D* FantomeCharacter2D::get_controller() const {
    return _controller;
}

bool FantomeCharacter2D::has_behavior(const StringName &p_name) const {
    return _behaviors.has(p_name);
}

FantomeBehavior2D* FantomeCharacter2D::get_behavior(const StringName &p_name) const {
    ERR_FAIL_COND_V_MSG(!_behaviors.has(p_name), nullptr, "Behavior " + p_name + " was not found with the associated character.");

    return Object::cast_to<FantomeBehavior2D>(_behaviors[p_name]);
}

Array FantomeCharacter2D::get_all_behavior_names() const {
    return _behaviors.keys();
}

Array FantomeCharacter2D::get_all_behaviors() const {
    return _behaviors.values();
}

PackedStringArray FantomeCharacter2D::get_configuration_warnings() const {
    PackedStringArray warnings = CharacterBody2D::get_configuration_warnings();

    if (_controller == nullptr)
        warnings.push_back(RTR("This node has no controller, so it won't have any functionality beyond a regular CharacterBody2D.\nConsider adding a FantomeStateController2D."));
    
    return warnings;
}

void FantomeCharacter2D::_notification(int p_what) {
    switch (p_what) {
        case NOTIFICATION_CHILD_ORDER_CHANGED: {
            // Check for behaviors
            _behaviors.clear();

            TypedArray<Node> children = get_children();
            for (int i = 0; i < children.size(); i++) {
                FantomeBehavior2D* behavior = Object::cast_to<FantomeBehavior2D>(children[i]);
                if (!behavior)
                    continue;
                
                _behaviors.set(behavior->get_name(), behavior);
            }
        } break;
    }
}

void FantomeCharacter2D::_bind_methods() {
    ClassDB::bind_method("get_controller", &FantomeCharacter2D::get_controller);

    ClassDB::bind_method(D_METHOD("has_behavior", "name"), &FantomeCharacter2D::has_behavior);
    ClassDB::bind_method(D_METHOD("get_behavior", "name"), &FantomeCharacter2D::get_behavior);

    ClassDB::bind_method("get_all_behavior_names", &FantomeCharacter2D::get_all_behavior_names);
    ClassDB::bind_method("get_all_behaviors", &FantomeCharacter2D::get_all_behaviors);
}

