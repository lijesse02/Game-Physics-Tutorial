#include "Scene1.h"
#include <glm/gtx/quaternion.hpp>

void Scene1::onDraw(Renderer& renderer){
    renderer.drawWireCube(glm::vec3(0), glm::vec3(5), glm::vec3(1));

    renderer.drawCube(  glm::vec3(0),
                        glm::quat(glm::vec3(pitch, roll, yaw)), 
                        glm::vec3(0.5, 0.5, 0.5), 
                        glm::vec4(1, 0, 0, 1));

    glm::mat4 rotation = glm::toMat4(glm::quat(glm::vec3(pitch, roll, yaw)));
    glm::vec3 forward = glm::vec3(rotation * glm::vec4(0, 0, 1, 0));
    glm::vec3 right = glm::vec3(rotation * glm::vec4(1, 0, 0, 0));
    glm::vec3 up = glm::vec3(rotation * glm::vec4(0, 1, 0, 0));
}

void Scene1::simulateStep(){
    pitch += 0.001f;
    roll += 0.002f;
    yaw += 0.003f;
}

