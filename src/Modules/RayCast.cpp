//
//  RayCast.cpp
//  MiniGolfXCode
//
//  Created by Orlando Salvatore on 5/6/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#include "RayCast.h"

Face* RayCast::rayCast(GameObject *g, glm::vec3 d)
{
    std::vector<GameObject*>* allObjects = SceneManager::instance().getObjects();
    Face *intersectingFace;
    
    for(GameObject* tempG : *allObjects)
    {
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
            /*glm::vec3 e1, e2, h, s, q;
            float a,f,u,v,t;
            
            //face->print();
            
            e1 = face->getVerticies()[1] - face->getVerticies()[0];
            e2 = face->getVerticies()[2] - face->getVerticies()[0];
            h = glm::cross(d, e2);
            a = acos(glm::dot(e1, h)/(glm::length(e1)*glm::length(h)));
            
            std::cout << "e1: " << e1.x << "," << e1.y << "," << e1.z << " h: " << h.x << "," << h.y << "," << h.z << std::endl;
            
            std::cout << a << std::endl;
            break;
            
            if (a > -0.00001 && a < 0.00001)
            {
                std::cout << "Nope! a is bad! Not hitting an object! " << a << std::endl;
                continue;
            }
            
            f = 1/a;
            s = tempG->getPosition() - face->getVerticies()[0];
            u = f * acos(glm::dot(d, h)/(glm::length(d)*glm::length(h)));
            
            if (u < 0.0 || u > 1.0)
            {
                std::cout << "Nope! u is bad! Not hitting an object!\n";
                continue;
            }
            
            q = glm::cross(s,e1);
            v = f * acos(glm::dot(d,q)/(glm::length(d)*glm::length(q)));
            
            if(v < 0.0 || u + v > 1.0)
            {
                //std::cout << "Nope! v is bad! Not hitting an object!\n";
                continue;
            }
            
            t = f * glm::dot(e2, q);
            
            if( t > 0.00001 )
            {
                std::cout << "Hitting an object!\n";
                return face;
            }
            else
            {
                //std::cout << "Nope! t is bad! Not hitting an object!\n";
                continue;
            }*/
            
            std::cout << "Direction: " << d.x << "," << d.y << "," << d.z << std::endl;
            
            glm::vec3 edge1, edge2, tvec, qvec, pvec;
            float det, inv_det;
            float t,u,v;
            
            //find vectors for two edges sharing vert
            edge1 = face->getVerticies()[1] - face->getVerticies()[0];
            edge2 = face->getVerticies()[2] - face->getVerticies()[0];
            
            glm::vec3 testingNormal = glm::cross(edge2, edge1);
            //std::cout << testingNormal.x << " " << testingNormal.y << " " << testingNormal.z << std::endl;
            
            //face->print();
            
            //return NULL;
            
            //begin calculating determinant - also used to calculate U parameter
            pvec = glm::cross(d, edge2);
            
            //if determinant is near zero ray lies in plane of triangle
            det = glm::dot(edge1,pvec);
            
            //culling
            if(det < 0.000001)
            {
                std::cout << "NOPE! " << det << std::endl;
                return NULL;
            }
            
            tvec = g->getPosition() - face->getVerticies()[0];
            
            //calculate U parameter and test bounds
            u = glm::dot(tvec,pvec);
            if(u < 0 || u > det)
            {
                std::cout << "NOPE!\n";
                return NULL;
            }
            
            //prepare to test V parameter
            qvec = glm::cross(tvec,edge1);
            
            //calculate V parameter and test bounds
            v = glm::dot(d,qvec);
            if(v < 0 || u + v > det)
            {
                std::cout << "NOPE!\n";
                return NULL;
            }
            
            //calculate t scale parameters ray intersects triangle
            t = glm::dot(edge2,qvec);
            inv_det = 1.0/det;
            t *= inv_det;
            u *= inv_det;
            v *= inv_det;
            
            std::cout << "SUCCESS!\n";
            
            return face;
        }
        break;
    }
    
    return intersectingFace;
    //float e1[3],e2[3],h[3],s[3],q[3];
    /*glm::vec3 e1, e2;
	float a,f,u,v;
	vector(e1,v1,v0);
	vector(e2,v2,v0);
    
	crossProduct(h,d,e2);
	a = innerProduct(e1,h);
    
	if (a > -0.00001 && a < 0.00001)
		return(false);
    
	f = 1/a;
	vector(s,p,v0);
	u = f * (innerProduct(s,h));
    
	if (u < 0.0 || u > 1.0)
		return(false);
    
	crossProduct(q,s,e1);
	v = f * innerProduct(d,q);
    
	if (v < 0.0 || u + v > 1.0)
		return(false);
    
	// at this stage we can compute t to find out where
	// the intersection point is on the line
	t = f * innerProduct(e2,q);
    
	if (t > 0.00001) // ray intersection
		return(true);
    
	else // this means that there is a line intersection
        // but not a ray intersection
        return (false);*/
    
    /*
     double edge
      edge
      tvec
      pvec
      qvec
     
     double detinvdet
     
     find vectors for two edges sharing vert
     
     SUBedge vert vert
     SUBedge vert vert
     
     begin calculating determinant  also used to calculate U parameter
     
     CROSSpvec dir edge
     
     if determinant is near zero ray lies in plane of triangle
     
     det  DOTedge pvec
     ifdef TESTCULL 
     define TESTCULL if culling is desired 
     
     if det  EPSILON
     return*/
}