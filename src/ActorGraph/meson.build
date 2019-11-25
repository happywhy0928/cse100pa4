actorGraph = library('actorGraph', sources: ['ActorGraph.cpp','ActorGraph.hpp'], dependencies: [actor_edge_dep,actor_Node_dep, movie_dep])
inc = include_directories('.')

actorGraph_dep = declare_dependency(include_directories: inc, link_with: actorGraph)