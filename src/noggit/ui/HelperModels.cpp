// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include <noggit/ui/HelperModels.h>
#include <noggit/ui/Button.h>

#include <algorithm>

#include <noggit/application.h> // fonts
#include <noggit/ui/Text.h>
#include <noggit/ui/Texture.h>
#include <noggit/Video.h> // video
#include <noggit/MapView.h>

#include <noggit/Log.h>

void addModel(UIFrame *f, int model)
{
  (static_cast<UIHelperModels *>(f->parent()))->addModelNow(model);
}

UIHelperModels::UIHelperModels(MapView *mapview)
  : UICloseWindow((float)video.xres() / 2.0f - (float)winWidth / 2.0f, (float)video.yres() / 2.0f - (float)winHeight / 2.0f, (float)winWidth, (float)winHeight, "")
{
  /*
  Cube 100", InsertObject, 4  );
  Cube 250", InsertObject, 5  );
  Cube 500", InsertObject, 6  );
  Cube 1000", InsertObject, 7  );
  Disc 50", InsertObject, 8  );
  Disc 200", InsertObject, 9  );
  Disc 777", InsertObject, 10  );
  Sphere 50", InsertObject, 11  );
  Sphere 200", InsertObject, 12  );
  Sphere 777", InsertObject, 13  );

  */
  const float buttonWidth = 140.0f;
  const float buttonheight = 30.0f;
  float leftStart = 10.0f;
  const float topStart = 53.0f;
  float currentPos = topStart;


  addChild(new UITexture(10.0f, 10.0f, 64.0f, 64.0f, "Interface\\ICONS\\INV_Misc_EngGizmos_swissArmy.blp"));
  addChild(new UIText(95.0f, 20.0f, "Select a model to add.", app.getArial14(), eJustifyLeft));
  addChild(new UIText(95.0f, 40.0f, "You must select a chunk first!", app.getArial14(), eJustifyLeft));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Human scale", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 2));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Cube 50", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 3));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Cube 100", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 4));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Cube 250", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 5));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Cube 500", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 6));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Cube 1000", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 7));

  leftStart = 160.0f;
  currentPos = topStart;
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Disc 50", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 8));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Disc 200", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 9));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Disc 777", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 10));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Sphere 50", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 11));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Sphere 200", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 12));
  addChild(new UIButton(leftStart, currentPos += (buttonheight - 5), buttonWidth, buttonheight, "Sphere 777", "Interface\\BUTTONS\\UI-DialogBox-Button-Disabled.blp", "Interface\\BUTTONS\\UI-DialogBox-Button-Down.blp", addModel, 13));


}

void UIHelperModels::resize()
{
  x(std::max((video.xres() / 2.0f) - (winWidth / 2.0f), 0.0f));
  y(std::max((video.yres() / 2.0f) - (winHeight / 2.0f), 0.0f));
}

void UIHelperModels::addModelNow(int model)
{
  this->_mapView->inserObjectFromExtern(model);
}
