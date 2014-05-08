//
//  RayCast.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "RayCast.h"

RayCastHit* RayCast::rayCast(GameObject *g, glm::vec3 d)
{
    std::vector<GameObject*>* allObjects = SceneManager::instance().getObjects();
    RayCastHit *intersectingFace = nullptr;
    
    //for(GameObject* tempG : *allObjects)
   for(int i=0;i<allObjects->size(); ++i)
    {
       GameObject* tempG = (*allObjects)[i];
        if(!tempG->getModel())
        {
            continue;
        }
        if(tempG == g)
        {
            continue;
        }
        std::vector<Face *> faces = tempG->getModel()->getFaces();
        for(Face* face : faces)
        {
            //std::cout << "Direction: " << d.x << "," << d.y << "," << d.z << std::endl;
            
            glm::vec3 edge1, edge2, tvec, qvec, pvec;
            float det, inv_det;
            float t,u,v;
           
            glm::vec3 objPos(g->getPosition());
            //find vectors for two edges sharing vert
            edge1 = face->getWorldVertices(tempG)[1] - face->getWorldVertices(tempG)[0];
            edge2 = face->getWorldVertices(tempG)[2] - face->getWorldVertices(tempG)[0];
           
            //begin calculating determinant - also used to calculate U parameter
            pvec = glm::cross(d, edge2);
            //std::cout << "pvec: " << faces.size() << ", "<< pvec.x << ", " << pvec.y << ", " << pvec.z << std::endl;
           
            //if determinant is near zero ray lies in plane of triangle
            det = glm::dot(edge1,pvec);
           //std::cout << "det: " << allObjects->size() << ", " << det << std::endl;
           
            //culling
            if(det < 0.000001)
            {
                //std::cout << "NOPE! " << det << std::endl;
                continue;
            }
            
            tvec = g->getPosition() - face->getWorldVertices(tempG)[0];
            
            //calculate U parameter and test bounds
            u = glm::dot(tvec,pvec);
            if(u < 0 || u > det)
            {
                //std::cout << "NOPE!\n";
                continue;
            }
            
            //prepare to test V parameter
            qvec = glm::cross(tvec,edge1);
            
            //calculate V parameter and test bounds
            v = glm::dot(d,qvec);
            if(v < 0 || u + v >= det)
            {
                //std::cout << "NOPE!\n";
                continue;
            }
            
            //calculate t scale parameters ray intersects triangle
            t = glm::dot(edge2,qvec);
           
            if(t < 0)
            {
              //std::cout << "NOPE!\n";
              continue;
            }
            inv_det = 1.0/det;
            t *= inv_det;
            u *= inv_det;
            v *= inv_det;
            
            //std::cout << "SUCCESS!: " << t;
            glm::vec3 targetPoint = g->getPosition() + d*t;
            //std::cout << targetPoint.x << "," << targetPoint.y << "," << targetPoint.z << std::endl;
            
            intersectingFace = new RayCastHit(face, tempG, targetPoint, t);
            
            return intersectingFace;
        }
        //break;
    }
    
    return intersectingFace;
}