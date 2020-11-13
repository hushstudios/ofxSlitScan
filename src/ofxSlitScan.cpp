#include "ofxSlitScan.h"

ofxSlitScan::ofxSlitScan()
{
}

ofxSlitScan::~ofxSlitScan()
{
}

void ofxSlitScan::setup()
{
}

void ofxSlitScan::update( float dt )
{
}

void ofxSlitScan::draw()
{
}


void ofxSlitScan::drawVerticalSlotIn(
    int num_cols, glm::vec2 size, glm::vec2 content_size, ofMesh &mesh, glm::vec2 where_start, glm::vec2 where_target, float anim_val )
{

    for( int i = 0; i < num_cols; i++ ) {
        MeshHelper::RectData where;
        where.size.x = size.x / num_cols;
        where.size.y = size.y;
        where.pos.x = where.size.x * i + where_start.x + abs( where_target.x - where_start.x ) * ofMap( anim_val, 1.0f, 0.0f, 0.0f, 1.0f );
        where.pos.y = where_start.y + abs( where_target.y - where_start.y ) * ofMap( anim_val, 1.0f, 0.0f, 0.0f, 1.0f );
        // where.pos.y = proto_val;

        float size_percent = where.size.y / size.y;
        float mapCounter = ofMap( i, -1, num_cols - 1, 1, 0 );
        // float mapCounter = ofMap(i, 0, num_cols, 0, 1); //uncomment for right to left slot in
        float offSsetExp = powf( mapCounter, 2.0f );
        float offSsetExp_map = ofMap( offSsetExp, 0, 1, 10.0f, ( 1 - size_percent ) );

        MeshHelper::RectData tex;
        // glm::vec2            content_size = content_size;

        // start values
        glm::vec2 start_size, start_pos;
        glm::vec2 target_size, target_pos;

        start_size.y = content_size.y;
        start_size.x = content_size.x / num_cols;
        start_pos.y = 0;
        start_pos.x = tex.size.x * i;


        // animation vals
        target_size.y = content_size.y * offSsetExp_map;
        target_size.x = content_size.x / num_cols;
        target_pos.y = content_size.y * offSsetExp_map;
        target_pos.x = tex.size.x * i;

        tex.size.y = start_size.y - abs( start_size.y - target_size.y ) * anim_val;
        tex.size.x = content_size.x / num_cols;
        tex.pos.y = start_pos.y + abs( start_pos.y - target_pos.y ) * anim_val;
        tex.pos.x = tex.size.x * i;

        MeshHelper::TexQuad quad = MeshHelper::one().getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

#pragma region VSS


void ofxSlitScan::typeVSSSlotIn( int num_cols, glm::vec2 size, glm::vec2 content_size, ofMesh &mesh, glm::vec2 where_start,
    glm::vec2 where_target, float xoffset, float anim_val )
{
    // add quad on the offset part, then start the slit part for just text size, then add another quad to fill to camvas size
    MeshHelper::RectData where;
    where.pos.x = 0;
    where.pos.y = where_start.y;
    where.size.y = size.y;
    where.size.x = xoffset;
    MeshHelper::RectData tex;
    tex.size.x = xoffset;
    tex.size.y = content_size.y;
    tex.pos.x = 0;
    tex.pos.y = 0;
    MeshHelper::TexQuad quad = MeshHelper::one().getQuad( where, tex );
    MeshHelper::one().addToMesh( mesh, quad );

    // add slit scan with x offset
    for( int i = 0; i < num_cols; i++ ) {
        MeshHelper::RectData where;
        where.size.x = content_size.x / num_cols;
        where.size.y = content_size.y;
        where.pos.x = xoffset + where.size.x * i + where_start.x
            + abs( where_target.x - where_start.x ) * ofMap( anim_val, 1.0f, 0.0f, 0.0f, 1.0f );
        where.pos.y = where_start.y + abs( where_target.y - where_start.y ) * ofMap( anim_val, 1.0f, 0.0f, 0.0f, 1.0f );

        float size_percent = where.size.y / size.y;
        float mapCounter = ofMap( i, -1, num_cols - 1, 1, 0 );
        // float mapCounter = ofMap(i, 0, num_cols, 0, 1); //uncomment for right to left slot in
        float offSsetExp = powf( mapCounter, 2.0f );
        float offSsetExp_map = ofMap( offSsetExp, 0, 1, 10.0f, ( 1 - size_percent ) );

        MeshHelper::RectData tex;

        // start values
        glm::vec2 start_size, start_pos;
        glm::vec2 target_size, target_pos;

        start_size.y = content_size.y;
        start_size.x = content_size.x / num_cols;
        start_pos.y = 0;
        start_pos.x = tex.size.x * i;


        // animation vals
        target_size.y = content_size.y * offSsetExp_map;
        target_size.x = content_size.x / num_cols;
        target_pos.y = content_size.y * offSsetExp_map;
        target_pos.x = tex.size.x * i;

        tex.size.y = start_size.y - abs( start_size.y - target_size.y ) * anim_val;
        tex.size.x = content_size.x / num_cols;
        tex.pos.y = start_pos.y + abs( start_pos.y - target_pos.y ) * anim_val;
        tex.pos.x = xoffset + tex.size.x * i;

        MeshHelper::TexQuad quad = MeshHelper::one().getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

#pragma endregion

void ofxSlitScan::typeVSSSlotOut( int num_cols, glm::vec2 size, glm::vec2 content_size, ofMesh &mesh, glm::vec2 where_start,
    glm::vec2 where_target, float xoffset, float anim_val )
{
    // add quad on the offset part, then start the slit part for just text size, then add another quad to fill to camvas size
    MeshHelper::RectData where;
    where.pos.x = 0;
    where.pos.y = where_start.y;
    where.size.y = size.y;
    where.size.x = xoffset;
    MeshHelper::RectData tex;
    tex.size.x = xoffset;
    tex.size.y = content_size.y;
    tex.pos.x = 0;
    tex.pos.y = 0;
    MeshHelper::TexQuad quad = MeshHelper::one().getQuad( where, tex );
    MeshHelper::one().addToMesh( mesh, quad );

    // add slit scan with x offset
    for( int i = 0; i < num_cols; i++ ) {
        MeshHelper::RectData where;
        where.size.x = content_size.x / num_cols;
        where.size.y = content_size.y;
        where.pos.x = xoffset + where.size.x * i + where_start.x
            + abs( where_target.x - where_start.x ) * ofMap( anim_val, 1.0f, 0.0f, 0.0f, 1.0f );
        float indexScale = 1 - ( i / ( num_cols - 1 ) );
        where.pos.y = where_start.y + abs( where_target.y - where_start.y ) * ofMap( anim_val, 1.0f, 0.0f, 0.0f, 1.0f );

        float size_percent = where.size.y / size.y;
        float mapCounter = ofMap( i, -1, num_cols - 1, 1, 0 );
        float offSsetExp = powf( mapCounter, 2.0f );
        float offSsetExp_map = ofMap( offSsetExp, 0, 1, ( 1 - size_percent ), 5.0f );

        MeshHelper::RectData tex;

        // start values
        glm::vec2 start_size, start_pos;
        glm::vec2 target_size, target_pos;

        start_size.y = content_size.y;
        start_size.x = content_size.x / num_cols;
        start_pos.y = 0;
        start_pos.x = tex.size.x * i;


        // animation vals
        target_size.y = content_size.y; // *offSsetExp_map;
        target_size.x = content_size.x / num_cols;
        target_pos.y = content_size.y * offSsetExp_map;
        target_pos.x = tex.size.x * i;

        tex.size.y = start_size.y - abs( start_size.y - target_size.y ) * anim_val;
        tex.size.x = content_size.x / num_cols;
        tex.pos.y = start_pos.y - abs( start_pos.y - target_pos.y ) * ( 1 - anim_val );
        tex.pos.x = xoffset + tex.size.x * i;

        MeshHelper::TexQuad quad = MeshHelper::one().getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

void ofxSlitScan::drawHorizontalPixel(
    glm::vec2 pos, glm::vec2 size, glm::vec2 content_size, ofMesh &mesh, float anim_val, float target_ypos )
{
    MeshHelper::RectData where;
    where.size.x = size.x;
    where.size.y = size.y;
    where.pos.x = pos.x;
    where.pos.y = pos.y + anim_val * target_ypos;

    MeshHelper::RectData tex;
    // glm::vec2 content_size = glm::vec2(tex_ref.getWidth(), tex_ref.getHeight());

    tex.size.y = content_size.y;
    tex.size.x = content_size.x;
    tex.pos.y = 0.0f;
    tex.pos.x = 0.0f;


    //! crop
    MeshHelper::TexQuad temp;

    //! MESH
    temp.verts.tl.x = where.pos.x;
    temp.verts.tl.y = where.pos.y;

    temp.verts.tr.x = where.pos.x + where.size.x;
    temp.verts.tr.y = where.pos.y;

    temp.verts.bl.x = where.pos.x;
    temp.verts.bl.y = where.pos.y + where.size.y * ofMap( anim_val, 0, 1, 1, 0 );

    temp.verts.br.x = where.pos.x + where.size.x;
    temp.verts.br.y = where.pos.y + where.size.y * ofMap( anim_val, 0, 1, 1, 0 );

    //! TEXTURE
    temp.texCoords.tl.x = tex.pos.x;
    temp.texCoords.tl.y = tex.size.y * anim_val;

    temp.texCoords.tr.x = tex.pos.x + tex.size.x;
    temp.texCoords.tr.y = tex.size.y * anim_val;

    temp.texCoords.bl.x = tex.pos.x;
    temp.texCoords.bl.y = tex.pos.y + tex.size.y;

    temp.texCoords.br.x = tex.pos.x + tex.size.x;
    temp.texCoords.br.y = tex.pos.y + tex.size.y;

    MeshHelper::one().addToMesh( mesh, temp );

    MeshHelper::TexQuad pixel_stretch;

    //! MESH
    pixel_stretch.verts.tl.x = where.pos.x;
    pixel_stretch.verts.tl.y = where.pos.y + where.size.y * ofMap( anim_val, 0, 1, 1, 0 );

    pixel_stretch.verts.tr.x = where.pos.x + where.size.x;
    pixel_stretch.verts.tr.y = where.pos.y + where.size.y * ofMap( anim_val, 0, 1, 1, 0 );

    pixel_stretch.verts.bl.x = where.pos.x;
    pixel_stretch.verts.bl.y = where.pos.y + where.size.y;

    pixel_stretch.verts.br.x = where.pos.x + where.size.x;
    pixel_stretch.verts.br.y = where.pos.y + where.size.y;

    //! TEXTURE
    pixel_stretch.texCoords.tl.x = tex.pos.x;
    pixel_stretch.texCoords.tl.y = tex.size.y;

    pixel_stretch.texCoords.tr.x = tex.pos.x + tex.size.x;
    pixel_stretch.texCoords.tr.y = pixel_stretch.texCoords.tl.y;

    pixel_stretch.texCoords.bl.x = pixel_stretch.texCoords.tl.x;
    pixel_stretch.texCoords.bl.y = tex.size.y;

    pixel_stretch.texCoords.br.x = pixel_stretch.texCoords.tr.x;
    pixel_stretch.texCoords.br.y = pixel_stretch.texCoords.bl.y;

    MeshHelper::one().addToMesh( mesh, pixel_stretch );
}

void ofxSlitScan::drawHorSwipeVertSC(
    int num_cols, glm::vec2 pos, glm::vec2 size, glm::vec2 content_size, ofMesh &mesh, float anim_wipe, float anim_slit, bool lr )
{


    for( int i = 0; i < num_cols; i++ ) {


        MeshHelper::RectData where;
        where.size.x = size.x / num_cols;
        where.size.y = size.y;
        where.pos.y = pos.y;
        if( lr ) {
            where.pos.x = pos.x + where.size.x * i - size.x + size.x * anim_wipe;
        }
        else {
            where.pos.x = pos.x + where.size.x * i + size.x - size.x * anim_wipe;
        }


        float size_percent = where.size.x / size.x;
        float mapCounter = ofMap( i, 0, num_cols + 2, 1, 0 );
        // float mapCounter = ofMap(i, 0, num_cols + 2, 0, 1);

        //! functions
        // float offSsetExp = powf(mapCounter, 5.0 * anim_slit);
        // float offSsetExp = 1 - sqrt(1 - powf(mapCounter, 7.0 * anim_slit));
        float offSsetExp = doubleOddPolynomialSeat( mapCounter, 0.25 * anim_slit, 1.25 * ofMap( anim_slit, 1, 0, 0, 1 ), 0.0 );
        // float offSsetExp = doubleOddPolynomialSeat(mapCounter, 1.6 * anim_slit, 1.5 * ofMap(anim_slit, 1, 0, 0, 1), 8.0);

        float offSsetExp_map;
        offSsetExp_map = ofMap( offSsetExp, 0, 1, size_percent, 1.0f );
        offSsetExp_map = ofClamp( offSsetExp_map, size_percent, 1.0f );

        MeshHelper::RectData tex;

        tex.size.y = content_size.y;
        tex.size.x = content_size.x / num_cols;
        tex.pos.y = 0.0f;

        // add dist?
        float i_start = (float)num_cols - 1.;
        float i_target = (float)i;
        float final_i = i_start - abs( i_start - i_target ) * offSsetExp_map;
        // tex.pos.x = tex.size.x * final_i;

        tex.pos.x = tex.size.x * i * offSsetExp_map;
        // tex.pos.x = tex.size.x * ofMap(i, 0, num_cols, num_cols, 0) * offSsetExp_map;

        MeshHelper::TexQuad quad = MeshHelper::one().getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

void ofxSlitScan::drawVerticalTransition( int num_rows, glm::vec2 pos, glm::vec2 size, glm::vec2 content_size, ofMesh &mesh,
    float anim_slit, float anim_move_up, float anim_mask_out )
{

    float mask_pos = 0.0f;
    // float mask_pos = 1.0 / 5.0;
    float mask_target = pos.y + size.y * mask_pos - size.y / num_rows;

    for( int i = 0; i < num_rows; i++ ) {


        MeshHelper::RectData where;
        float                start_size = size.y / num_rows;
        where.size.x = size.x;

        float img_y_pos = pos.y + start_size * i;
        if( i > num_rows * mask_pos ) {
            float move_dist = abs( img_y_pos - mask_target );
            where.pos.y = img_y_pos + size.y - (size.y) * anim_move_up - move_dist * anim_mask_out;
        }
        else {
            float move_dist = abs( img_y_pos - mask_target );
            where.pos.y = img_y_pos + size.y - size.y * anim_move_up + move_dist * anim_mask_out;
        }

        where.size.y = size.y / num_rows;

        where.pos.x = 0.0f;


        // float size_percent = where.size.y / ofGetHeight();
        float size_percent = start_size / size.y;
        float mapCounter = ofMap( i, 0, num_rows + 2, 0, 1 );
        float offSsetExp = powf( mapCounter, 4.0 * anim_slit );

        float offSsetExp_map;
        offSsetExp_map = ofMap( offSsetExp, 0.0, 1.0, 1.0, size_percent );
        // offSsetExp_map = ofClamp(offSsetExp_map, 1.0, 0.0f);


        MeshHelper::RectData tex;


        tex.size.x = content_size.x;
        tex.size.y = content_size.y / num_rows * offSsetExp_map; // *percent_height;
        tex.pos.x = 0.0f;
        tex.pos.y = tex.size.y * i;

        MeshHelper::TexQuad quad = MeshHelper::one().getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

void ofxSlitScan::drawVerticalBase(
    int num_rows, glm::vec2 pos, glm::vec2 size, ofTexture &tex_ref, ofMesh &mesh, float anim_move_up, float offset_y )
{

    for( int i = 0; i < num_rows; i++ ) {


        MeshHelper::RectData where;
        float                start_size = size.y / num_rows;
        where.size.x = size.x;
        where.size.y = size.y / num_rows;
        where.pos.x = 0.0f;

        float start_pos = pos.y + size.y;
        float target_pos = pos.y + start_size * i;
        where.pos.y = start_pos - abs( start_pos - target_pos ) * anim_move_up;

        MeshHelper::RectData tex;
        glm::vec2            content_size = glm::vec2( tex_ref.getWidth(), tex_ref.getHeight() );


        tex.size.x = content_size.x;
        tex.size.y = content_size.y / num_rows; // *percent_height;
        tex.pos.x = 0.0f;
        float offset = ofMap( offset_y, 0.0, 1.0, 1.0, 0.6 );
        tex.pos.y = tex.size.y * i - content_size.y / num_rows * i * offset;

        MeshHelper::TexQuad quad = MeshHelper::one().getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

void ofxSlitScan::drawVerticalOverlay(
    int num_rows, glm::vec2 pos, glm::vec2 size, ofTexture &tex_ref, ofMesh &mesh, float anim_move_up, float offset_y )
{
}

void ofxSlitScan::drawVerticalMaskOut(
    int num_cols, glm::vec2 pos, glm::vec2 size, glm::vec2 content_size, ofMesh &mesh, vector<float> &anim_vals )
{
    for( int i = 0; i < num_cols; i++ ) {
        MeshHelper::RectData where;

        where.size.x = size.x / num_cols;
        where.size.y = size.y - size.y * anim_vals[i];
        where.pos.x = where.size.x * i;
        where.pos.y = pos.y;

        MeshHelper::RectData tex;

        // animation vals
        tex.size.y = content_size.y - content_size.y * anim_vals[i];
        tex.size.x = content_size.x / num_cols;
        tex.pos.y = 0.0f;
        tex.pos.x = tex.size.x * i;

        MeshHelper::TexQuad quad = MeshHelper::one().getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}

void ofxSlitScan::drawMaskIn( int num_rows, float row_height, glm::vec2 content_size, ofMesh &mesh, glm::vec2 pos, float anim_val )
{
    for( int i = 0; i < num_rows; i++ ) {

        float pos_offset = row_height;

        MeshHelper::RectData where;
        where.size.x = content_size.x;

        // float size_offset = ofMap( i, 0, num_rows-1, 0, 1 );
        // where.size.y = row_height * size_offset;

        where.size.y = row_height;
        where.pos.x = pos.x;
        where.pos.y = pos.y + row_height * i + pos_offset * i;

        MeshHelper::RectData tex;

        /*
        //uncomment for debug
        ofSetColor( 255, 0, 0, 100 );
        ofDrawRectangle( where.pos.x, where.pos.y, where.size.x, where.size.y );
        ofSetColor( 255 );
        */

        tex.size.x = content_size.x;
        // tex.size.y = content_size.y / num_rows * size_offset;
        tex.size.y = row_height;
        tex.pos.x = 0.0f;
        tex.pos.y = tex.size.y * i - anim_val;

        MeshHelper::TexQuad quad = MeshHelper::one().getQuad( where, tex );
        MeshHelper::one().addToMesh( mesh, quad );
    }
}


#pragma mark FUNCTION UTILS

float ofxSlitScan::blinnWyvillCosineApproximation( float x )
{

    float x2 = x * x;
    float x4 = x2 * x2;
    float x6 = x4 * x2;

    float fa = ( 4.0 / 9.0 );
    float fb = ( 17.0 / 9.0 );
    float fc = ( 22.0 / 9.0 );

    float y = fa * x6 - fb * x4 + fc * x2;
    return y;
}

float ofxSlitScan::doubleOddPolynomialSeat( float x, float a, float b, int n )
{

    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    a = min( max_param_a, max( min_param_a, a ) );
    b = min( max_param_b, max( min_param_b, b ) );

    int   p = 2 * n + 1;
    float y = 0;
    if( x <= a ) {
        y = b - b * pow( 1 - x / a, p );
    }
    else {
        y = b + ( 1 - b ) * pow( ( x - a ) / ( 1 - a ), p );
    }
    return y;
}

float ofxSlitScan::doublePolynomialSigmoid( float x, float a, float b, int n )
{

    float y = 0;
    if( n % 2 == 0 ) {
        // even polynomial
        if( x <= 0.5 ) {
            y = pow( 2.0 * x, n ) / 2.0;
        }
        else {
            y = 1.0 - pow( 2 * ( x - 1 ), n ) / 2.0;
        }
    }

    else {
        // odd polynomial
        if( x <= 0.5 ) {
            y = pow( 2.0 * x, n ) / 2.0;
        }
        else {
            y = 1.0 + pow( 2.0 * ( x - 1 ), n ) / 2.0;
        }
    }

    return y;
}

void ofxSlitScan::drawMesh( ofTexture &tex_ref, ofMesh &mesh )
{
    //! draw mesh
    tex_ref.bind();
    mesh.draw();
    tex_ref.unbind();
}