# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/home/dorson/Documents/github/Doe/src/doe_simulation;/home/dorson/Documents/github/Doe/src/doe_simulation/build/doe_simulation")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENTS_ALL "")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "doe_simulation built using CMake")
set(CPACK_GENERATOR "DEB")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALL_CMAKE_PROJECTS "/home/dorson/Documents/github/Doe/src/doe_simulation/build/doe_simulation;doe_simulation;ALL;/")
set(CPACK_INSTALL_PREFIX "/home/dorson/Documents/github/Doe/src/doe_simulation/install/doe_simulation")
set(CPACK_MODULE_PATH "/opt/ros/jazzy/share/fastrtps_cmake_module/cmake/Modules;/opt/ros/jazzy/opt/gz_cmake_vendor/share/cmake/gz-cmake3/cmake3")
set(CPACK_NSIS_DISPLAY_NAME "doe_simulation ..")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "doe_simulation ..")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "/usr/bin/objcopy")
set(CPACK_OBJDUMP_EXECUTABLE "/usr/bin/objdump")
set(CPACK_OUTPUT_CONFIG_FILE "/home/dorson/Documents/github/Doe/src/doe_simulation/build/doe_simulation/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "doe_simulation built using CMake")
set(CPACK_PACKAGE_FILE_NAME "doe_simulation-..-Linux")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "doe_simulation ..")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "doe_simulation ..")
set(CPACK_PACKAGE_NAME "doe_simulation")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "..")
set(CPACK_PACKAGE_VERSION_MAJOR "")
set(CPACK_PACKAGE_VERSION_MINOR "")
set(CPACK_PACKAGE_VERSION_PATCH "")
set(CPACK_PROJECT_CONFIG_FILE "/home/dorson/Documents/github/Doe/src/doe_simulation/build/doe_simulation/cpack_options.cmake")
set(CPACK_READELF_EXECUTABLE "/usr/bin/readelf")
set(CPACK_RESOURCE_FILE_LICENSE "/usr/share/cmake-3.28/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "/usr/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.28/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TBZ2;ZIP")
set(CPACK_SOURCE_IGNORE_FILES "TODO;.hg/;.sw.$;/build/;.hgtags;.hgignore;appveyor.yml;.travis.yml;codecov.yml")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/dorson/Documents/github/Doe/src/doe_simulation/build/doe_simulation/CPackSourceConfig.cmake")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/dorson/Documents/github/Doe/src/doe_simulation/build/doe_simulation/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
