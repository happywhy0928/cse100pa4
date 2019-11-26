
subdir('ActorAndMovie')
subdir('ActorGraph')

pathfinder_exe = executable('pathfinder.cpp.executable', 
sources:['pathfinder.cpp'],
dependencies : [actorGraph_dep, movie_dep, actor_Node_dep, actor_edge_dep, cxxopts_dep],
install: true)

linkpredictor_exe = executable('linkpredictor.cpp.executable', 
sources:['linkpredictor.cpp'],
dependencies : [actorGraph_dep, movie_dep, actor_Node_dep, actor_edge_dep, cxxopts_dep],
install: true)



