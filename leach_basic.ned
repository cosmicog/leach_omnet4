//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
network LeachBasic
{
    parameters:
        int numNodes;
        int k;
        double p;
        double eElec;
        double eAmp;
        double eFs;
        double eMp;
        double nodeBatteries;
        double thresholdDist;
        double aggregation;
        double switchPercentage;
        int maxX;
        int maxY;
        int bazX;
        int bazY;

        @display("bgb=290,200,white");

    submodules:
        nd[numNodes]: Node {
            @display("p=10,10");
        }
        base: Base {
            @display("p=250,100;i=device/antennatower,,27;i2=,,61");
            numberOfLiveNodes = numNodes;
        }
}

