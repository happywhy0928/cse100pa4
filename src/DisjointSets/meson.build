disjointsets = library('disjointsets', sources: ['DisjointSets.cpp','DisjointSets.hpp'], dependencies: [actor_edge_dep,actor_Node_dep, movie_dep, actorGraph_dep])
inc = include_directories('.')

disjointsets_dep = declare_dependency(include_directories: inc, link_with: disjointsets)