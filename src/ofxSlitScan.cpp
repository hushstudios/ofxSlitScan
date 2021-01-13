#include "ofxSlitScan.h"

#include "MeshHelper.h"
#include "ofTexture.h"

void ofxSlitScan::drawVerticalSlotIn( int numCols, const glm::vec2 &size, const glm::vec2 &contentSize, ofMesh &mesh,
    const glm::vec2 &whereStart, const glm::vec2 &whereTarget, float animVal ) const
{
    for( int i = 0; i < numCols; i++ ) {
        MeshHelper::RectData where;
        where.size.x = size.x / float( numCols );
        where.size.y = size.y;
        where.position.x
            = where.size.x * float( i ) + whereStart.x + abs( whereTarget.x - whereStart.x ) * ofMap( animVal, 1.0f, 0.0f, 0.0f, 1.0f );
        where.position.y = whereStart.y + abs( whereTarget.y - whereStart.y ) * ofMap( animVal, 1.0f, 0.0f, 0.0f, 1.0f );
        // where.position.y = proto_val;

        float sizePercent = where.size.y / size.y;
        float mapCounter = ofMap( float( i ), -1, float( numCols - 1 ), 1, 0 );
        // float mapCounter = ofMap(i, 0, num_cols, 0, 1); //uncomment for right to left slot in
        float offsetExp = powf( mapCounter, 2.0f );
        float offsetExpMap = ofMap( offsetExp, 0, 1, 10.0f, 1 - sizePercent );

        MeshHelper::RectData tex;
        // glm::vec2            content_size = content_size;

        glm::vec2 startSize;
        glm::vec2 startPos;
        glm::vec2 targetSize;
        glm::vec2 targetPos;

        startSize.y = contentSize.y;
        startSize.x = contentSize.x / float( numCols );
        startPos.y = 0;
        startPos.x = tex.size.x * float( i );

        // animation values
        targetSize.y = contentSize.y * offsetExpMap;
        targetSize.x = contentSize.x / float( numCols );
        targetPos.y = contentSize.y * offsetExpMap;
        targetPos.x = tex.size.x * float( i );

        tex.size.y = startSize.y - abs( startSize.y - targetSize.y ) * animVal;
        tex.size.x = contentSize.x / float( numCols );
        tex.position.y = startPos.y + abs( startPos.y - targetPos.y ) * animVal;
        tex.position.x = tex.size.x * float( i );

        MeshHelper::TexQuad quad = MeshHelper::getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

#pragma region VSS


void ofxSlitScan::typeVssSlotIn( int numCols, const glm::vec2 &size, const glm::vec2 &contentSize, ofMesh &mesh,
    const glm::vec2 &whereStart, const glm::vec2 &whereTarget, float offsetX, float animVal ) const
{
    // add quad on the offset part, then start the slit part for just text size, then add another quad to fill to canvas size
    {
        MeshHelper::RectData where;
        where.position.x = 0;
        where.position.y = whereStart.y;
        where.size.y = size.y;
        where.size.x = offsetX;

        MeshHelper::RectData tex;
        tex.size.x = offsetX;
        tex.size.y = contentSize.y;
        tex.position.x = 0;
        tex.position.y = 0;

        MeshHelper::TexQuad quad = MeshHelper::getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }

    // add slit scan with x offset
    for( int i = 0; i < numCols; i++ ) {
        MeshHelper::RectData where;
        where.size.x = contentSize.x / float( numCols );
        where.size.y = contentSize.y;
        where.position.x = offsetX + where.size.x * float( i ) + whereStart.x
            + abs( whereTarget.x - whereStart.x ) * ofMap( animVal, 1.0f, 0.0f, 0.0f, 1.0f );
        where.position.y = whereStart.y + abs( whereTarget.y - whereStart.y ) * ofMap( animVal, 1.0f, 0.0f, 0.0f, 1.0f );

        float sizePercent = where.size.y / size.y;
        float mapCounter = ofMap( float( i ), -1, float( numCols - 1 ), 1, 0 );
        // float mapCounter = ofMap(i, 0, num_cols, 0, 1); //uncomment for right to left slot in
        float offsetExp = powf( mapCounter, 2.0f );
        float offsetExpMap = ofMap( offsetExp, 0, 1, 10.0f, 1 - sizePercent );

        MeshHelper::RectData tex;

        glm::vec2 startSize;
        glm::vec2 startPos;
        glm::vec2 targetSize;
        glm::vec2 targetPos;

        startSize.y = contentSize.y;
        startSize.x = contentSize.x / float( numCols );
        startPos.y = 0;
        startPos.x = tex.size.x * float( i );

        // animation values
        targetSize.y = contentSize.y * offsetExpMap;
        targetSize.x = contentSize.x / float( numCols );
        targetPos.y = contentSize.y * offsetExpMap;
        targetPos.x = tex.size.x * float( i );

        tex.size.y = startSize.y - abs( startSize.y - targetSize.y ) * animVal;
        tex.size.x = contentSize.x / float( numCols );
        tex.position.y = startPos.y + abs( startPos.y - targetPos.y ) * animVal;
        tex.position.x = offsetX + tex.size.x * float( i );

        MeshHelper::TexQuad quad = MeshHelper::getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

#pragma endregion

void ofxSlitScan::typeVssSlotOut( int numCols, const glm::vec2 &size, const glm::vec2 &contentSize, ofMesh &mesh,
    const glm::vec2 &whereStart, const glm::vec2 &whereTarget, float offsetX, float animVal ) const
{
    // add quad on the offset part, then start the slit part for just text size, then add another quad to fill to canvas size
    {
        MeshHelper::RectData where;
        where.position.x = 0;
        where.position.y = whereStart.y;
        where.size.y = size.y;
        where.size.x = offsetX;

        MeshHelper::RectData tex;
        tex.size.x = offsetX;
        tex.size.y = contentSize.y;
        tex.position.x = 0;
        tex.position.y = 0;

        MeshHelper::TexQuad quad = MeshHelper::getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }

    // add slit scan with x offset
    for( int i = 0; i < numCols; i++ ) {
        MeshHelper::RectData where;
        where.size.x = contentSize.x / float( numCols );
        where.size.y = contentSize.y;
        where.position.x = offsetX + where.size.x * float( i ) + whereStart.x
            + abs( whereTarget.x - whereStart.x ) * ofMap( animVal, 1.0f, 0.0f, 0.0f, 1.0f );
        // float indexScale = 1.0f - float( i ) / float( numCols - 1 );
        where.position.y = whereStart.y + abs( whereTarget.y - whereStart.y ) * ofMap( animVal, 1.0f, 0.0f, 0.0f, 1.0f );

        float sizePercent = where.size.y / size.y;
        float mapCounter = ofMap( float( i ), -1, float( numCols - 1 ), 1, 0 );
        float offsetExp = powf( mapCounter, 2.0f );
        float offsetExpMap = ofMap( offsetExp, 0, 1, 1 - sizePercent, 5.0f );

        MeshHelper::RectData tex;

        glm::vec2 startSize;
        glm::vec2 startPos;
        glm::vec2 targetSize;
        glm::vec2 targetPos;

        startSize.y = contentSize.y;
        startSize.x = contentSize.x / float( numCols );
        startPos.y = 0;
        startPos.x = tex.size.x * float( i );

        // animation values
        targetSize.y = contentSize.y; // *offsetExpMap;
        targetSize.x = contentSize.x / float( numCols );
        targetPos.y = contentSize.y * offsetExpMap;
        targetPos.x = tex.size.x * float( i );

        tex.size.y = startSize.y - abs( startSize.y - targetSize.y ) * animVal;
        tex.size.x = contentSize.x / float( numCols );
        tex.position.y = startPos.y - abs( startPos.y - targetPos.y ) * ( 1 - animVal );
        tex.position.x = offsetX + tex.size.x * float( i );

        MeshHelper::TexQuad quad = MeshHelper::getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

void ofxSlitScan::drawHorizontalPixel(
    const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &contentSize, ofMesh &mesh, float animVal, float targetY )
{
    MeshHelper::RectData where;
    where.size.x = size.x;
    where.size.y = size.y;
    where.position.x = position.x;
    where.position.y = position.y + animVal * targetY;

    MeshHelper::RectData tex;
    // glm::vec2 content_size = glm::vec2(tex_ref.getWidth(), tex_ref.getHeight());

    tex.size.y = contentSize.y;
    tex.size.x = contentSize.x;
    tex.position.y = 0.0f;
    tex.position.x = 0.0f;

    //! crop
    MeshHelper::TexQuad temp;

    //! MESH
    temp.vertices.tl.x = where.position.x;
    temp.vertices.tl.y = where.position.y;

    temp.vertices.tr.x = where.position.x + where.size.x;
    temp.vertices.tr.y = where.position.y;

    temp.vertices.bl.x = where.position.x;
    temp.vertices.bl.y = where.position.y + where.size.y * ofMap( animVal, 0, 1, 1, 0 );

    temp.vertices.br.x = where.position.x + where.size.x;
    temp.vertices.br.y = where.position.y + where.size.y * ofMap( animVal, 0, 1, 1, 0 );

    //! TEXTURE
    temp.texCoords.tl.x = tex.position.x;
    temp.texCoords.tl.y = tex.size.y * animVal;

    temp.texCoords.tr.x = tex.position.x + tex.size.x;
    temp.texCoords.tr.y = tex.size.y * animVal;

    temp.texCoords.bl.x = tex.position.x;
    temp.texCoords.bl.y = tex.position.y + tex.size.y;

    temp.texCoords.br.x = tex.position.x + tex.size.x;
    temp.texCoords.br.y = tex.position.y + tex.size.y;

    MeshHelper::one().addToMesh( mesh, temp );

    MeshHelper::TexQuad pixelStretch;

    //! MESH
    pixelStretch.vertices.tl.x = where.position.x;
    pixelStretch.vertices.tl.y = where.position.y + where.size.y * ofMap( animVal, 0, 1, 1, 0 );

    pixelStretch.vertices.tr.x = where.position.x + where.size.x;
    pixelStretch.vertices.tr.y = where.position.y + where.size.y * ofMap( animVal, 0, 1, 1, 0 );

    pixelStretch.vertices.bl.x = where.position.x;
    pixelStretch.vertices.bl.y = where.position.y + where.size.y;

    pixelStretch.vertices.br.x = where.position.x + where.size.x;
    pixelStretch.vertices.br.y = where.position.y + where.size.y;

    //! TEXTURE
    pixelStretch.texCoords.tl.x = tex.position.x;
    pixelStretch.texCoords.tl.y = tex.size.y;

    pixelStretch.texCoords.tr.x = tex.position.x + tex.size.x;
    pixelStretch.texCoords.tr.y = pixelStretch.texCoords.tl.y;

    pixelStretch.texCoords.bl.x = pixelStretch.texCoords.tl.x;
    pixelStretch.texCoords.bl.y = tex.size.y;

    pixelStretch.texCoords.br.x = pixelStretch.texCoords.tr.x;
    pixelStretch.texCoords.br.y = pixelStretch.texCoords.bl.y;

    MeshHelper::one().addToMesh( mesh, pixelStretch );
}

void ofxSlitScan::drawHorSwipeVertSc( int numCols, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &contentSize,
    ofMesh &mesh, float animWipe, float animSlit, bool lr ) const
{
    for( int i = 0; i < numCols; i++ ) {
        MeshHelper::RectData where;
        where.size.x = size.x / float( numCols );
        where.size.y = size.y;
        where.position.y = position.y;
        if( lr ) {
            where.position.x = position.x + where.size.x * float( i ) - size.x + size.x * animWipe;
        }
        else {
            where.position.x = position.x + where.size.x * float( i ) + size.x - size.x * animWipe;
        }

        float sizePercent = where.size.x / size.x;
        float mapCounter = ofMap( float( i ), 0, float( numCols + 2 ), 1, 0 );
        // float mapCounter = ofMap(i, 0, num_cols + 2, 0, 1);

        //! functions
        // float offsetExp = pow(mapCounter, 5.0f * anim_slit);
        // float offsetExp = 1 - sqrt(1 - pow(mapCounter, 7.0f * anim_slit));
        float offsetExp = doubleOddPolynomialSeat( mapCounter, 0.25f * animSlit, 1.25f * ofMap( animSlit, 1, 0, 0, 1 ), 0.0f );
        // float offsetExp = doubleOddPolynomialSeat(mapCounter, 1.6f * anim_slit, 1.5f * ofMap(anim_slit, 1, 0, 0, 1), 8.0f);

        float offsetExpMap;
        offsetExpMap = ofMap( offsetExp, 0, 1, sizePercent, 1.0f );
        offsetExpMap = ofClamp( offsetExpMap, sizePercent, 1.0f );

        MeshHelper::RectData tex;

        tex.size.y = contentSize.y;
        tex.size.x = contentSize.x / float( numCols );
        tex.position.y = 0.0f;

        // add dist?
        // float iStart = float( numCols ) - 1.;
        // float iTarget = float( i );
        // float iFinal = iStart - abs( iStart - iTarget ) * offsetExpMap;
        // tex.position.x = tex.size.x * iFinal;

        tex.position.x = tex.size.x * float( i ) * offsetExpMap;
        // tex.position.x = tex.size.x * ofMap(i, 0, num_cols, num_cols, 0) * offsetExpMap;

        MeshHelper::TexQuad quad = MeshHelper::getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

void ofxSlitScan::drawVerticalTransition( int numRows, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &contentSize,
    ofMesh &mesh, float animSlit, float animMoveUp, float animMaskOut ) const
{
    int maskPos = 0;
    // float maskPos = 1.0f / 5.0f;
    float maskTarget = position.y + size.y * float( maskPos ) - size.y / float( numRows );

    for( int i = 0; i < numRows; i++ ) {
        MeshHelper::RectData where;

        float startSize = size.y / float( numRows );
        where.size.x = size.x;

        float imgY = position.y + startSize * float( i );
        if( i > numRows * maskPos ) {
            float moveDist = abs( imgY - maskTarget );
            where.position.y = imgY + size.y - size.y * animMoveUp - moveDist * animMaskOut;
        }
        else {
            float moveDist = abs( imgY - maskTarget );
            where.position.y = imgY + size.y - size.y * animMoveUp + moveDist * animMaskOut;
        }

        where.size.y = size.y / float( numRows );

        where.position.x = 0.0f;

        // float sizePercent = where.size.y / ofGetHeight();
        float sizePercent = startSize / size.y;
        float mapCounter = ofMap( float( i ), 0, float( numRows + 2 ), 0, 1 );
        float offsetExp = powf( mapCounter, 4.0f * animSlit );

        float offsetExpMap;
        offsetExpMap = ofMap( offsetExp, 0.0f, 1.0f, 1.0f, sizePercent );
        // offsetExpMap = ofClamp(offsetExpMap, 1.0f, 0.0f);

        MeshHelper::RectData tex;
        tex.size.x = contentSize.x;
        tex.size.y = contentSize.y / float( numRows ) * offsetExpMap; // *percent_height;
        tex.position.x = 0.0f;
        tex.position.y = tex.size.y * float( i );

        MeshHelper::TexQuad quad = MeshHelper::getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

void ofxSlitScan::drawVerticalBase( int numRows, const glm::vec2 &position, const glm::vec2 &size, const ofTexture &texture, ofMesh &mesh,
    float animMoveUp, float offsetY ) const
{
    for( int i = 0; i < numRows; i++ ) {
        MeshHelper::RectData where;

        float startSize = size.y / float( numRows );
        where.size.x = size.x;
        where.size.y = size.y / float( numRows );
        where.position.x = 0.0f;

        float startPos = position.y + size.y;
        float targetPos = position.y + startSize * float( i );
        where.position.y = startPos - abs( startPos - targetPos ) * animMoveUp;

        MeshHelper::RectData tex;

        glm::vec2 contentSize = glm::vec2( texture.getWidth(), texture.getHeight() );
        tex.size.x = contentSize.x;
        tex.size.y = contentSize.y / float( numRows ); // *percent_height;
        tex.position.x = 0.0f;
        float offset = ofMap( offsetY, 0.0f, 1.0f, 1.0f, 0.6f );
        tex.position.y = tex.size.y * float( i ) - contentSize.y / float( numRows ) * float( i ) * offset;

        MeshHelper::TexQuad quad = MeshHelper::getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

void ofxSlitScan::drawVerticalOverlay(
    int numRows, const glm::vec2 &position, const glm::vec2 &size, const ofTexture &texture, ofMesh &mesh, float animMoveUp, float offsetY )
{
}

void ofxSlitScan::drawVerticalMaskOut( int numCols, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &contentSize,
    ofMesh &mesh, const std::vector<float> &animValues )
{
    for( int i = 0; i < numCols; i++ ) {
        MeshHelper::RectData where;

        where.size.x = size.x / float( numCols );
        where.size.y = size.y - size.y * animValues[i];
        where.position.x = where.size.x * float( i );
        where.position.y = position.y;

        MeshHelper::RectData tex;

        // animation values
        tex.size.y = contentSize.y - contentSize.y * animValues[i];
        tex.size.x = contentSize.x / float( numCols );
        tex.position.y = 0.0f;
        tex.position.x = tex.size.x * float( i );

        MeshHelper::TexQuad quad = MeshHelper::getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

void ofxSlitScan::drawMaskIn(
    int numRows, float rowHeight, const glm::vec2 &contentSize, ofMesh &mesh, const glm::vec2 &position, float animVal )
{
    for( int i = 0; i < numRows; i++ ) {

        float posOffset = rowHeight;

        MeshHelper::RectData where;
        where.size.x = contentSize.x;

        // float size_offset = ofMap( i, 0, num_rows-1, 0, 1 );
        // where.size.y = row_height * size_offset;

        where.size.y = rowHeight;
        where.position.x = position.x;
        where.position.y = position.y + rowHeight * float( i ) + posOffset * float( i );

        MeshHelper::RectData tex;

        /*
        //uncomment for debug
        ofSetColor( 255, 0, 0, 100 );
        ofDrawRectangle( where.position.x, where.position.y, where.size.x, where.size.y );
        ofSetColor( 255 );
        */

        tex.size.x = contentSize.x;
        // tex.size.y = content_size.y / num_rows * size_offset;
        tex.size.y = rowHeight;
        tex.position.x = 0.0f;
        tex.position.y = tex.size.y * float( i ) - animVal;

        MeshHelper::TexQuad quad = MeshHelper::getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}


#pragma mark FUNCTION UTILS

float ofxSlitScan::cosineApproximation( float x )
{
    float x2 = x * x;
    float x4 = x2 * x2;
    float x6 = x4 * x2;

    float fa = 4.0f / 9.0f;
    float fb = 17.0f / 9.0f;
    float fc = 22.0f / 9.0f;

    float y = fa * x6 - fb * x4 + fc * x2;
    return y;
}

float ofxSlitScan::doubleOddPolynomialSeat( float x, float a, float b, int n ) const
{
    float epsilon = 0.00001f;
    float minParamA = 0.0f + epsilon;
    float maxParamA = 1.0f - epsilon;
    float minParamB = 0.0f;
    float maxParamB = 1.0f;
    a = glm::min( maxParamA, glm::max( minParamA, a ) );
    b = glm::min( maxParamB, glm::max( minParamB, b ) );

    int   p = 2 * n + 1;
    float y;
    if( x <= a ) {
        y = b - b * pow( 1 - x / a, p );
    }
    else {
        y = b + ( 1 - b ) * pow( ( x - a ) / ( 1 - a ), p );
    }
    return y;
}

float ofxSlitScan::doublePolynomialSigmoid( float x, float a, float b, int n ) const
{
    float y;
    if( n % 2 == 0 ) {
        // even polynomial
        if( x <= 0.5f ) {
            y = pow( 2.0f * x, n ) / 2.0f;
        }
        else {
            y = 1.0f - pow( 2.0f * ( x - 1 ), n ) / 2.0f;
        }
    }

    else {
        // odd polynomial
        if( x <= 0.5f ) {
            y = pow( 2.0f * x, n ) / 2.0f;
        }
        else {
            y = 1.0f + pow( 2.0f * ( x - 1 ), n ) / 2.0f;
        }
    }

    return y;
}

void ofxSlitScan::drawMesh( const ofTexture &texture, const ofMesh &mesh )
{
    //! draw mesh
    texture.bind();
    mesh.draw();
    texture.unbind();
}