#pragma once

#include "SceneManagement/Camera.h"
#include "SceneManagement/GameObject.h"
#include <memory>
namespace Dread {

class RequestHandler {
public:
    static void ForwardRequestRegisterGameObject(GameObject& go);

private:
    RequestHandler();

};

}