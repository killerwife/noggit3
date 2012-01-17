# FindStormLib.cmake is part of Noggit3, licensed via GNU General Publiicense (version 3).
# Bernd Lörwald <bloerwald+noggit@googlemail.com>
# Stephan Biegel <project.modcraft@googlemail.com>

#find STORMLIB
# STORMLIB_LIBRARIES, the name of the library to link against
# STORMLIB_FOUND, if false, do not try to link
# STORMLIB_INCLUDES,

find_path(STORMLIB_INCLUDE_DIR StormLib.h StormPort.h )
find_path(STORMLIB_LIBRARY_DIR StormLibRAD.lib )
find_library(STORMLIB_LIBRARY StormLib)
set(STORMLIB_LIBRARIES ${STORMLIB_LIBRARY})
if( WIN32 )
  find_library(STORMLIB_LIBRARYRAD StormLibRAD.lib)
  find_library(STORMLIB_LIBRARYDAD StormLibDAD.lib)
  set(STORMLIB_LIBRARIES ${STORMLIB_LIBRARIES} ${STORMLIB_LIBRARYRAD} ${STORMLIB_LIBRARYDAD})
endif( WIN32 )

if(STORMLIB_INCLUDE_DIR AND STORMLIB_LIBRARY)
    SET(STORMLIB_FOUND TRUE)
endif(STORMLIB_INCLUDE_DIR AND STORMLIB_LIBRARY)

set(STORMLIB_INCLUDES ${STORMLIB_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(StormLib DEFAULT_MSG STORMLIB_LIBRARY STORMLIB_INCLUDE_DIR)

mark_as_advanced(STORMLIB_INCLUDE_DIR STORMLIB_LIBRARY STORMLIB_LIBRARYRAD STORMLIB_LIBRARYDAD)
