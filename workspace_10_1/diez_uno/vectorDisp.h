/*
 * vectorDisp.h
 *
 *  Created on: 22/05/2015
 *      Author: barfelix
 */

#ifndef VECTORDISP_H_
#define VECTORDISP_H_
#include "bundleEDA.h"

typedef  HashMap<int,float> tVectorDisp;

tVectorDisp suma (const tVectorDisp& a, const tVectorDisp& b )
{
	tVectorDisp unReturn;
	tVectorDisp::ConstIterator unIterador=a.cbegin();
	tVectorDisp::ConstIterator unFin=a.cend();

	while (unIterador!=unFin)
	{
		int unaClave=unIterador.key();
		if (b.contains(unaClave))
			unReturn.insert(unaClave,unIterador.value()+b.find(unaClave).value());
		else
			unReturn.insert(unaClave,unIterador.value());
	}

	unIterador=b.cbegin();
	unFin=b.cend();
	while (unIterador!=unFin)
	{
		int unaClave=unIterador.key();
		if(!unReturn.contains(unaClave))
			unReturn.insert(unaClave,unIterador.value());
	}

	return unReturn;
}

tVectorDisp escalar  (const tVectorDisp& a, const tVectorDisp& b )
{
	tVectorDisp unReturn;
	tVectorDisp::ConstIterator unIterador=a.cbegin();
	tVectorDisp::ConstIterator unFin=a.cend();
	while (unIterador!=unFin)
		{
			int unaClave=unIterador.key();
			if (b.contains(unaClave))
				unReturn.insert(unaClave,unIterador.value()*b.find(unaClave).value());
		}


	return unReturn;
}

#endif /* VECTORDISP_H_ */
