# Lenstra-Elliptic-Curve-Factorization
Got bored one night and dived a bit too deep into elliptic curves.

Anyways, this is an attempt at Lenstra's Elliptic Curve Factorization Algorithm after reading 6.3 of Stein's Elementary Number Theory Book along with some Googling.

#### NOTE: I'm not sure why I chose C++ to implement this in. It is very impractical because they only have 64-bit integers (and I guess 128-bit integers as well) and Lenstra's Factorization works best for numbers on the order of $`10^{30}`$. I should reimplement in Python or use some elliptic curve software like Sage.
