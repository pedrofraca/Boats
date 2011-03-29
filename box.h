/*
 *  casillas.h
 *  barquitos
 *
 *  Created by Pedro on 18/03/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */
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


