This repo contains the source code of SPF graph's algorithms program.

Install
===================

 1. The langage code used is C++. Appropriate compiler MUST be installed on your environment. 
 2. The utily `make` MUST be installed on your environment. 
 3. Move to the directory "src".
 4. Execute the following commands :

`[~ src]$ make clean`
 
`[~ src]$ make`

First command cleans object and binary files.

Execution
===================

 1. Move to the directory "bin".
 2. Execute the program "main" as per below:

`[~ bin]$ ./main`

User Guide
===================

Three algorithms are implemented : 

 1. Ford-Bellman with a complexity of O(N2), efficient over hollow graphs
 2. Dijkstra with a complexity de O(N2), efficient over completes graphs
 3. Dijkstra by heap with a complexity of O(NlogN)

When executed, the program launchs an interactive menu:
 1. Choose the algorithm between 3
 2. Choose the graph to process the algorithm over
 
Graph representation files can be generated manually.
Each line is an edge as per below : 

`TOP1 TOP2 WEIGHT`

The `WEIGHT` is the cost going through this edge.

The display of a graph is based on lists of adjacences.

The first columnrepresents `TOPS`. The second column represents its `SUCCESSORS`.

Acknowledgements
===================

Thanks to Jeremy Soulary for the codev.
Thanks to Rodolph Giroudeau for his teaching.
