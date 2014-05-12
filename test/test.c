/*
 * test.c
 *
 * Создал А.В. Колтаков
 */

#include <stdio.h>
#include <string.h>
#include "../include/_pargresql_library.h"

void test();

int main(int argc, char **argv)
{
	_pargresql_InitLib();
	int i=0;
	do
	{
		test();
		i++;
	}while(i!=10);
	_pargresql_FinalizeLib();
	return 0;
}

void test()
{
	int msgSize, msg, flag, i;
	_pargresql_request_t rqst;

	msg = 777;//_pargresql_GetNode();
	
	for (i = 0; i < _pargresql_GetNodesCount(); i++) {
		_pargresql_ISend(i, 1, sizeof(msg), &msg, &rqst);

		do {
			_pargresql_Test(&rqst, &flag);
		} while (flag != 1);

		printf("Sent \"%d\" to %d node\n", msg, i);
	}
	
	for (i = 0; i < _pargresql_GetNodesCount(); i++) {
		do {
			_pargresql_IProbe(i, 1, &flag, &msgSize);
		} while (flag != 1);

		printf("Size: %d\n", msgSize);

		_pargresql_IRecv(i, 1, msgSize, &msg, &rqst);

		do {
			_pargresql_Test(&rqst, &flag);
		} while (flag != 1);

		printf("Recived \"%d\" from %d node\n", msg, i);
	}
}
