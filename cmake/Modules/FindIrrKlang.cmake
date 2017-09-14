#
# - Try to find irrKlang
# Once done this will define
#
#  IRRKLANG_FOUND - system has irrKlang
#  IRRKLANG_INCLUDE_DIRS - the irrKlang include directory
#  IRRKLANG_LIBRARIES - Link these to use irrKlang
#  IRRKLANG_DEFINITIONS - Compiler switches required for using irrKlang
#


if (IRRKLANG_LIBRARIES AND IRRKLANG_INCLUDE_DIRS)
   set(IRRKLANG_FOUND TRUE)
else (IRRKLANG_LIBRARIES AND IRRKLANG_INCLUDE_DIRS)
     find_path(IRRKLANG_INCLUDE_DIR
		NAMES
		irrKlang.h
		PATHS
		/usr/include
		/usr/irrklang-includes
		${CMAKE_CURRENT_SOURCE_DIR}/lib/irrklang-includes
		)

     if (UNIX)
     	find_library(IRRKLANG_LIBRARY
			NAMES
			libIrrKlang.so
			PATHS
			/usr/lib
			${CMAKE_CURRENT_SOURCE_DIR}/lib/Unix
  			)
     elseif(WIN32)
	find_library(IRRKLANG_LIBRARY
			NAMES
      			irrKlang.lib
      			PATHS
			/usr/lib
      			${CMAKE_CURRENT_SOURCE_DIR}/lib/Win32
  			)

     	find_file(IRRKLANG_DLL
			NAMES
       			irrKlang.dll
      			PATHS
			/usr/lib
      			${CMAKE_CURRENT_SOURCE_DIR}/lib/Win32
  			)
	MESSAGE(STATUS "IRRKLANG_LIBRARIES = ${IRRKLANG_DLL}")
     endif()

     if (IRRKLANG_LIBRARY)
     	set(IRRKLANG_FOUND TRUE)
     endif (IRRKLANG_LIBRARY)

     set(IRRKLANG_INCLUDE_DIRS
	${IRRKLANG_INCLUDE_DIR}
	)

     set(IRRKLANG_DLL
	${IRRKLANG_DLL}
	)

     if (IRRKLANG_FOUND)
     	set(IRRKLANG_LIBRARIES
	   ${IRRKLANG_LIBRARIES}
	   ${IRRKLANG_LIBRARY}
    	   )
     endif (IRRKLANG_FOUND)

     if (IRRKLANG_INCLUDE_DIRS AND IRRKLANG_LIBRARIES)
     	set(IRRKLANG_FOUND TRUE)
     endif (IRRKLANG_INCLUDE_DIRS AND IRRKLANG_LIBRARIES)

     if (IRRKLANG_FOUND)
     	if (NOT IRRKLANG_FIND_QUIETLY)
      	   MESSAGE(STATUS "*** Found irrKlang ***")
      	   MESSAGE(STATUS "IRRKLANG_INCLUDE_DIRS = ${IRRKLANG_INCLUDE_DIRS}")
      	   MESSAGE(STATUS "IRRKLANG_LIBRARIES = ${IRRKLANG_LIBRARIES}")
	   if (WIN32)
      	      MESSAGE(STATUS "IRRKLANG_DLL = ${IRRKLANG_DLL}")
	   endif (WIN32)
    	endif (NOT IRRKLANG_FIND_QUIETLY)
     else (IRRKLANG_FOUND)
     	if (IRRKLANG_FIND_REQUIRED)
      	   message(FATAL_ERROR "/!\ Could not find irrKlang")
    	endif (IRRKLANG_FIND_REQUIRED)
     endif (IRRKLANG_FOUND)

     # show the IRRKLANG_INCLUDE_DIRS and IRRKLANG_LIBRARIES variables only in the advanced view
     mark_as_advanced(IRRKLANG_INCLUDE_DIRS IRRKLANG_LIBRARIES IRRKLANG_DLL)

endif (IRRKLANG_LIBRARIES AND IRRKLANG_INCLUDE_DIRS)
