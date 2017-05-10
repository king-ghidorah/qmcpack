//////////////////////////////////////////////////////////////////////////////////////
// This file is distributed under the University of Illinois/NCSA Open Source License.
// See LICENSE file in top directory for details.
//
// Copyright (c) 2016 Jeongnim Kim and QMCPACK developers.
//
// File developed by:  Mark Dewing, markdewing@gmail.com, University of Illinois at Urbana-Champaign
//
// File created by: Mark Dewing, markdewing@gmail.com, University of Illinois at Urbana-Champaign
//////////////////////////////////////////////////////////////////////////////////////


#include "catch.hpp"

#include "OhmmsPETE/OhmmsMatrix.h"

#include <stdio.h>
#include <string>

using std::string;

namespace qmcplusplus
{


TEST_CASE("matrix", "[OhmmsPETE]")
{
  typedef Matrix<double> mat_t;
  mat_t A(3,3);
  mat_t B(3,3);
  mat_t C(3,3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      B(i,j) = (i+j)*2.1;
    }
  }

  // Assign to all elements
  A = 1.0;

  // Assignment.   This eventually generates a call to 'evaluate' in OhmmsVector.h
  C = A;

  // *= operator in OhmmMatrixOperators.h
  A *= 3.1;

  // iterator
  mat_t::iterator ia = A.begin();
  for (; ia != A.end(); ia++) {
    REQUIRE(*ia == Approx(3.1));
  }

  // copy constructor and copy method
  mat_t D(C);
  REQUIRE(D.rows() == 3);
  REQUIRE(D.cols() == 3);

}

}
