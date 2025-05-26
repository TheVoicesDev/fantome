#ifndef FANTOME_CHARACTER_2D_H
#define FANTOME_CHARACTER_2D_H

#include "core/variant/array.h"
#include "core/variant/typed_dictionary.h"
#include "core/object/class_db.h"
#include "scene/2d/physics/character_body_2d.h"
#include "fantome_behavior_2d.h"
#include "fantome_state_controller_2d.h"

template <typename K, typename V>
class TypedDictionary;

class FantomeBehavior2D;
class FantomeStateController2D;

class FantomeCharacter2D : public CharacterBody2D {
    GDCLASS(FantomeCharacter2D, CharacterBody2D);

public:
    void set_controller(FantomeStateController2D* p_controller);
    FantomeStateController2D* get_controller() const;

    bool has_behavior(const StringName &p_name) const;
    FantomeBehavior2D* get_behavior(const StringName &p_name) const;

    Array get_all_behavior_names() const;
    Array get_all_behaviors() const;

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_what);
    static void _bind_methods();

private:
    FantomeStateController2D* _controller = nullptr;
    TypedDictionary<StringName, FantomeBehavior2D> _behaviors;
};

#endif // FANTOME_CHARACTER_2D_H