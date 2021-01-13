//
//  MeshHelper.cpp
//  SLIT_SCAN_SKETCH
//
//  Created by Nicole Yi Messier on 4/2/20.
//

#include "MeshHelper.h"

#include "ofGraphics.h"

#pragma mark QUAD GETERS

MeshHelper::TexQuad MeshHelper::getQuad( const RectData &where, const RectData &tex )
{
    TexQuad temp;

    //! MESH
    temp.vertices.tl.x = where.position.x;
    temp.vertices.tl.y = where.position.y;

    temp.vertices.tr.x = where.position.x + where.size.x;
    temp.vertices.tr.y = where.position.y;

    temp.vertices.bl.x = where.position.x;
    temp.vertices.bl.y = where.position.y + where.size.y;

    temp.vertices.br.x = where.position.x + where.size.x;
    temp.vertices.br.y = where.position.y + where.size.y;

    //! TEXTURE
    temp.texCoords.tl.x = tex.position.x;
    temp.texCoords.tl.y = tex.position.y;

    temp.texCoords.tr.x = tex.position.x + tex.size.x;
    temp.texCoords.tr.y = tex.position.y;

    temp.texCoords.bl.x = tex.position.x;
    temp.texCoords.bl.y = tex.position.y + tex.size.y;

    temp.texCoords.br.x = tex.position.x + tex.size.x;
    temp.texCoords.br.y = tex.position.y + tex.size.y;

    return temp;
}

MeshHelper::ColQuad MeshHelper::getColQuad( const RectData &where, const ofColor &color )
{
    ColQuad temp;

    //! MESH
    temp.verts.tl.x = where.position.x;
    temp.verts.tl.y = where.position.y;

    temp.verts.tr.x = where.position.x + where.size.x;
    temp.verts.tr.y = where.position.y;

    temp.verts.bl.x = where.position.x;
    temp.verts.bl.y = where.position.y + where.size.y;

    temp.verts.br.x = where.position.x + where.size.x;
    temp.verts.br.y = where.position.y + where.size.y;

    //! COLOR
    temp.color = color;

    return temp;
}

#pragma mark ADD TO MESH

void MeshHelper::addToMesh( ofMesh &mesh, const TexQuad &quad ) const
{
    mesh.addVertex( ofVec3f( quad.vertices.tl.x, quad.vertices.tl.y ) );
    mesh.addTexCoord( ofVec2f( quad.texCoords.tl.x, quad.texCoords.tl.y ) );

    mesh.addVertex( ofVec3f( quad.vertices.bl.x, quad.vertices.bl.y ) );
    mesh.addTexCoord( ofVec2f( quad.texCoords.bl.x, quad.texCoords.bl.y ) );

    mesh.addVertex( ofVec3f( quad.vertices.tr.x, quad.vertices.tr.y ) );
    mesh.addTexCoord( ofVec2f( quad.texCoords.tr.x, quad.texCoords.tr.y ) );

    mesh.addVertex( ofVec3f( quad.vertices.tr.x, quad.vertices.tr.y ) );
    mesh.addTexCoord( ofVec2f( quad.texCoords.tr.x, quad.texCoords.tr.y ) );

    mesh.addVertex( ofVec3f( quad.vertices.br.x, quad.vertices.br.y ) );
    mesh.addTexCoord( ofVec2f( quad.texCoords.br.x, quad.texCoords.br.y ) );

    mesh.addVertex( ofVec3f( quad.vertices.bl.x, quad.vertices.bl.y ) );
    mesh.addTexCoord( ofVec2f( quad.texCoords.bl.x, quad.texCoords.bl.y ) );
}

void MeshHelper::addToMesh( ofMesh &mesh, const ColQuad &quad ) const
{
    mesh.addVertex( ofVec3f( quad.verts.tl.x, quad.verts.tl.y ) );
    mesh.addColor( quad.color );

    mesh.addVertex( ofVec3f( quad.verts.bl.x, quad.verts.bl.y ) );
    mesh.addColor( quad.color );

    mesh.addVertex( ofVec3f( quad.verts.tr.x, quad.verts.tr.y ) );
    mesh.addColor( quad.color );

    mesh.addVertex( ofVec3f( quad.verts.tr.x, quad.verts.tr.y ) );
    mesh.addColor( quad.color );

    mesh.addVertex( ofVec3f( quad.verts.br.x, quad.verts.br.y ) );
    mesh.addColor( quad.color );

    mesh.addVertex( ofVec3f( quad.verts.bl.x, quad.verts.bl.y ) );
    mesh.addColor( quad.color );

    ofSetColor( 255 );
    ofDrawCircle( quad.verts.tl.x, quad.verts.tl.y, 10.0f );
    ofDrawCircle( quad.verts.tr.x, quad.verts.tr.y, 10.0f );
    ofDrawCircle( quad.verts.bl.x, quad.verts.bl.y, 10.0f );
    ofDrawCircle( quad.verts.br.x, quad.verts.br.y, 10.0f );
}
