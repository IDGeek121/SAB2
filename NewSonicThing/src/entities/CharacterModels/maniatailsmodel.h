#ifndef MANIATAILSMODEL_H
#define MANIATAILSMODEL_H

class TexturedModel;
class Limb;
class Body;
class ParticleTexture;
class Dummy;

#include <list>
#include <vector>
#include "../entity.h"
#include "playermodel.h"


class ManiaTailsModel : public PlayerModel
{
private:
    std::list<TexturedModel*>* models;

    const float displayHeightOffset = -0.5f;
    const float displayBallOffset = 3.0f;

    const float limbsScale = 1.0f;

    Body* myBody         = nullptr;
    Limb* myHead         = nullptr;
    Limb* myLeftHumerus  = nullptr;
    Limb* myLeftForearm  = nullptr;
    Limb* myLeftHand     = nullptr;
    Limb* myLeftThigh    = nullptr;
    Limb* myLeftShin     = nullptr;
    Limb* myLeftFoot     = nullptr;
    Limb* myRightHumerus = nullptr;
    Limb* myRightForearm = nullptr;
    Limb* myRightHand    = nullptr;
    Limb* myRightThigh   = nullptr;
    Limb* myRightShin    = nullptr;
    Limb* myRightFoot    = nullptr;

    Dummy* flyTails = nullptr;

    static std::list<TexturedModel*> modelBody;
    static std::list<TexturedModel*> modelHead;
    static std::list<TexturedModel*> modelLeftHumerus;
    static std::list<TexturedModel*> modelLeftForearm;
    static std::list<TexturedModel*> modelLeftHand;
    static std::list<TexturedModel*> modelLeftThigh;
    static std::list<TexturedModel*> modelLeftShin;
    static std::list<TexturedModel*> modelLeftFoot;
    static std::list<TexturedModel*> modelRightHumerus;
    static std::list<TexturedModel*> modelRightForearm;
    static std::list<TexturedModel*> modelRightHand;
    static std::list<TexturedModel*> modelRightThigh;
    static std::list<TexturedModel*> modelRightShin;
    static std::list<TexturedModel*> modelRightFoot;

    static std::list<TexturedModel*> modelDash0;
    static std::list<TexturedModel*> modelDash1;
    static std::list<TexturedModel*> modelDash2;
    static std::list<TexturedModel*> modelDash3;
    static std::list<TexturedModel*> modelDash4;
    static std::list<TexturedModel*> modelDash5;
    static std::list<TexturedModel*> modelDash6;
    static std::list<TexturedModel*> modelDash7;
    static std::list<TexturedModel*> modelDash8;
    static std::list<TexturedModel*> modelDash9;
    static std::list<TexturedModel*> modelDash10;
    static std::list<TexturedModel*> modelDash11;
    static std::list<TexturedModel*> modelDash12;
    static std::list<TexturedModel*> modelDash13;
    static std::list<TexturedModel*> modelDash14;
    static std::list<TexturedModel*> modelDash15;
    static std::list<TexturedModel*> modelDash16;
    static std::list<TexturedModel*> modelDash17;
    static std::list<TexturedModel*> modelJump;
    static std::list<TexturedModel*> modelJog0;
    static std::list<TexturedModel*> modelJog1;
    static std::list<TexturedModel*> modelJog2;
    static std::list<TexturedModel*> modelJog3;
    static std::list<TexturedModel*> modelJog4;
    static std::list<TexturedModel*> modelJog5;
    static std::list<TexturedModel*> modelJog6;
    static std::list<TexturedModel*> modelJog7;
    static std::list<TexturedModel*> modelJog8;
    static std::list<TexturedModel*> modelJog9;
    static std::list<TexturedModel*> modelJog10;
    static std::list<TexturedModel*> modelJog11;
    static std::list<TexturedModel*> modelJog12;
    static std::list<TexturedModel*> modelJog13;
    static std::list<TexturedModel*> modelJog14;
    static std::list<TexturedModel*> modelJog15;
    static std::list<TexturedModel*> modelJog16;
    static std::list<TexturedModel*> modelJog17;
    static std::list<TexturedModel*> modelGrind;
    static std::list<TexturedModel*> modelSkid;
    static std::list<TexturedModel*> modelLightdash;
    static std::list<TexturedModel*> modelFreefall;
    static std::list<TexturedModel*> modelStomp;
    static std::list<TexturedModel*> modelGrab;
    static std::list<TexturedModel*> modelFlyBody;
    static std::list<TexturedModel*> modelFlyBodyTired;
    static std::list<TexturedModel*> modelFlyTails;

    void setLimbsVisibility(bool newVisible);

    void updateLimbs(int animIndex, float time);

    void updateLimbsMatrix();

    void setFlyVisibility(bool newVisible);

    void updateFlyMatrix();

public:
    ManiaTailsModel();

    void step();

    void animate(int animIndex, float time);

    void setOrientation(float x, float y, float z, float xRot, float yRot, float zRot, float spinRot, Vector3f* up);

    void setBaseColor(float r, float g, float b);

    void setBaseAlpha(float a);

    void setBaseVisibility(bool newVisible);

    void setRenderOrderOverride(char newOrder);

    const float getDisplayBallOffset();

    ParticleTexture* getBallTexture();

    std::list<TexturedModel*>* getModels();

    static void loadStaticModels();

    static void deleteStaticModels();
};
#endif
