#include "register_types.h"

#include "fantome_character_2d.h"
#include "fantome_state_2d.h"
#include "fantome_state_controller_2d.h"
#include "fantome_state_set_2d.h"

void initialize_fantome_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
    
    GDREGISTER_CLASS(FantomeCharacter2D);
    GDREGISTER_CLASS(FantomeState2D);
    GDREGISTER_CLASS(FantomeStateController2D);
    GDREGISTER_CLASS(FantomeStateSet2D);
}

void uninitialize_fantome_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
}