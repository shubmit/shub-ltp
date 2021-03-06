/*
* Copyright (c) Bull S.A.  2007 All Rights Reserved.
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of version 2 of the GNU General Public License as
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it would be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* Further, this software is distributed without any warranty that it is
* free of the rightful claim of any third person regarding infringement
* or the like.  Any license provided herein, whether implied or
* otherwise, applies only to this software file.  Patent licenses, if
* any, provided herein do not apply to combinations of this program with
* other software, or any other product whatsoever.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
* History:
* Created by: Cyril Lacabanne (Cyril.Lacabanne@bull.net)
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <tirpc/rpc/rpc.h>
#include <tirpc/netconfig.h>
#include <netinet/in.h>
#include <tirpc/rpc/svc.h>
#include <errno.h>

//Standard define
#define PROCNUM 1
#define VERSNUM 1

//Sys define
#define ADDRBUFSIZE 100

int main(int argn, char *argc[])
{
	//Program parameters : argc[1] : HostName or Host IP
	//					   argc[2] : Server Program Number
	//					   other arguments depend on test case

	//run_mode can switch into stand alone program or program launch by shell script
	//1 : stand alone, debug mode, more screen information
	//0 : launch by shell script as test case, only one printf -> result status
	int run_mode = 0;
	int test_status = 1; //Default test result set to FAILED
	int progNum = atoi(argc[2]);
    CLIENT *client = NULL;
	struct netconfig *nconf = NULL;
	struct netbuf svcaddr;
    char addrbuf[ADDRBUFSIZE];
	bool_t rpcb_rslt;

	//Initialization
    if (run_mode)
    {
    	printf("Before creation\n");
		printf("client : %d\n", client);
		printf("nconf : %d\n", nconf);
	}

	nconf = getnetconfigent("udp");
	if (nconf == (struct netconfig *) NULL)
	{
		//syslog(LOG_ERR, "getnetconfigent for udp failed");
		printf("err nconf\n");
		exit(1);
	}

	svcaddr.len = 0;
	svcaddr.maxlen = ADDRBUFSIZE;
	svcaddr.buf = addrbuf;

	if (svcaddr.buf == NULL)
	{
    	/* if malloc() failed, print error messages and exit */
  		return 1;
    }

    //printf("svcaddr reserved (%s)\n", argc[1]);

	if (!rpcb_getaddr(progNum, VERSNUM, nconf,
                               &svcaddr, argc[1]))
    {
    	fprintf(stderr, "rpcb_getaddr failed!!\n");
    	exit(1);
    }
    //printf("svc get\n");

	client = clnt_vc_create(RPC_ANYFD, &svcaddr,
			 				progNum, VERSNUM, 1024, 1024);/**/

	test_status = ((CLIENT *)client != NULL) ? 0 : 1;

	//This last printf gives the result status to the tests suite
	//normally should be 0: test has passed or 1: test has failed
	printf("%d\n", test_status);

	return test_status;
}
