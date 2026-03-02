#include "RequestHandler.h"
#include "Renderer/Renderer.h"
#include "SceneManagement/Camera.h"
#include <memory>

namespace Dread {

void RequestHandler::ForwardRequestRegisterGameObject(GameObject &go) {
    Renderer::RegisterGameObject(go);
}


}