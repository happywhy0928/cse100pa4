movie = library('movie', sources: ['Movie.hpp'])
inc = include_directories('.')

movie_dep = declare_dependency(include_directories: inc, link_with: movie)


actor_Node = library('actor_Node', sources: ['ActorNode.hpp'], dependencies:[movie_dep])
inc = include_directories('.')

actor_Node_dep = declare_dependency(include_directories: inc, link_with:actor_Node)

actor_edge = library('actor_edge', sources: ['ActorEdge.hpp'], dependencies:[movie_dep, actor_Node_dep])
inc = include_directories('.')

actor_edge_dep = declare_dependency(include_directories: inc, link_with:actor_edge)