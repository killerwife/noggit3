// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include <noggit/AsyncLoader.h>// AsyncLoader
#include <noggit/Environment.h>
#include <noggit/Log.h> // LogDebug
#include <noggit/Model.h> // Model
#include <noggit/ModelManager.h> // ModelManager
#include <noggit/application.h> // app.loader()

#include <algorithm>

ModelManager::mapType ModelManager::items;

void ModelManager::report()
{
  std::string output = "Still in the model manager:\n";
  for (mapType::iterator t = items.begin(); t != items.end(); ++t)
  {
    output += "- " + t->first + "\n";
  }
  LogDebug << output;
}

Model* ModelManager::add(std::string name)
{
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);

  size_t found = name.rfind(".mdx");
  if (found != std::string::npos)
    name.replace(found, 4, ".m2");

  found = name.rfind(".mdl");
  if (found != std::string::npos)
    name.replace(found, 4, ".m2");

  if (items.find(name) == items.end())
  {
    items[name] = new Model(name);

    try
    {
      items[name]->finishLoading();
    }
    catch (const std::exception& e)
    {
      LogError << "Exception " << e.what() << " while loading " << name << std::endl;
    }

    //app.loader()->addObject( items[name] ); isnt that loading it two times?
  }

  items[name]->addReference();
  return items[name];
}

void ModelManager::delbyname(std::string name)
{
  std::transform(name.begin(), name.end(), name.begin(), ::tolower);

  size_t found = name.rfind(".mdx");
  if (found != std::string::npos)
    name.replace(found, 4, ".m2");

  found = name.rfind(".mdl");
  if (found != std::string::npos)
    name.replace(found, 4, ".m2");

  if (items.find(name) != items.end())
  {
    items[name]->removeReference();

    if (items[name]->hasNoReferences())
    {
      delete items[name];
      items.erase(items.find(name));
    }
  }
}

void ModelManager::resetAnim()
{
  for (ModelManager::mapType::iterator it = items.begin(); it != items.end(); ++it)
    it->second->animcalc = false;
}

void ModelManager::updateEmitters(float dt)
{
  for (ModelManager::mapType::iterator it = items.begin(); it != items.end(); ++it)
    it->second->updateEmitters(dt);
}
