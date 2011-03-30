/* Is a game to play boat battleship using network
    Copyright (C) 2004  <pedro.fraca@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/
#define longEst 1
class box
{
	int status;
	public: 
	 box (void)  {changeStatus(0);};

		void changeStatus(int a) {status=a;}
		int  returnStatus()
		{
			return(status);
		};
};


