# MagneticDiffusion1D

## Introduction

The magnetic diffusion problems is formed by coupling the magnetic diffusion equation and the Ohmic heating energy equation. Ohmic heating causes a severe change in the magnetic diffusion coefficient, making magnetic diffusion a highly nonlinear process. We take 1D as an example and provide a numerical algorithm for this problem under the condition of a step-function resistivity.

## Build

Build *main*:

```makefile
~> cd MagneticDiffusion1D
~> make 
```

## Running

```sh
for example:
./main
```

## Results

The terminal outputs:

```sh
The input parameters are：
Ec = 1.000000E-01   
B0 = 2.000000E-01   
EtaS = 9.700000E-05   
EtaL = 9.700000E-03   

Results：
Bc = 1.557672E-01   
h = 2.440632E-03   

Writting curves to files...

finished.
```

The test result files **BcToh-DoubleCurves.txt** and **f-u.txt** are saved in the current directory.

## License

This software is free software distributed under the Lesser General Public License or LGPL, version 2.1 or any later versions. This software distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this program. If not, see http://www.gnu.org/licenses/.
