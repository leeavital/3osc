# - Build script for 3osc
# author: Lee Avital

cmake_minimum_required(VERSION 2.8)


set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "." )



include( "cmake/FindPortaudio" )



if( PORTAUDIO_FOUND )
  set( LIBS ${LIBS} ${PORTAUDIO_LIBRARIES} )
endif( PORTAUDIO_FOUND )


set( LIBS ${LIBS} "pthread" )


add_executable( 3osc main.c ftable.c 3osc.c)
target_link_libraries( 3osc ${LIBS} )
