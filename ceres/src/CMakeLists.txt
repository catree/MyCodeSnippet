add_executable(helloworld helloworld.cpp)
target_link_libraries(helloworld ${CERES_LIBRARIES})

add_executable(helloworld_numeric_diff helloworld_numeric_diff.cpp)
target_link_libraries(helloworld_numeric_diff ${CERES_LIBRARIES})

add_executable(helloworld_analytic_diff helloworld_analytic_diff.cpp)
target_link_libraries(helloworld_analytic_diff ${CERES_LIBRARIES})

add_executable(powell powell.cpp)
target_link_libraries(powell ${CERES_LIBRARIES})

add_executable(curve_fitting curve_fitting.cpp)
target_link_libraries(curve_fitting ${CERES_LIBRARIES})

add_executable(bundle_adjuster bundle_adjuster.cpp)
target_link_libraries(bundle_adjuster ${CERES_LIBRARIES})