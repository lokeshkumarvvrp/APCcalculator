/*




*/

#include <apc.h>

int takeNum(char * expr, dig **No1, dig **No2)
{

	/*local variable declaration*/
	int idx = strlen (expr) - 1;
	char operator, buff[4] = {'0' , '0', '0', '0'};
	int slice_flag = 0, op_flag = 0, sum = 0;
	int jdx = 3, minus_flag = 0, high_flag;
	dig *Result = NULL;
    char minus1_flag;

	while (idx >= 0)
	{

		if (idx == 0)
		{
			if ( expr[idx] == '-')
			{
				minus_flag = 1;
				break;
			}
		}
		/*if the character is not an operator*/
		if (expr[idx] != '+' &&expr[idx] != '-' && expr[idx] != '*' && expr[idx] != '/' && expr[idx] != '%' && expr[idx] != '^')
		{
			if (slice_flag == 4)
			{

				/*performing atoi on variable 1*/
				if (op_flag == 0)
				{
					sum = atoi(buff);
					dl_insert_first(No1, sum);
				}

				/*performing atoi on variable 2*/
				if (op_flag == 1)
				{
					sum = atoi(buff);
					dl_insert_first(No2, sum);
				}

				slice_flag = 0;

				/*moving 4 characters in to a buffer*/
				for (jdx = 0; jdx < 4; jdx++)
					buff[jdx] = '0';

				jdx = 3;

			}

			buff[jdx] = expr[idx];
			--jdx;
			++slice_flag;

		}

		/*if the character is an operator*/
		else
		{

			if (slice_flag != 0)
			{
				sum = atoi(buff);
				dl_insert_first(No1, sum);
			}

			operator = expr[idx];
			op_flag = 1;
			slice_flag = 0;

			for (jdx = 0; jdx < 4; jdx++)
				buff[jdx] = '0';

			jdx = 3;
		}

		--idx;
	}

	sum = atoi(buff);
	dl_insert_first(No2, sum);
/*
	/*printing No1
	("\nNo1 : ");
	dl_print_list(*No2);
	/*printing No2
	printf("\nNo2 : ");
	dl_print_list(*No1);
*/
	/*calling addition function block for + and - operators*/
	if (operator == '+' || operator == '-')

	{

		/*if op is -, check for greater num and swap*/
        if(operator == '-' && minus_flag == 1)
        {
            minus1_flag = '-';
            operator = '+';
            Result = eval_sum(No1, No2, operator);
        }

		if (operator == '-' && minus_flag == 0)
		{
			high_flag = check_greater(No1, No2);
			//printf("\nhigh = %d\n", high_flag);
		}
		if( high_flag == 100)
		{
			Result = eval_sum(No2, No1, operator);
		}
		else
		{
			Result = eval_sum(No1, No2, operator);
		}

        if(minus1_flag == '-')
            printf("\nResult = -");

		if (operator == '+' && minus1_flag != '-')
			printf("\nResult = ");


		if (operator == '-')
		{

			/*if the 1st num is less than 2nd num, print - sign*/
			if (high_flag == 1)
				printf("\nResult = -");

			else
				printf("\nResult = ");

		}

		dl_print_list(Result);
		printf("\n");
	}

	/*if the operator is "*"*/
	if (operator == '*')
	{
		Result = eval_mul(No1, No2, operator);
		printf("\nResult : ");
		dl_print_list(Result);
	}

	/*if the operator is "/"*/
	if (operator == '/')
	{
		int count = eval_div(No1, No2, operator);
		printf("\nResult is %d\n", count);
	}

	/*if the operator is "%"*/
	if (operator == '%')
	{
		eval_div(No1, No2, operator);
	}

	
}





