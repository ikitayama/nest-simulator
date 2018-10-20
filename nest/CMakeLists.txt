# nest/CMakeLists.txt
#
# This file is part of NEST.
#
# Copyright (C) 2004 The NEST Initiative
#
# NEST is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# NEST is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NEST.  If not, see <http://www.gnu.org/licenses/>.

set( nest_sources
    )

add_executable( nest main.cpp ${nest_sources} )
if ( static-libraries )
    set_target_properties( nest
        PROPERTIES
        LINK_SEARCH_END_STATIC TRUE
        LINK_SEARCH_START_STATIC TRUE
        )
endif ()

if ( NOT APPLE )
    set_target_properties( nest
        PROPERTIES
        LINK_FLAGS "-Wl,--no-as-needed"
        )
endif ()

add_library( nest_lib ${nest_sources} )

if ( NOT APPLE )
    set_target_properties( nest_lib
        PROPERTIES
        OUTPUT_NAME nest
        LINK_FLAGS "-Wl,--no-as-needed"
        )
else ()
    set_target_properties( nest_lib
        PROPERTIES
        OUTPUT_NAME nest
        )
endif ()

target_link_libraries( nest
    nestutil nestkernel random sli_lib sli_readline
    ${SLI_MODULES} ${EXTERNAL_MODULE_LIBRARIES} )

target_link_libraries( nest_lib
    nestutil nestkernel random sli_lib ${SLI_MODULES} ${EXTERNAL_MODULE_LIBRARIES} )

target_include_directories( nest PRIVATE
    ${PROJECT_BINARY_DIR}/nest
    ${PROJECT_BINARY_DIR}/libnestutil
    ${PROJECT_SOURCE_DIR}/libnestutil
    ${PROJECT_SOURCE_DIR}/librandom
    ${PROJECT_SOURCE_DIR}/sli
    ${PROJECT_SOURCE_DIR}/nestkernel
    )

install( TARGETS nest
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

install( FILES ${install_headers}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nest)
