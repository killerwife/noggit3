// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include <noggit/ConfigFile.h>
#include <noggit/Log.h>
#include <noggit/Settings.h>

#include <boost/filesystem.hpp>

Settings::Settings()
{
  // set hardcoded till settings get serialized
  this->random_rotation = false;
  this->random_size = false;
  this->random_tilt = false;
  this->AutoSelectingMode = true;
  this->holelinesOn = false;
  this->FarZ = 1024;
  this->_noAntiAliasing = false;
  this->copyModelStats = true;
    this->tabletMode = false;
  this->renderModelsWithBox = false;

  if (boost::filesystem::exists("noggit.conf"))
  {
    ConfigFile config("noggit.conf");
    config.readInto(this->FarZ, "FarZ");
    config.readInto(_noAntiAliasing, "noAntiAliasing");
    config.readInto(this->wodSavePath, "wodSavePath");
    config.readInto(this->tabletMode, "TabletMode");
    if (!config.readInto(this->importFile, "ImportFile"))
    {
      // use default import file if not found in config
      importFile = "Import.txt";
    }
    config.readInto(this->wmvLogFile, "wmvLogFile");
  }

}

const bool& Settings::noAntiAliasing() const
{
  return _noAntiAliasing;
}

Settings* Settings::instance = 0;

Settings* Settings::getInstance()
{
  if (!instance)
    instance = new Settings();
  return instance;
}