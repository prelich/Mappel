# Mappel-PackageConfig.cmake
#
# Mark J. Olah (mjo@cs.unm DOT edu)
# Copyright 2017
# see file: LICENCE
#
#
# Prepare Package Configuration and and Targets export files and install them in appropriate locations
#
include(CMakePackageConfigHelpers)
set(CONFIG_DIR ${CMAKE_CURRENT_BINARY_DIR}/config) #Directory for generated .cmake config file
set(EXPORT_TARGETS_NAME ${PROJECT_NAME}Targets)
set(CONFIG_NAME ${PROJECT_NAME}Config)
set(VERSION_CONFIG_FILE ${CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake)
set(CONFIG_FILE ${CONFIG_DIR}/${CONFIG_NAME}.cmake)
set(CONFIG_TEMPLATE_FILE ${CMAKE_SOURCE_DIR}/cmake/Templates/${CONFIG_NAME}.cmake.in)
set(CONFIG_INSTALL_DIR lib/cmake/${PROJECT_NAME}) #Where to install project Config.cmake and ConfigVersion.cmake files
set(SHARED_CMAKE_INSTALL_DIR share/${PROJECT_NAME}/cmake) #Where to install shared .cmake build scripts for downstream

## Generate Package Config files for downstream projects to utilize
#Generate: MexIFaceConfigVersion.cmake
write_basic_package_version_file(${VERSION_CONFIG_FILE} COMPATIBILITY SameMajorVersion)

#Generate: MexIFaceConfig.cmake
configure_package_config_file(${CONFIG_TEMPLATE_FILE} ${CONFIG_FILE} 
                              INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
                              PATH_VARS CONFIG_INSTALL_DIR SHARED_CMAKE_INSTALL_DIR)

#Install package config files
install(FILES ${CONFIG_FILE} ${VERSION_CONFIG_FILE} 
        DESTINATION ${CONFIG_INSTALL_DIR} COMPONENT Development)
#Install MexIFaceTargets exports
install(EXPORT ${EXPORT_TARGETS_NAME} 
        DESTINATION ${CONFIG_INSTALL_DIR} COMPONENT Development)

