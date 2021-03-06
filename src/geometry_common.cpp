#include "geometry_vector.h"

#include <cpp11/doubles.hpp>
#include <cpp11/strings.hpp>
#include <cpp11/matrix.hpp>
#include <cpp11/logicals.hpp>
#include <cpp11/integers.hpp>
#include <cpp11/list_of.hpp>
#include <cpp11/external_pointer.hpp>

[[cpp11::register]]
cpp11::writable::strings geometry_primitive_type(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  switch (geometries->geometry_type()) {
  case CIRCLE: return {"circle"};
  case DIRECTION: return {"direction"};
  case ISOCUBE: return {"iso_cube"};
  case ISORECT: return {"iso_rect"};
  case LINE: return {"line"};
  case PLANE: return {"plane"};
  case POINT: return {"point"};
  case RAY: return {"ray"};
  case SEGMENT: return {"segment"};
  case SPHERE: return {"sphere"};
  case TETRAHEDRON: return {"tetrahedron"};
  case TRIANGLE: return {"triangle"};
  case VECTOR: return {"vector"};
  case WPOINT: return {"point_w"};
  case VIRTUAL: return {"virtual"};
  }
  return {"unknown"};
}

[[cpp11::register]]
int geometry_length(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    return 0;
  }
  return geometries->size();
}

[[cpp11::register]]
int geometry_dimension(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    return 0;
  }
  return geometries->dimensions();
}

[[cpp11::register]]
cpp11::writable::strings geometry_definition_names(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->def_names();
}

[[cpp11::register]]
exact_numeric_p geometry_definition(geometry_vector_base_p geometries, int which, cpp11::integers element) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  std::vector<Exact_number> res = geometries->definition(which, element);
  exact_numeric* vec(new exact_numeric(res));
  return {vec};
}

[[cpp11::register]]
geometry_vector_base_p geometry_vertex(geometry_vector_base_p geometries, cpp11::integers which) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->vertex(which);
}

[[cpp11::register]]
cpp11::writable::integers geometry_cardinality(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  cpp11::writable::integers result;
  result.reserve(geometries->size());
  for (size_t i = 0; i < geometries->size(); ++i) {
    result.push_back(geometries->cardinality(i));
  }
  return result;
}

[[cpp11::register]]
geometry_vector_base_p geometry_subset(geometry_vector_base_p geometries, cpp11::integers index) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->subset(index);
}

[[cpp11::register]]
geometry_vector_base_p geometry_copy(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->copy();
}

[[cpp11::register]]
geometry_vector_base_p geometry_assign(geometry_vector_base_p geometries, cpp11::integers index, geometry_vector_base_p value) {
  if (geometries.get() == nullptr || value.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->assign(index, *value);
}

[[cpp11::register]]
geometry_vector_base_p geometry_combine(geometry_vector_base_p geometries, cpp11::list_of< geometry_vector_base_p > extra) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->combine(extra);
}

[[cpp11::register]]
geometry_vector_base_p geometry_unique(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->unique();
}

[[cpp11::register]]
cpp11::writable::logicals geometry_duplicated(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->duplicated();
}

[[cpp11::register]]
cpp11::writable::integers geometry_any_duplicated(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return {geometries->any_duplicated() + 1};
}

[[cpp11::register]]
cpp11::writable::integers geometry_match(geometry_vector_base_p geometries, geometry_vector_base_p table) {
  if (geometries.get() == nullptr || table.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->match(*table);
}

[[cpp11::register]]
cpp11::writable::logicals geometry_is_na(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->is_na();
}

[[cpp11::register]]
bool geometry_any_na(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->any_na();
}

[[cpp11::register]]
cpp11::writable::doubles_matrix geometry_to_matrix(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->as_numeric();
}

[[cpp11::register]]
cpp11::writable::strings geometry_format(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    return {">>>Data structure pointer cleared from memory<<<"};
  }
  return geometries->format();
}

[[cpp11::register]]
cpp11::writable::logicals geometry_is_equal(geometry_vector_base_p geometries1,
                                            geometry_vector_base_p geometries2) {
  if (geometries1.get() == nullptr || geometries2.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return (*geometries1) == (*geometries2);
}

[[cpp11::register]]
geometry_vector_base_p geometry_transform(geometry_vector_base_p geometries, transform_vector_base_p affine) {
  if (geometries.get() == nullptr || affine.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->transform(*affine);
}

[[cpp11::register]]
bbox_vector_base_p geometry_bbox(geometry_vector_base_p geometries) {
  if (geometries.get() == nullptr) {
    cpp11::stop("Data structure pointer cleared from memory");
  }
  return geometries->bbox();
}
