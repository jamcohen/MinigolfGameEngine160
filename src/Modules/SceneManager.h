//
//  SceneManager.h
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__SceneManager__
#define __MiniGolfXCode__SceneManager__

#include <vector>
#include <iostream>
#include <iterator>

class Ball;
class GameObject;
class Camera;

class SceneManager
{
public:
    static SceneManager& instance()
    {
        static SceneManager INSTANCE;
        return INSTANCE;
    }
    SceneManager();
    SceneManager(SceneManager const&);
    void operator=(SceneManager const&);
    void update();
    void addGameObject(GameObject *);
    inline void clearScene(){_objects.clear();};
    void closeScene();
    inline std::vector<GameObject *>* getObjects() { return &_objects; }
    void addCamera(Camera *);
    inline void setCurrentCamera(Camera *c) { _currentCamera = c; }
    inline Camera* getCurrentCamera() { return _currentCamera; }
    
private:
    std::vector<GameObject *> _objects;
    Camera *_currentCamera;
    std::vector<Camera *> _cameraList;
};

#endif /* defined(__MiniGolfXCode__SceneManager__) */
