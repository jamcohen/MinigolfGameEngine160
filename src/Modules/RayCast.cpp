//
//  RayCast.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "RayCast.h"

RayCastHit* RayCast::rayCast(GameObject *g, glm::vec3 d, float radius)
{
    std::vector<GameObject*>* allObjects = SceneManager::instance().getObjects();
    RayCastHit *intersectingFace = nullptr;
    float nearestDistance(1000000);
   
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
            for(int i=0;i<2;i++){
                //std::cout << "Direction: " << d.x << "," << d.y << "," << d.z << std::endl;
                
                glm::vec3 v1, v2, v3, newPos;
                glm::vec3 edge1, edge2, tvec, qvec, pvec;
                float det, inv_det;
                float t,u,v;
                
                std::vector<glm::vec3> vecs = getCollisionCoords(*face, *g, *tempG, i*radius);
                v1 = vecs[0];
                v2 = vecs[1];
                v3 = vecs[2];
                
                
                //find vectors for two edges sharing vert
                edge1 = v2 - v1;
                edge2 = v3 - v1;
               
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
                
                tvec = g->getPosition() - v1;
                
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
               
                if(t < nearestDistance)
                {
                  nearestDistance = t;
                }
                else
                {
                  continue;
                }
               
                //std::cout << "SUCCESS!: " << t;
                glm::vec3 targetPoint = g->getPosition() + d*t;
                //std::cout << targetPoint.x << "," << targetPoint.y << "," << targetPoint.z << std::endl;
                
                intersectingFace = new RayCastHit(face, tempG, targetPoint, t);
                
                //return intersectingFace;
            }
        //break;
        }
    }
    
    return intersectingFace;
}

std::vector<glm::vec3> RayCast::getCollisionCoords(Face& face, GameObject &g, GameObject &tempG, float radius){
    //Caches the tiles coords for normals
    glm::vec3 norm = face.getWorldNormal(&tempG);
    std::vector<glm::vec3> vecs{};
    for(int i=0;i<3;++i){
        vecs.push_back(face.getWorldVertices(&tempG)[i]);
        glm::vec3 normal = glm::normalize(norm);
        vecs[i] += -1.0f*normal*radius;
    }
    glm::vec3 center = (vecs[0]+vecs[1]+vecs[2])/3.0f;
    /*v1 += glm::normalize((v1-center))*radius;
     v2 += glm::normalize((v2-center))*radius;
     v3 += glm::normalize((v3-center))*radius;*/
    Gizmo::instance().addDebugRay(vecs[0], vecs[1]);
    Gizmo::instance().addDebugRay(vecs[1], vecs[2]);
    Gizmo::instance().addDebugRay(vecs[2], vecs[0]);
    
    Gizmo::instance().addDebugRay(center, center+norm*0.2f);
    return vecs;
}