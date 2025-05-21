#include "fantome_engine.h"
#include "core/config/project_settings.h"
#include "core/config/engine.h"
#include "scene/main/scene_tree.h"
#include "core/variant/variant.h"

bool FantomeEngine::initialize() {
    _last_physics_frame_count = Engine::get_singleton()->get_physics_frames();
    SceneTree::get_singleton()->connect(SNAME("physics_frame"), callable_mp(this, &FantomeEngine::process_ticks));
}

void FantomeEngine::process_ticks() {
    int physics_frame_count = Engine::get_singleton()->get_physics_frames();

    _delta_ticks = physics_frame_count - _last_physics_frame_count;

    _last_physics_frame_count = physics_frame_count;
}