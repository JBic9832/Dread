#include "RequestHandler.h"
#include "Renderer/Renderer.h"

namespace Dread {

void RequestHandler::ForwardRequestRegisterGameObject(GameObject &go) {
    Renderer::RegisterGameObject(go);
}


}