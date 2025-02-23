/*******************************************************************************
 Causal Dynamical Triangulations in C++ using CGAL

 Copyright © 2017 Adam Getchell
 ******************************************************************************/

/// @file Vertex_test.cpp
/// @brief Tests on points and vertices in foliated Delaunay triangulations
/// @author Adam Getchell
/// @details Tests for inserting and deleting vertices.

#include <doctest/doctest.h>

#include <numbers>

#include "Manifold.hpp"

using namespace manifolds;

static inline auto constinit const RADIUS_2 =
    2.0 * std::numbers::inv_sqrt3_v<double>;

SCENARIO("Point operations" * doctest::test_suite("vertex"))
{
  using Point = Point_t<3>;
  GIVEN("Some points.")
  {
    auto point_1 = Point(0, 0, 0);
    auto point_2 = Point(0, 0.0, 0.0);
    auto point_3 = Point(1, 1, 1);
    WHEN("They are compared.")
    {
      THEN("Similar points are equal.") { REQUIRE_EQ(point_1, point_2); }
      THEN("Dissimilar points are not equal.") { REQUIRE_NE(point_1, point_3); }
    }
  }
}

SCENARIO("Vertex operations" * doctest::test_suite("vertex"))
{
  using Causal_vertices = Causal_vertices_t<3>;
  using Manifold        = Manifold_3;
  using Point           = Point_t<3>;
  GIVEN("A foliated Delaunay triangulation.")
  {
    Causal_vertices causal_vertices;
    WHEN("A vertex is inserted.")
    {
      causal_vertices.emplace_back(Point(0, 0, 0), 1);
      Manifold const manifold(causal_vertices, 0, 1);
      THEN("The vertex is in the manifold.")
      {
        auto vertex = manifold.get_vertices();
        REQUIRE(manifold.is_vertex(vertex.front()));
      }

      THEN("The Delaunay triangulation is valid.")
      {
        REQUIRE(manifold.is_valid());
      }

      THEN("There is 1 vertex.") { REQUIRE_EQ(manifold.N0(), 1); }

      THEN("There are no edges.") { REQUIRE_EQ(manifold.N1(), 0); }

      THEN("A 1 vertex manifold has dimension 0.")
      {
        REQUIRE_EQ(manifold.dimensionality(), 0);
      }

      THEN("The vertex is valid.")
      {
        fmt::print("When a causal vertex is inserted, the vertices are:\n");
        manifold.print_vertices();
        CHECK(manifold.get_triangulation().check_all_vertices());
      }
    }

    AND_WHEN("Two vertices are inserted.")
    {
      causal_vertices.emplace_back(Point(0, 0, 0), 1);
      causal_vertices.emplace_back(Point(1, 0, 0), 2);
      Manifold const manifold(causal_vertices, 0, 1);

      THEN("The vertices are in the manifold.")
      {
        auto vertex = manifold.get_vertices();
        REQUIRE(manifold.is_vertex(vertex.front()));
        REQUIRE(manifold.is_vertex(vertex.back()));
      }

      THEN("The Delaunay triangulation is valid.")
      {
        REQUIRE(manifold.is_valid());
      }

      THEN("There are 2 vertices.") { REQUIRE_EQ(manifold.N0(), 2); }

      THEN("There is 1 edge.") { REQUIRE_EQ(manifold.N1(), 1); }

      THEN("There are no faces.") { REQUIRE_EQ(manifold.N2(), 0); }

      THEN("A 2 vertex manifold has dimension 1.")
      {
        REQUIRE_EQ(manifold.dimensionality(), 1);
      }

      THEN("The vertices are valid.")
      {
        fmt::print("When 2 causal vertices are inserted, the vertices are:\n");
        manifold.print_vertices();
        CHECK(manifold.get_triangulation().check_all_vertices());
      }
    }

    AND_WHEN("Three vertices are inserted.")
    {
      causal_vertices.emplace_back(Point(0, 0, 0), 1);
      causal_vertices.emplace_back(Point(1, 0, 0), 2);
      causal_vertices.emplace_back(Point(0, 1, 0), 2);
      Manifold manifold(causal_vertices, 0, 1);

      THEN("The vertices are in the manifold.")
      {
        auto vertices = manifold.get_vertices();
        auto require  = [&manifold](auto& vertex) {
          REQUIRE(manifold.is_vertex(vertex));
        };
        std::for_each(vertices.begin(), vertices.end(), require);
      }

      THEN("The Delaunay triangulation is valid.")
      {
        REQUIRE(manifold.is_valid());
      }

      THEN("There are 3 vertices.") { REQUIRE_EQ(manifold.N0(), 3); }

      THEN("There are 3 edges.") { REQUIRE_EQ(manifold.N1(), 3); }

      THEN("There is 1 face.") { REQUIRE_EQ(manifold.N2(), 1); }

      THEN("There are no simplices.") { REQUIRE_EQ(manifold.N3(), 0); }

      THEN("A 3 vertex manifold has dimension 2.")
      {
        REQUIRE_EQ(manifold.dimensionality(), 2);
      }

      THEN("The vertices are valid.")
      {
        fmt::print("When 3 causal vertices are inserted, the vertices are:\n");
        manifold.print_vertices();
        CHECK(manifold.get_triangulation().check_all_vertices());
      }
    }

    AND_WHEN("Four vertices are inserted.")
    {
      causal_vertices.emplace_back(Point(0, 0, 0), 1);
      causal_vertices.emplace_back(Point(1, 0, 0), 2);
      causal_vertices.emplace_back(Point(0, 1, 0), 2);
      causal_vertices.emplace_back(Point(0, 0, 1), 2);
      Manifold manifold(causal_vertices, 0, 1);

      THEN("The vertices are in the manifold.")
      {
        auto vertices = manifold.get_vertices();
        auto require  = [&manifold](auto& vertex) {
          REQUIRE(manifold.is_vertex(vertex));
        };
        std::for_each(vertices.begin(), vertices.end(), require);
      }

      THEN("The Delaunay triangulation is valid.")
      {
        REQUIRE(manifold.is_valid());
      }

      THEN("There are 4 vertices.") { REQUIRE_EQ(manifold.N0(), 4); }

      THEN("There are 6 edges.") { REQUIRE_EQ(manifold.N1(), 6); }

      THEN("There are 4 faces.") { REQUIRE_EQ(manifold.N2(), 4); }

      THEN("There is a simplex.") { REQUIRE_EQ(manifold.N3(), 1); }

      THEN("A 4 vertex manifold has dimension 3.")
      {
        REQUIRE_EQ(manifold.dimensionality(), 3);
      }

      THEN("The vertices are valid.")
      {
        fmt::print(
            "When 4 causal vertices are inserted, there is a simplex:\n");
        manifold.print_cells();
        CHECK(manifold.get_triangulation().check_all_vertices());
      }
    }

    AND_WHEN("Five vertices are inserted.")
    {
      causal_vertices.emplace_back(Point(0, 0, 0), 1);
      causal_vertices.emplace_back(Point(1, 0, 0), 2);
      causal_vertices.emplace_back(Point(0, 1, 0), 2);
      causal_vertices.emplace_back(Point(0, 0, 1), 2);
      causal_vertices.emplace_back(Point(RADIUS_2, RADIUS_2, RADIUS_2), 3);
      Manifold manifold(causal_vertices, 0, 1);

      THEN("The vertices are in the manifold.")
      {
        auto vertices = manifold.get_vertices();
        auto require  = [&manifold](auto& vertex_candidate) {
          REQUIRE(manifold.is_vertex(vertex_candidate));
        };
        std::for_each(vertices.begin(), vertices.end(), require);
      }

      THEN("The Delaunay triangulation is valid.")
      {
        REQUIRE(manifold.is_valid());
      }

      THEN("There are 5 vertices.") { REQUIRE_EQ(manifold.N0(), 5); }

      THEN("There are 9 edges.") { REQUIRE_EQ(manifold.N1(), 9); }

      THEN("There are 7 faces.") { REQUIRE_EQ(manifold.N2(), 7); }

      THEN("There are 2 simplexes.") { REQUIRE_EQ(manifold.N3(), 2); }

      THEN("A 5 vertex manifold still has dimension 3.")
      {
        REQUIRE_EQ(manifold.dimensionality(), 3);
      }

      THEN("The vertices are valid.")
      {
        fmt::print(
            "When 5 causal vertices are inserted, there are 2 simplices:\n");
        manifold.print_cells();
        CHECK(manifold.get_triangulation().check_all_vertices());
      }
    }
  }
}
