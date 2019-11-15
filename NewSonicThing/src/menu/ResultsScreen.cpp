#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "resultsscreen.h"
#include "../engineTester/main.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

#include "../fontMeshCreator/guitext.h"
#include "../fontMeshCreator/fonttype.h"
#include "../renderEngine/renderEngine.h"
#include "../toolbox/input.h"
#include "../toolbox/levelloader.h"
#include "../fontMeshCreator/guitext.h"
#include "../audio/audioplayer.h"
#include "../audio/source.h"
#include "../entities/camera.h"
#include "../guis/guitextureresources.h"
#include "../guis/guimanager.h"
#include "../guis/guitexture.h"
#include "mainmenu.h"
#include "../toolbox/maths.h"
#include "../fontMeshCreator/guitext.h"

ResultsScreen::ResultsScreen()
{
    fontSize = 0.05f;
    selectInputPrevious = false;
    backInputPrevious = false;
    loadResources();
}

ResultsScreen::~ResultsScreen()
{
    unloadResources();
}

void ResultsScreen::loadResources()
{
    if (textArcadeModeClear != nullptr)
    {
        std::fprintf(stdout, "Warning: ResultsScreen loading resources when they are already loaded.\n");
    }

    //extern unsigned int SCR_WIDTH;
    //extern unsigned int SCR_HEIGHT;
    //float aspectRatio = (float)SCR_WIDTH / SCR_HEIGHT;

    textArcadeModeClear = new GUIText("Congrats bro", 0.2f, Global::fontVipnagorgialla, 0.5f, 0.5f, 4, false); INCR_NEW("GUIText")
}

void ResultsScreen::unloadResources()
{
    if (textArcadeModeClear == nullptr)
    {
        std::fprintf(stdout, "Warning: ResultsScreen unloading resources when they are empty.\n");
    }

    textArcadeModeClear->deleteMe();
    delete textArcadeModeClear; INCR_DEL("GUIText")
    textArcadeModeClear = nullptr;
}

Menu* ResultsScreen::step()
{
    Menu* retVal = nullptr;

    bool pressedSelect = false;
    bool pressedBack = false;

    if ((Input::inputs.INPUT_ACTION1 && !Input::inputs.INPUT_PREVIOUS_ACTION1) || 
        (Input::inputs.INPUT_START && !Input::inputs.INPUT_PREVIOUS_START))
    {
        pressedSelect = true;
    }

    if (Input::inputs.INPUT_ACTION2 && !Input::inputs.INPUT_PREVIOUS_ACTION2)
    {
        pressedBack = true;
    }

    textArcadeModeClear->visible = true;

    if ((pressedSelect && !selectInputPrevious) ||
        (pressedBack && !backInputPrevious))
    {
        retVal = PopMenu::get();
    }

    selectInputPrevious = pressedSelect;
    backInputPrevious = pressedBack;

    return retVal;
}
