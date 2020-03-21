# see https://github.com/coin-or/Gravity/blob/master/cmake/FindSDPA.cmake
# (jwd) - I've tweaked to work with bionic's libsdpa-dev aptitude package
if(UNIX)
   find_path(SDPA_INCLUDE_DIR sdpa_call.h	HINTS "/usr/include/")
   find_path(Mumps_INCLUDE_DIR dmumps_c.h HINTS "/usr/include/")
   find_library(SDPA_LIBRARY libsdpa.a HINTS "/usr/lib")
   find_library(Mumps_LIBRARY libdmumps_seq.a	HINTS "/usr/lib/x86_64-linux-gnu/" )
   find_library(Mumps_LIBRARY1 libmumps_common_seq.a HINTS "/usr/lib/x86_64-linux-gnu/" )
   find_library(Mumps_LIBRARY2 libpord_seq.a HINTS  "/usr/lib/x86_64-linux-gnu/")
   find_library(Mumps_LIBRARY3 libmpiseq_seq.a	HINTS "/usr/lib/x86_64-linux-gnu/")
   find_library(Mumps_LIBRARY4 libesmumps.a HINTS "/usr/lib/x86_64-linux-gnu/")
   find_library(BLAS_LIBRARY libopenblas.a	HINTS "/usr/lib/x86_64-linux-gnu/")
   find_library(LAPACK_LIBRARY liblapack.a	HINTS "/usr/lib/x86_64-linux-gnu/")
   find_library(FORTRAN_LIBRARY libgfortran.so.4 HINTS "/usr/lib/x86_64-linux-gnu/")
   find_library(FORTRAN_LIBRARY1 libquadmath.so.0	HINTS "/usr/lib/x86_64-linux-gnu/")
   find_library(SCOTCH_LIBRARY libscotch.a	HINTS "/usr/lib/x86_64-linux-gnu/")
   find_library(SCOTCH_LIBRARY1 libscotcherr.a	HINTS "/usr/lib/x86_64-linux-gnu/")
else()
   message(ERROR "OS NOT SUPPORTED; use UNIX-based!")
endif(UNIX)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDPA DEFAULT_MSG SDPA_LIBRARY SDPA_INCLUDE_DIR)

if(SDPA_FOUND)
   message("—- Found SDPA under ${SDPA_INCLUDE_DIR}")
   set(SDPA_INCLUDE_DIRS ${SDPA_INCLUDE_DIR}  ${Mumps_INCLUDE_DIR})
   set(SDPA_LIBRARIES ${SDPA_LIBRARY} ${Mumps_LIBRARY} ${Mumps_LIBRARY1}
      ${Mumps_LIBRARY2} ${Mumps_LIBRARY3} ${Mumps_LIBRARY4} ${BLAS_LIBRARY} ${LAPACK_LIBRARY} "pthread"
      ${FORTRAN_LIBRARY} ${FORTRAN_LIBRARY1} ${SCOTCH_LIBRARY} ${SCOTCH_LIBRARY1})
   message("—- Set SDPA lib  ${SDPA_LIBRARY}")
   if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
      set(SDPA_LIBRARIES "${SDPA_LIBRARIES};m;pthread")
   endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif(SDPA_FOUND)

mark_as_advanced(SDPA_LIBRARY SDPA_INCLUDE_DIR)
