Generalised Hadamard Matrix finder
===========

Software to find generalised Hadamard matrices (GHM)

This is a relatively simple brute-force approach. We ensure that the first row
is completely positive (every entry is positive) and is weakly increasing. We
also ensure that the first column is completely positive. Lastly, we check
that, where the first row only consists of 1s, the second row is weakly
increasing; and the same for where the first row only consists of 2s, and then
3s.


For more details on SGHMs, see A Generalization of Hadamard Matrices, Saieed Akbari and Asghar Bahmani, Electronic Notes in Discrete Mathematics, 01/2014.
