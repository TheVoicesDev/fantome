#ifndef FANTOME_CHARACTER_2D_H
#define FANTOME_CHARACTER_2D_H

#include "core/object/class_db.h"
#include "scene/2d/physics/character_body_2d.h"
#include "fantome_state_controller_2d.h"

class FantomeCharacter2D : public CharacterBody2D {
    GDCLASS(FantomeCharacter2D, CharacterBody2D);

public:
    void set_controller(FantomeStateController2D* p_value);
    FantomeStateController2D* get_controller() const;

    PackedStringArray get_configuration_warnings() const override;

private:
    FantomeStateController2D* _controller = nullptr;
};

#endif // FANTOME_CHARACTER_2D_H