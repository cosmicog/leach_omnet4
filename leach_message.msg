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

message node2headMsg
{
    int source;
    int posX;
    int posY;
    bool die;
    double battery;
}

message head2baseMsg
{
    bool die;
    int source;
    int posX;
    int posY;
    string mes;
    int dieCount;
    double totalExpendedEnergy = 0.0; // o round'daki mesajlar ch'de birleşene kadarki harcanan toplam enerji, baza iletilmek üzere toplanır.
}

message broadcastMsg
{
    int posX;
    int posY;
    string color;
    string chFullPath;
}

message littleBroMsg
{
    int posX;
    int posY;
    int chNo;
    int chPosX;
    int chPosY;
    string chFullPath;
    string color;
}

