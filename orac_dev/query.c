#include <stdio.h>
#include <stdlib.h>
#include "oci.h"


char	select_sql[] = "select empno, ename from emp";
char	update_sql[] = "";
char	insert_sql[] = "";

void PrintError(char *msg, OCIError *error)
{
    sb4     errCode;
    char    errmsg[100] = {'\0'};
    OCIErrorGet((dvoid *)error, (ub4)1, NULL, &errCode, (text *)errmsg, (ub4)sizeof(errmsg), OCI_HTYPE_ERROR);
    fprintf(stderr, "%s %s\n", msg, errmsg);
}

int query_fetch_by_one(OCISvcCtx *context, OCIError *error)
{
	OCIStmt		*stmt = NULL;
	
	ret = OCIStmtPrepare2(context, &stmt, error, (text *)select_sql, strlen(select_sql), NULL, 0, OCI_NTV_SYNTAX, OCI_DEFAULT);
	if(ret)
	{
		PrintError("OCIStmtPrepare2 error: ", error);
		return -1;
	}	

	/* 绑定输入参数 */
	OCIBind		*bind1 = NULL;
	
	OCIBindByName(stmt, &bind1, error, (text *)"", -1, (void *), sizeof(), SQLT_INT, NULL, NULL, NULL, 0, NULL, OCI_DEFAULT);

	//OCIBinfByName(stmt, &bind1, error, 0, 0, );
	ret = OCIStmtExecute(context, stmt, error, 0, 0, (OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT);
	if(ret != OCI_SUCCESS)
	{
		PrintError("OCIStmtExecute error: ", error);
		return -1;
	}

	/* 定义输出参数 */
	OCIDefineByPos(stmt, &def1, error, 1, (void *)user.userid, sizeof(user.userid), SQLT_STR, NULL, NULL, NULL, OCI_DEFAULT);

	int		done = 0;
	int		status = 0;
	while(!done)
	{
		status = OCIStmtFetch(stmt, error, 1, OCI_FETCH_NEXT, OCI_DEFAULT);
		if(status != OCI_SUCCESS && status != OCI_NO_DATA)
		{
			if(status == OCI_SUCCESS )	
			{
				rows = 1;
			}
		
			if(status == OCI_NO_DATA)
			{
				ret = OCIAttrGet(stmt, OCI_HTYPE_STMT, &rows, NULL, OCI_ATTR_ROWS_FETCHED, error);
				if(ret != OCI_SUCCESS)
					PrintError("OCIAttrGet OCI_HTYPE_STMT: ", error);
				done = 1;
			}
		
			for(i = 0; i<rows; i++)
			{
				/* 打印查询数据 */
				printf("");
			}
		}
		else
		{
			PrintError("Fetch stmt fail, ", error);
			done = 1;
		}
	}

	OCIStmtRelease(stmt, error, NULL, 0, OCI_DEFAULT);

	return 0;
}

int query_fetch_by_multi(OCISvcCtx *context, OCIError *error)
{
	int			ret;
	
	OCIStmt		*stmt;
	
	ret = OCIStmtPrepare2(context, &stmt, error, (text *)select_sql, strlen(select_sql), NULL, 0, OCI_NTV_SYNTAX, OCI_DEFAULT);
	if(ret != OCI_SUCCESS)
	{
		PrintError("OCIStmtPrepare2 fail:", error);
		return -1;
	}

	/* 绑定输入参数 */


	ret = OCIStmtExecute(context, stmt, error, 0, 0, (OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT);
	if(ret != OCI_SUCCESS)
	{
		PrintError("OCIStmtExecute fail:", error);
		return -1;
	}

	/* 输出参数定义 */

	int done = 1;
    int rows, i;
    while(done)
    {
        ret = OCIStmtFetch(stmt, error, ARRAY_SIZE, OCI_FETCH_NEXT, OCI_DEFAULT);
        if(ret == OCI_SUCCESS || ret == OCI_NO_DATA)
        {
            if(ret == OCI_SUCCESS)
                rows = ARRAY_SIZE;
            if(ret == OCI_NO_DATA)
            {
                ret = OCIAttrGet(stmt, OCI_HTYPE_STMT, &rows, NULL, OCI_ATTR_ROWS_FETCHED, error);
                if(ret != OCI_SUCCESS)
                    printError("OCIAttrGet, ", error);
                done = 0;
            }
            printf("fetch rows: %d\n", rows);
            for(i=0; i<rows; i++)
            {
                printf("empno:%d, ename:%s, job:%s, mgr:%d, sal:%.2f, comm:%.2f\n", empno[i], ename[i], job[i], mgr[i], sal[i], comm[i]);
			}
		}
		else
        {
            printError("OCIStmtFetch: ", error);
            done = 0;
        }
	}

	OCIStmtRelease(stmt, error, NULL, 0, OCI_DEFAULT);

	return 0;		
}


