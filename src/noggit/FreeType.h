// FreeType.h is part of Noggit3, licensed via GNU General Publiicense (version 3).
// Bernd Lörwald <bloerwald+noggit@googlemail.com>
// Stephan Biegel <project.modcraft@googlemail.com>
// Tigurius <bstigurius@googlemail.com>

#ifndef FREE_TYPE_H
#define FREE_TYPE_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>

#include <opengl/call_list.h>

namespace opengl
{
  class texture;
}

namespace noggit
{
  namespace mpq
  {
    class file;
  }
}

namespace freetype
{
  struct GlyphData
  {
    opengl::call_list* _call_list;
    opengl::texture* _texture;
    int _width;

    inline void render() const
    {
      _call_list->render();
    }
    inline const int& width() const
    {
      return _width;
    }
  };

  class font_data
  {
  public:
    unsigned int h;

    font_data()
    : _mpqFile( NULL )
    {
    }
    ~font_data();

    void init( const std::string& fname, unsigned int h, bool fromMPQ );
    int width( const std::string& text ) const;
    void print( float x, float y, const std::string& text, float colorR = 1.0f, float colorG = 1.0f, float colorB = 1.0f ) const;
    void shprint( float x, float y, const std::string& text, float colorR = 1.0f, float colorG = 1.0f, float colorB = 1.0f ) const;

  private:
    typedef FT_ULong CharacterCode;
    //! \todo Use some hash map.
    typedef std::map<CharacterCode, GlyphData> GlyphListType;

    mutable GlyphListType _cachedGlyphs;

    FT_Face _face;
    FT_Library _library;

    noggit::mpq::file* _mpqFile;

    void createGlyph( CharacterCode charCode ) const;
    const GlyphData& getGlyphData( CharacterCode charCode ) const;
  };
}

#endif
