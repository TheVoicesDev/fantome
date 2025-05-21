#ifndef FANTOME_BEHAVIOR_2D_H
#define FANTOME_BEHAVIOR_2D_H

#include "scene/main/node.h"
#include "fantome_character_2d.h"

class FantomeBehavior2D : public Node {
    GDCLASS(FantomeBehavior2D, Node);

public:
    FantomeCharacter2D* character;
    void set_character(FantomeCharacter2D* p_value);
    FantomeCharacter2D* get_character();
    
};

#endif // FANTOME_BEHAVIOR_2D_H