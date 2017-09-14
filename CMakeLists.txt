cmake_minimum_required	(VERSION 3.6)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 42)

set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message(STATUS "*** Building Indie Studio version ${VERSION_STRING} // Salty Queens' Bomberman! ***")

project			(indie_studio)

set			(IRRLICHT Irrlicht)
set 			(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

set			(SRCS           ACharacter.cpp
				  	AI.cpp
				  	Player.cpp
				  	main.cpp
				  	Configuration.cpp
					LevelFactory.cpp
					SaveInformation.cpp
					ExtensionsValidator.cpp
					ColorFactory.cpp
				  	Map.cpp
				  	OptionsManager.cpp
				  	Player.cpp
					IrrlichtEnvFinder.cpp
				  	SizeTConverter.cpp
					MyDirectory.cpp
					Game.cpp
					GameParameters.cpp
				  	SoundManager.cpp
				  	Settings.cpp
					HighScores.cpp
					MultipleEventReceiver.cpp
					Intro.cpp)

set			(SRCS_BOX	ABox.cpp
					Bomb.cpp
					Empty.cpp
					Explosion.cpp)

set			(SRCS_LOADERS	RessourcesLoader.cpp
					MonitoredLoader.cpp
					RessourcesMenuLoader.cpp
					AudioLoader.cpp
					ImagesLoader.cpp
					MeshesLoader.cpp)

set			(SRCS_GUI	GuiView.cpp
					OptionsViewEventReceiver.cpp
					GameParametersViewEventReceiver.cpp
					ViewManager.cpp
					HelpViewEventReceiver.cpp
					ScoresViewEventReceiver.cpp
					SavesViewEventReceiver.cpp
					MainViewEventReceiver.cpp
					SGuiElem.cpp
					ViewsInstantiator.cpp)

set			(SRCS_BOX_BONUS	ABonus.cpp
					ExtraLife.cpp
					ImproveBomb.cpp
					Legacy.cpp
					SimBomb.cpp
					UpRange.cpp)

set			(SRCS_BOX_BLOCK	Breakable.cpp
					Unbreakable.cpp)

PREPEND(RELEASE_SRCS "srcs" ${SRCS})
PREPEND(RELEASE_SRCS_BOX "srcs/box" ${SRCS_BOX})
PREPEND(RELEASE_SRCS_BOX_BONUS "srcs/box/bonus" ${SRCS_BOX_BONUS})
PREPEND(RELEASE_SRCS_BOX_BLOCK "srcs/box/block" ${SRCS_BOX_BLOCK})
PREPEND(RELEASE_SRCS_GUI "srcs/gui" ${SRCS_GUI})
PREPEND(RELEASE_SRCS_LOADERS "srcs/loaders" ${SRCS_LOADERS})

add_executable		(indie_studio ${RELEASE_SRCS} ${RELEASE_SRCS_BOX} ${RELEASE_SRCS_BOX_BONUS} ${RELEASE_SRCS_BOX_BLOCK} ${RELEASE_SRCS_GUI} ${RELEASE_SRCS_LOADERS})

include_directories	(includes)
include_directories	(includes/gui)
include_directories	(includes/interfaces)
include_directories	(includes/loaders)
include_directories	(includes/exceptions)
include_directories	(includes/box)
include_directories	(includes/box/bonus)
include_directories	(includes/box/block)

# Included stuff
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Installation

if(WIN32)
	set(SHAREDIR ".")
	set(BINDIR "bin")
	set(CMAKE_CXX_FLAGS "-EHsc")
elseif(UNIX) # Linux, BSD etc
	set(SHAREDIR ".")
	set(BINDIR "bin")
	set(CMAKE_CXX_FLAGS "-W -Wextra -Werror")
	set(IRRLICHT_DEPENDENCIES Irrlicht IrrKlang X11 Xxf86vm pthread GL)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/lib/irrlicht-includes
	        DESTINATION /usr/include
		FILE_PERMISSIONS WORLD_READ WORLD_WRITE
		)
	install(FILES ${CMAKE_SOURCE_DIR}/lib/Unix/libIrrlicht.a
		DESTINATION /usr/lib
		)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/lib/irrklang-includes
		DESTINATION /usr/include
		FILE_PERMISSIONS WORLD_READ WORLD_WRITE
		)
	install(FILES ${CMAKE_SOURCE_DIR}/lib/Unix/libIrrKlang.so
		DESTINATION /usr/lib
		)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/indie_config
		DESTINATION /usr/bin
		FILE_PERMISSIONS WORLD_READ WORLD_WRITE
		)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/indie_ressources
		DESTINATION /usr/bin
		FILE_PERMISSIONS WORLD_READ WORLD_WRITE
		)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/indie_persistent_data
		DESTINATION /usr/bin
		FILE_PERMISSIONS WORLD_READ WORLD_WRITE
		)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/indie_credits
		DESTINATION /usr/bin
		FILE_PERMISSIONS WORLD_READ WORLD_WRITE
		)
	install(FILES ${CMAKE_SOURCE_DIR}/indie_studio
		DESTINATION /usr/bin/
		PERMISSIONS WORLD_EXECUTE
		)
	install(FILES ${CMAKE_SOURCE_DIR}/indie_studio
		DESTINATION /usr/local/bin/
		PERMISSIONS WORLD_EXECUTE
		)
endif()

# This is done here so that relative search paths are more reasonable
find_package(Irrlicht)
find_package(IrrKlang)

if(IRRLICHT_FOUND AND IRRKLANG_FOUND)
	message(STATUS "*** Irrlicht && IrrKlang found! ***")
	
	if(WIN32)
		include_directories(${IRRLICHT_INCLUDE_DIR})
		target_link_libraries(indie_studio
					${IRRLICHT_DEPENDENCIES}
					${IRRLICHT_LIBRARY}
					)
		file(COPY ${IRRLICHT_DLL} DESTINATION "${CMAKE_SOURCE_DIR}/bin")
		file(COPY ${IRRLICHT_LIBRARY} DESTINATION "${CMAKE_SOURCE_DIR}/bin")	
		file(COPY ${IRRKLANG_DLL} DESTINATION "${CMAKE_SOURCE_DIR}/bin")
		file(COPY ${IRRKLANG_LIBRARIES} DESTINATION "${CMAKE_SOURCE_DIR}/bin")
	else()
		include_directories(${IRRLICHT_INCLUDE_DIR} ${IRRKLANG_INCLUDE_DIRS})
		target_link_libraries(indie_studio
					${IRRLICHT_DEPENDENCIES}
					${IRRLICHT_LIBRARY}
					${IRRKLANG_LIBRARIES}
					)
	endif()

	set_property		(TARGET indie_studio PROPERTY CXX_STANDARD 11)
	message(STATUS "*** Successfully generated Salty Queens' Bomberman project! ***")
else()
	message(WARNING "*** Irrlicht and/or IrrKlang not found, build failed! ***")
endif()
