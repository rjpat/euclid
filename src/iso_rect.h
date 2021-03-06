#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"
#include "intersection.h"
#include "distance.h"

class iso_rect : public geometry_vector<Iso_rectangle, 2> {
public:
  using geometry_vector::geometry_vector;
  ~iso_rect() = default;

  Primitive geometry_type() const { return ISORECT; }

  size_t cardinality(size_t i) const { return 4; }
  size_t long_length() const { return size() * 4; }

  cpp11::writable::strings def_names() const {
    return {"x", "y"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].vertex(element).x();
    case 1: return _storage[i].vertex(element).y();
    }
    return _storage[i].vertex(0).x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].vertex(j).x().exact()),
      CGAL::to_double(_storage[i].vertex(j).y().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISORECT: return intersection_impl(_storage, get_vector_of_geo<Iso_rectangle>(other));
    case LINE: return intersection_impl(_storage, get_vector_of_geo<Line_2>(other));
    case POINT: return intersection_impl(_storage, get_vector_of_geo<Point_2>(other));
    case RAY: return intersection_impl(_storage, get_vector_of_geo<Ray_2>(other));
    case SEGMENT: return intersection_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return intersection_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case CIRCLE: return do_intersect_impl(get_vector_of_geo<Circle_2>(other), _storage);
    case ISORECT: return do_intersect_impl(_storage, get_vector_of_geo<Iso_rectangle>(other));
    case LINE: return do_intersect_impl(_storage, get_vector_of_geo<Line_2>(other));
    case POINT: return do_intersect_impl(_storage, get_vector_of_geo<Point_2>(other));
    case RAY: return do_intersect_impl(_storage, get_vector_of_geo<Ray_2>(other));
    case SEGMENT: return do_intersect_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return do_intersect_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: return unknown_intersect_impl(std::max(size(), other.size()));
    }
  }

  std::vector<Exact_number> squared_distance(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    return unknown_squared_distance_impl(std::max(size(), other.size()));
  }

  cpp11::writable::doubles_matrix distance_matrix(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    return unknown_distance_matrix_impl(size(), other.size());
  }
};

typedef cpp11::external_pointer<iso_rect> iso_rect_p;
