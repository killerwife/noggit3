// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include <noggit/ui/About.h>

#include "revision.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

UIAbout::UIAbout()
  : QWidget (nullptr)
{
  //! \todo make nice looking again, I don't care currently
  new QVBoxLayout (this);

  //! \todo iconize
  layout()->addWidget (new QLabel ("interface/icons/inv_potion_83.blp", this));
  //! \todo was Skurri32
  layout()->addWidget (new QLabel ("Noggit Studio", this));
  layout()->addWidget (new QLabel ("a wow map editor for 3.3.5a", this));
  layout()->addWidget ( new QLabel ( "Ufoz [...], Cryect, Beket, Schlumpf, "
                                     "Tigurius, Steff, Garthog, Glararan, Cromon, "
                                     "Hanfer, Skarn, AxelSheva, Valium, Kaev, "
                                     "Adspartan", this
                                   )
                      );
  layout()->addWidget (new QLabel ("World of Warcraft is (C) Blizzard Entertainment", this));
  layout()->addWidget (new QLabel (STRPRODUCTVER, this));
  layout()->addWidget (new QLabel (__DATE__ ", " __TIME__, this));
}
