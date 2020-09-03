/*==============================================================================

    ofxVisualProgramming: A visual programming patching environment for OF

    Copyright (c) 2018 Emanuele Mazza aka n3m3da <emanuelemazza@d3cod3.org>

    ofxVisualProgramming is distributed under the MIT License.
    This gives everyone the freedoms to use ofxVisualProgramming in any context:
    commercial or non-commercial, public or private, open or closed source.

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

    See https://github.com/d3cod3/ofxVisualProgramming for documentation

==============================================================================*/

#ifndef OFXVP_BUILD_WITH_MINIMAL_OBJECTS

#include "Clamp.h"

//--------------------------------------------------------------
Clamp::Clamp() : PatchObject("clamp"){

    this->numInlets  = 3;
    this->numOutlets = 1;

    _inletParams[0] = new float();  // min
    *(float *)&_inletParams[0] = 0.0f;
    _inletParams[1] = new float();  // max
    *(float *)&_inletParams[1] = 0.0f;
    _inletParams[2] = new float();  // value
    *(float *)&_inletParams[2] = 0.0f;

    _outletParams[0] = new float(); // output
    *(float *)&_outletParams[0] = 0.0f;

    this->initInletsState();

    min     = 0.0f;
    max     = 1.0f;

    loaded  = false;

}

//--------------------------------------------------------------
void Clamp::newObject(){
    PatchObject::setName( this->objectName );

    this->addInlet(VP_LINK_NUMERIC,"value");
    this->addInlet(VP_LINK_NUMERIC,"min");
    this->addInlet(VP_LINK_NUMERIC,"max");

    this->addOutlet(VP_LINK_NUMERIC,"result");

    this->setCustomVar(static_cast<float>(min),"MIN");
    this->setCustomVar(static_cast<float>(max),"MAX");

}

//--------------------------------------------------------------
void Clamp::setupObjectContent(shared_ptr<ofAppGLFWWindow> &mainWindow){

}

//--------------------------------------------------------------
void Clamp::updateObjectContent(map<int,shared_ptr<PatchObject>> &patchObjects){
    if(this->inletsConnected[0]){
      *(float *)&_outletParams[0] = ofClamp(*(float *)&_inletParams[0],min,max);
    }else{
      *(float *)&_outletParams[0] = 0.0f;
    }

    if(this->inletsConnected[1]){
      min = *(float *)&_inletParams[1];
    }
    if(this->inletsConnected[2]){
      max = *(float *)&_inletParams[2];
    }

    if(!loaded){
        loaded = true;
        min = this->getCustomVar("MIN");
        max = this->getCustomVar("MAX");
    }
}

//--------------------------------------------------------------
void Clamp::drawObjectContent(ofxFontStash *font, shared_ptr<ofBaseGLRenderer>& glRenderer){
    ofSetColor(255);
}

//--------------------------------------------------------------
void Clamp::drawObjectNodeGui( ImGuiEx::NodeCanvas& _nodeCanvas ){

    // CONFIG GUI inside Menu
    if(_nodeCanvas.BeginNodeMenu()){

        ImGui::Separator();
        ImGui::Separator();
        ImGui::Separator();

        if (ImGui::BeginMenu("CONFIG"))
        {

            ImGuiEx::ObjectInfo(
                        "Force the numerical input between the configured range.",
                        "https://mosaic.d3cod3.org/reference.php?r=clamp", scaleFactor);

            ImGui::EndMenu();
        }

        _nodeCanvas.EndNodeMenu();
    }

    // Visualize (Object main view)
    if( _nodeCanvas.BeginNodeContent(ImGuiExNodeView_Visualise) ){

        ImGui::Dummy(ImVec2(-1,IMGUI_EX_NODE_CONTENT_PADDING*8*scaleFactor));

        if(ImGui::DragFloat("Min",&min,0.01f)){
            this->setCustomVar(static_cast<float>(min),"MIN");
        }
        ImGui::Spacing();
        if(ImGui::DragFloat("Max",&max,0.01f)){
            this->setCustomVar(static_cast<float>(max),"MAX");
        }

    }

}

//--------------------------------------------------------------
void Clamp::removeObjectContent(bool removeFileFromData){

}

OBJECT_REGISTER( Clamp, "clamp", OFXVP_OBJECT_CAT_MATH)

#endif
