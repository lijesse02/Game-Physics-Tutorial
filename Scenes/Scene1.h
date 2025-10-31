#include "Scene.h"

class Scene1 : public Scene
{
    float pitch = 0.f;
    float roll = 0.f;
    float yaw = 0.f;

    virtual void onDraw(Renderer &renderer) override;
    virtual void simulateStep() override;
};