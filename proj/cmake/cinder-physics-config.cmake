if ( NOT TARGET Cinder-Physics )
	get_filename_component( CINDER_PHYSICS_PATH "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE )

	set( CINDER_PHYSICS_INCLUDES
		${CINDER_PHYSICS_PATH}/src
	)
	set( CINDER_PHYSICS_SOURCES
		${CINDER_PHYSICS_PATH}/src/mndl/physics/VerletPhysics.cpp
	)

	add_library( Cinder-Physics ${CINDER_PHYSICS_SOURCES} )

	target_compile_options( Cinder-Physics PUBLIC "-std=c++11" )

	target_include_directories( Cinder-Physics PUBLIC "${CINDER_PHYSICS_INCLUDES}" )
	target_include_directories( Cinder-Physics SYSTEM BEFORE PUBLIC "${CINDER_PATH}/include" )
endif()
