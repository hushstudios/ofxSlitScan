//
//  MeshHelper.hpp
//  SLIT_SCAN_SKETCH
//
//  Created by Nicole Yi Messier on 4/2/20.
//

#pragma once

#include "ofColor.h"
#include "ofMesh.h"

class MeshHelper {
  public:
    static MeshHelper &one()
    {
        static MeshHelper instance;
        return instance;
    };

    // --- STRUCTS --- //
    struct Quad {
        glm::vec3 tl, tr, br, bl;
    };

    struct TexQuad {
        Quad vertices;
        Quad texCoords;
    };

    struct ColQuad {
        Quad    verts;
        ofColor color;
    };

    struct RectData {
        glm::vec2 size;
        glm::vec2 position;
    };

    // --- QUAD GETTERS --- //
    static TexQuad getQuad( const RectData &where, const RectData &tex );


    static ColQuad getColQuad( const RectData &where, const ofColor &color );

    // --- DRAWING TO MESH --- //
    void addToMesh( ofMesh &mesh, const TexQuad &quad ) const;
    void addToMesh( ofMesh &mesh, const ColQuad &quad ) const;
};
