# MagDiffExactSolution

## Introduction

The magnetic diffusion problem is formed by coupling the magnetic diffusion equation and the Ohmic heating energy equation. Ohmic heating causes a severe change in the magnetic diffusion coefficient, making magnetic diffusion a highly nonlinear process. Under the condition of a step-function resistivity and a constant magnetic boundary condition, an exact solution for this nonlinear magnetic diffusion problem can be derived according to reference "http://arxiv.org/abs/2311.14950". This C-program realizes the method in the reference: it outputs a solution of $B(x,t)$ once the four input parameters $B_0$, $E_c$, $\eta_L$, and $\eta_S$ are given.

## Build

Build *main*:

```makefile
~> cd MagDiffExactSolution
~> make 
```

## Running

```sh
./main
```

## Results

The terminal outputs:

```sh
The input parameters are:
Ec = 1.000000E-01   
B0 = 2.000000E-01   
EtaS = 9.700000E-05   
EtaL = 9.700000E-03   

Results:
Bc = 1.557672E-01   
h = 2.440632E-03   

Writting curves to files...

finished.
```

The test result files **BcToh-DoubleCurves.txt** and **f-u.txt** are saved in the current directory.

## License

This software is free software distributed under the Lesser General Public License or LGPL, version 2.1 or any later versions. This software distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this program. If not, see http://www.gnu.org/licenses/.
