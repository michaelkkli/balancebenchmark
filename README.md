# BalanceBenchmark
A Monte Carlo simulation benchmark based on the Heston stochastic volatility model.

## Developer Notes

First time use:
```bash
balancebenchmark$ autoreconf --install && mkdir build && cd build
```

Subsequent builds:
```bash
build$ (cd .. && autoreconf) && ../configure CFLAGS="-g" && make check
```

## References
- **Peter J. Acklam**. http://home.online.no/~pjacklam/notes/invnorm/
- **Leif B. G. Andersen**. Efficient Simulation of the Heston Stochastic Volatility Model. _Social Science Research Network_, **2007**. http://dx.doi.org/10.2139/ssrn.946405
- **Darrell Duffie, Jun Pan and Kenneth Singleton**. Transform Analysis and Asset Pricing for Affine Jump-Diffusions. _Econometrica_, **68**(6):1343-1376, **2000**. http://www.jstor.org/stable/3003992 
- **Walter Gander and Walter Gautschi**. Adaptive Quadrature--Revisited. _BIT Numerical Mathematics_, 84-101, **2000**. http://dx.doi.org/10.1023/A:1022318402393
- **Steven L. Heston**. A Closed-Form Solution for Options with Stochastic Volatility with Applications to Bond and Currency Options. _The Review of Financial Studies_, **6**(2):327-343, **1993**. http://www.jstor.org/stable/2962057
- **Peter Lankford, Lars Ericson, and Andrey Nikolaev**. End-User Driven Technology Benchmarks
Based on Market-Risk Workloads. _2012 SC Companion: High Performance Computing, Networking Storage and Analysis_, 1171-1175, **2012**. http://dx.doi.org/10.1109/SC.Companion.2012.141
- **Roger Lord and Christian Kahl**. Complex Logarithms in Heston-Like Models. _Mathematical Finance_, **20**(4):671-694, **2010**. http://dx.doi.org/10.1111/j.1467-9965.2010.00416.x
- **Kenichi Miura**. Prospects for Monte Carlo Methods in Million Processor-core Era and Beyond. _International Advanced Research Workshop on High Performance Computing_, **2014**. http://www.hpcc.unical.it/hpc2014/pdfs/miura.pdf
