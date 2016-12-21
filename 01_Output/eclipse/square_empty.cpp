/*
 * square_empty.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: porsche
 */
#include "square_empty.h"
#include <iostream>
using namespace std;

void square_empty(int a, int b) {


	int row;
	int column;

	for (row=1; row<=a; row++)
	{

	    for (column=1; column<=b; column++)
	    {
	        if (row == 1 || row ==a )
	        {
	            if (column != b)
	            {
	                cout<<"#";
	            }
	            else
	            {
	            	cout<<"#"<<endl;
	            }
	        }

	        else
	        {
	        	if (column == 1 )
	        	{
	            	cout<<"#";
	        	}
	        	else if (column==b)
	        	{
	            	cout<<"#"<<endl ;
	        	}
	            else
	            {
	        	  cout<<"5";
	          	}
	        }
	    }
	}
}
