#pragma once

#include "SceneManagement/GameObject.h"
namespace Dread {

class RequestHandler {
public:
    static void ForwardRequestRegisterGameObject(GameObject& go);

private:
    RequestHandler();

};

}