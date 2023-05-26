set(GLM_VERSION "0.9.9")
set(GLM_INCLUDE_DIRS "C:/Users/manht/4. Semester/VC/visual-computing-prak2/libs/glm-master")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    include("${CMAKE_CURRENT_LIST_DIR}/glmTargets.cmake")
endif()
