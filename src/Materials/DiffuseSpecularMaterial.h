//
//  DiffuseSpecularMaterial.h
//  MiniGolfXCode
//
//  Created by Jake Cohen on 4/19/14.
//  Copyright (c) 2014 Orlando Salvatore. All rights reserved.
//

#ifndef __MiniGolfXCode__DiffuseSpecularMaterial__
#define __MiniGolfXCode__DiffuseSpecularMaterial__

#include <iostream>
#include "GenericMaterial.h"
#include "ShaderHelper.h"

class DiffuseSpecularMaterial : public GenericMaterial
{
public:
    DiffuseSpecularMaterial(float shininess);
    bool initializeUniforms(GLuint);
    float shininess;
};

#endif /* defined(__MiniGolfXCode__DiffuseSpecularMaterial__) */
