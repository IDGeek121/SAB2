#include <glad/glad.h>

#include "entity.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "ring.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/camera.h"
#include "../entities/playersonic.h"
#include "../collision/collisionchecker.h"
#include "../collision/triangle3d.h"
#include "../toolbox/maths.h"
#include "../audio/audioplayer.h"
#include "../particles/particle.h"
#include "../particles/particleresources.h"
#include "../particles/particlemaster.h"
#include "shieldmagnet.h"
#include "ringmoving.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> Ring::models;


Ring::Ring()
{

}

Ring::Ring(float x, float y, float z)
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    moves = false;
    xVel = 0;
    yVel = 0;
    zVel = 0;
    grabTimer = 0;
    givesPoints = true;
    updateTransformationMatrix();
}

Ring::Ring(float x, float y, float z, float xVel, float yVel, float zVel)
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    moves = true;
    this->xVel = xVel;
    this->yVel = yVel;
    this->zVel = zVel;
    grabTimer = 60;
    givesPoints = false;
    updateTransformationMatrix();
}

void Ring::step()
{/*
    increaseRotation(0, 5, 0);

    if (abs(getX() - Global::gameCamera->eye.x) > ENTITY_RENDER_DIST)
    {
        setVisible(false);
    }
    else
    {
        if (abs(getZ() - Global::gameCamera->eye.z) > ENTITY_RENDER_DIST)
        {
            setVisible(false);
        }
        else
        {
            setVisible(true);

            if (abs(getY() - Global::gameMainVehicle->getPosition()->y) < 40 &&
                abs(getZ() - Global::gameMainVehicle->getPosition()->z) < 40 &&
                abs(getX() - Global::gameMainVehicle->getPosition()->x) < 40 &&
                grabTimer == 0)
            {
                if ((Global::gameMainVehicle->getCenterPosition()-getPosition()).lengthSquared() < (5.0f*5.0f + 9.0f*9.0f))
                {
            //if (grabTimer == 0 &&
            //    Global::gamePlayer->getX() > getX() - hitboxH - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getX() < getX() + hitboxH + Global::gamePlayer->getHitboxHorizontal() &&
            //    Global::gamePlayer->getZ() > getZ() - hitboxH - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getZ() < getZ() + hitboxH + Global::gamePlayer->getHitboxHorizontal() &&
            //    Global::gamePlayer->getY() > getY() - hitboxV - Global::gamePlayer->getHitboxVertical()   && Global::gamePlayer->getY() < getY() + hitboxV)
            //{
                    AudioPlayer::play(4, getPosition());

                    for (int i = 0; i < 10; i++)
                    {
                        Vector3f pos(
                            getX() + Maths::random() * 8 - 4,
                            getY() + Maths::random() * 8 - 4,
                            getZ() + Maths::random() * 8 - 4);

                        Vector3f vel(0, 0.4f, 0);

                        new Particle(ParticleResources::textureSparkleYellow, &pos, &vel,
                            0.025f, 30, 0, 7, -(7.0f / 30.0f), false);
                    }

                    Global::increaseRingCount(1);

                    if (givesPoints)
                    {
                        Global::gameScore += 10;
                    }

                    Global::deleteEntity(this);
                    return;
                }
            }

            if (moves)
            {
                grabTimer = std::max(0, grabTimer - 1);

                yVel -= 0.1f; //gravity

                Vector3f velVec(xVel, yVel, zVel);
                velVec.scale(0.99f); //air friction
                xVel = velVec.x;
                yVel = velVec.y;
                zVel = velVec.z;

                if (CollisionChecker::checkCollision(getX(), getY() - 5.0f, getZ(), getX() + xVel, getY() + yVel - 5.0f, getZ() + zVel))
                {
                    setPosition(CollisionChecker::getCollidePosition());
                    increasePosition(0, 5.0f, 0);

                    Vector3f normal = CollisionChecker::getCollideTriangle()->normal;
                    float speed = sqrtf(xVel*xVel + yVel*yVel + zVel*zVel);

                    if (speed > 0.5f)
                    {
                        Vector3f vel(xVel, yVel, zVel);
                        Vector3f newVel = bounceVector(&vel, &normal, 0.7f);
                        xVel = newVel.x;
                        yVel = newVel.y;
                        zVel = newVel.z;
                        increasePosition(normal.x*0.01f, normal.y*0.01f, normal.z*0.01f);
                    }
                    else
                    {
                        moves = false;
                        grabTimer = 0;
                    }
                }
                else
                {
                    increasePosition(xVel, yVel, zVel);
                }

                if (getY() < -100)
                {
                    Global::deleteEntity(this);
                }
            }
            else
            {
                if (Global::gamePlayer->getShieldMagnet() != nullptr)
                {
                    Vector3f diff = (*getPosition()) - Global::gamePlayer->getCenterPosition();

                    if (diff.lengthSquared() < 60*60)
                    {
                        trackingPlayer = true;
                    }

                    if (trackingPlayer)
                    {
                        diff.scale(-0.35f);
                        increasePosition(diff.x, diff.y, diff.z);
                    }
                }
                else
                {
                    trackingPlayer = false;
                }
            }

            updateTransformationMatrix();
        }
    }*/
    extern float dt;
    increaseRotation(0, 5*60*dt, 0);
    updateTransformationMatrix();

    if (fabsf(position.y - Global::gameMainPlayer->position.y) < 40 &&
        fabsf(position.z - Global::gameMainPlayer->position.z) < 40 &&
        fabsf(position.x - Global::gameMainPlayer->position.x) < 40 &&
        grabTimer == 0)
    {
        float toPlayerDistSquared = (Global::gameMainPlayer->getCenterPosition() - position).lengthSquared();
        if (toPlayerDistSquared < (11.0f*11.0f)) //collect ring range
        {
            AudioPlayer::play(4, getPosition());

            for (int i = 0; i < 10; i++)
            {
                Vector3f pos(
                    position.x + Maths::random() * 8 - 4,
                    position.y + Maths::random() * 8 - 4,
                    position.z + Maths::random() * 8 - 4);
            
                Vector3f partVel(0, 0.4f*60, 0);
            
                ParticleMaster::createParticle(ParticleResources::textureSparkleYellow, &pos, &partVel,
                    0.025f*60*60, 0.5f, 0, 4, -(4.0f / 0.5f), false, false, 0.5f, true);
            }

            Global::increaseRingCount(1);

            if (givesPoints)
            {
                Global::gameScore += 10;
            }

            Global::deleteChunkedEntity(this);
            return;
        }
        else
        {
            if (Global::gameMainPlayer->getShieldMagnet() != nullptr)
            {
                if (toPlayerDistSquared < 36.0f*36.0f) //attract ring range
                {
                    Global::deleteChunkedEntity(this);
                    RingMoving* newRing = new RingMoving(position.x, position.y, position.z); INCR_NEW("RingMoving")
                    Global::addEntity(newRing);
                }
            }
        }
    }
}

std::list<TexturedModel*>* Ring::getModels()
{
    return &Ring::models;
}

void Ring::loadStaticModels()
{
    if (Ring::models.size() > 0)
    {
        return;
    }

    #ifdef DEV_MODE
    std::fprintf(stdout, "Loading ring static models...\n");
    #endif

    loadModel(&Ring::models, "res/Models/Objects/Ring/", "Ring");
}

void Ring::deleteStaticModels()
{
    #ifdef DEV_MODE
    std::fprintf(stdout, "Deleting ring static models...\n");
    #endif

    Entity::deleteModels(&Ring::models);
}

const inline bool Ring::canLightdashOn()
{
    return true;
}
