// Copyright (C) 2022 National Center for Atmospheric Research
// SPDX-License-Identifier: Apache-2.0
//
// Tests for the C Array type

#include <aero/aero.hpp>
#include <aero/array/array.hpp>
#include <aero/array/c_array.hpp>
#include <aero/array/fortran_array.hpp>
#include <assert.h>
#include <iostream>
#include "array_helper.c"

extern "C" {
  void *test_array_create_fortran_array();
}

int main(const int argc, const char *argv[]) {

  aero::Array *a, *b;
  std::vector<Real> ra {12.5, 32.6, -132.45, 0.0};
  std::vector<Real> rb;

  a = new aero::Array(ra);
  assert(a->size() == 4);
  rb = std::vector<Real>(4);
  a->copy_out(rb);
  assert(rb[2] == -132.45);
  delete a;
  a = new aero::Array(6);
  assert(a->size() == 6);
  rb = std::vector<Real>(6);
  a->copy_out(rb);
  assert(rb[5] == 0.0);
  delete a;
  a = new aero::Array(8, 12.3);
  assert(a->size() == 8);
  rb = std::vector<Real>(8);
  a->copy_out(rb);
  assert(rb[7] == 12.3);
  delete a;
  a = new aero::Array(4);
  a->copy_in(ra);
  assert(a->size() == 4);
  rb = std::vector<Real>(4);
  a->copy_out(rb);
  assert(rb[2] == -132.45);
  rb = std::vector<Real>(8);
  rb[7] = 12.3;
  *a = rb;
  assert(a->size() == 8);
  rb[7] = 0.0;
  a->copy_out(rb);
  assert(rb[7] == 12.3);
  b = new aero::Array(*a);
  assert(a->size() == 8);
  rb[7] = 0.0;
  a->copy_out(rb);
  assert(rb[7] == 12.3);
  delete a;
  delete b;

  // fortran array
  a = new aero::FortranArray(test_array_create_fortran_array());
  assert(a->size() == 4);
  rb = std::vector<Real>(4);
  a->copy_out(rb);
  assert(rb[2] == 0.623);
  a->copy_in(ra);
  a->copy_out(rb);
  assert(rb[2] == -132.45);
  b = a->clone();
  rb[2] = 0.0;
  b->copy_out(rb);
  assert(rb[2] == -132.45);
  delete a;
  delete b;

  // c array
  a = new aero::CArray(test_array_create_c_array());
  assert(a->size() == 4);
  rb = std::vector<Real>(4);
  a->copy_out(rb);
  assert(rb[2] == 0.523);
  a->copy_in(ra);
  a->copy_out(rb);
  assert(rb[2] == -132.45);
  b = a->clone();
  rb[2] = 0.0;
  b->copy_out(rb);
  assert(rb[2] == -132.45);
  delete a;
  delete b;

  return 0;
}
