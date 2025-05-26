#ifndef FANTOME_BEHAVIOR_2D_H
#define FANTOME_BEHAVIOR_2D_H

#include "core/object/gdvirtual.gen.inc"
#include "scene/main/node.h"
#include "fantome_character_2d.h"

class FantomeCharacter2D;

class FantomeBehavior2D : public Node {
    GDCLASS(FantomeBehavior2D, Node);

public:
    FantomeCharacter2D* character;

    void set_active(const bool p_value);
    bool get_active() const;
    void set_character(FantomeCharacter2D* p_value);
    FantomeCharacter2D* get_character() const;

    PackedStringArray get_configuration_warnings() const override;

protected:
    void _notification(int p_what);
    static void _bind_methods();

    GDVIRTUAL0(_enter_character);
    GDVIRTUAL0(_exit_character);

private:
    bool _active = true;
};

#endif // FANTOME_BEHAVIOR_2D_H