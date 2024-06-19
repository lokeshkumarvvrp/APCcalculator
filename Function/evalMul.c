/*




*/

#include <apc.h>

dig *eval_mul(dig **No1, dig **No2, char operator)
{

	/*local variable declaration*/
	dig *Result1 = NULL, *Result2 = NULL, *ptr1 = *No1, *ptr2 = *No2, *last;
	int idx = 0, carry = 0, result, num, sum, flag = 0, jdx;

	dl_insert_first(&Result2, 0);

	/*moving the pointer to the last node*/
	while(ptr1->nextD != NULL)
	{
		ptr1 = ptr1->nextD;
	}


	/*moving the pointer to the last node*/
	while(ptr2->nextD != NULL)
	{
		ptr2 = ptr2->nextD;
	}

	last = ptr2;

	while (ptr1 != NULL)
	{

		while (ptr2 != NULL)
		{

			/*appending zeros*/
			if (ptr2->nextD == NULL)
			{
				for (jdx = 0; jdx < (idx); jdx++)
				{
					dl_insert_first(&Result1, 0);
				}
			}

			/*performing multiplication*/
			result = (ptr1->cur * ptr2->cur) + carry;

			flag = 0;


			/*checking for over flow*/
			if (result > 999999999)
			{
				num = result;
				result = num % 100000000;
				carry = num / 100000000;
				flag = 1;
			}

			if (flag == 0)
				carry = 0;

			dl_insert_first(&Result1, result);

			ptr2 = ptr2->prevD;

		}

		if (carry != 0)
		{
			dl_insert_first(&Result1, carry);

		}

		/*calling addition function block*/
		Result2 = eval_sum(&Result1, &Result2, '+');
		Result1 = NULL;
		ptr1 = ptr1->prevD;
		ptr2 = last;
		carry = 0;
		++idx;
	}


	return Result2;
}



