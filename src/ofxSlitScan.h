#pragma once

#include "ofMesh.h"

class ofxSlitScan {
  public:
    ofxSlitScan() = default;

    //! city stream types
    void drawVerticalSlotIn( int numCols, const glm::vec2 &size, const glm::vec2 &contentSize, ofMesh &mesh, const glm::vec2 &whereStart,
        const glm::vec2 &whereTarget, float animVal ) const;

    static void drawHorizontalPixel(
        const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &contentSize, ofMesh &mesh, float animVal, float targetY );

    void drawHorSwipeVertSc( int numCols, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &contentSize, ofMesh &mesh,
        float animWipe, float animSlit, bool lr = false ) const;

    // story stream
    void drawVerticalTransition( int numRows, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &contentSize, ofMesh &mesh,
        float animSlit, float animMoveUp, float animMaskOut ) const;

    void drawVerticalBase( int numRows, const glm::vec2 &position, const glm::vec2 &size, const ofTexture &texture, ofMesh &mesh,
        float animMoveUp, float offsetY ) const;

    static void drawVerticalOverlay( int numRows, const glm::vec2 &position, const glm::vec2 &size, const ofTexture &texture, ofMesh &mesh,
        float animMoveUp, float offsetY );

    // vss
    void typeVssSlotIn( int numCols, const glm::vec2 &size, const glm::vec2 &contentSize, ofMesh &mesh, const glm::vec2 &whereStart,
        const glm::vec2 &whereTarget, float offsetX, float animVal ) const;

    void typeVssSlotOut( int numCols, const glm::vec2 &size, const glm::vec2 &contentSize, ofMesh &mesh, const glm::vec2 &whereStart,
        const glm::vec2 &whereTarget, float offsetX, float animVal ) const;

    // no pixel stretch
    static void drawVerticalMaskOut( int numCols, const glm::vec2 &position, const glm::vec2 &size, const glm::vec2 &contentSize,
        ofMesh &mesh, const std::vector<float> &animValues );

    static void drawMesh( const ofTexture &texture, const ofMesh &mesh );

    // text animation
    static void drawMaskIn(
        int numRows, float rowHeight, const glm::vec2 &contentSize, ofMesh &mesh, const glm::vec2 &position, float animVal );

  private:
    //! Blinn-Wyvill.
    static float cosineApproximation( float x );

    float doubleOddPolynomialSeat( float x, float a, float b, int n ) const;
    float doublePolynomialSigmoid( float x, float a, float b, int n ) const;
};