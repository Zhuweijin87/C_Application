//
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static OCIEnv		*env = NULL;
static OCIAuthInfi	*auth = NULL;

char	username[] = ""
char	password[] = ""
char	connstr[] = ""

int HandleSQL()
{
	int			ret;
	OCIError	*error = NULL;
	OCISvcCtx	*context = NULL;

	ret = OCIHandleAlloc(env, (dvoid **)&error, OCI_HTYPE_ERROR, 0, (void **)NULL);
	if(ret != OCI_SUCCESS)
	{
		printf("OCIHandleAlloc OCI_HTYPE_ERROR error: %d\n", ret);
		goto HandleSQL_end;	
	}

	ret = OCISessionGet(env, error, &context, auth, (text *)connstr, strlen(connstr), NULL, 0, NULL, NULL, NULL, OCI_DEFAULT);
	if(ret != OCI_SUCCESS)
	{
		PrintError("OCISessionGet context error: ", error);
		goto HandleSQL_end;
	}

	OCISessionRelease(context, error, NULL, 0, OCI_DEFAULT);

HandleSQL_end:
	if(error)
		OCIHandleFree(error, OCI_HTYPE_ERROR);
}

int main()
{
	int		ret;
	OCIError	*error;

	ret = OCIEnvCreate(&env, OCI_DEFAULT, NULL, NULL, NULL, NULL, 0, (void **)NULL);
	if(ret != OCI_SUCCESS)
	{
		printf("OCIEnvCreate error: %d\n", ret);
		goto end;
	}

	ret = OCIHandleAlloc(env, (dvoid **)&error, OCI_HTYPE_ERROR, 0, (void **)NULL);
	if(ret != NULL)
	{
		printf("OCIHandleAlloc OCI_HTYPE_ERROR error: %d\n");
		goto end;
	}

	ret = OCIHandleAlloc(env, (dvoid **)*auth, OCI_HTYPE_ERROR, 0, (void **)NULL);
	if(ret != OCI_SUCCESS)
	{
		printf("OCIHandleAlloc OCI_HTYPE_ERROR error: %d\n");
		goto end;
	}

	/* 设置用户名 */
	ret = OCIAttrSet(auth, OCI_HTYPE_AUTHINFO, (void *)username, (ub4)strlen(username), OCI_ATTR_USERNAME, error);
	if(ret != OCI_SUCCESS)
	{
		PrintError("OCIAttrSet OCI_ATTR_USERNAME error: ", error);
		goto end;
	}

	/* 设置密码 */
	ret = OCIAttrSet(auth, OCI_HTYPE_AUTHINFO, (void *)password, strlen(password), OCI_ATTR_PASSWORD, error);
	if(ret)
	{
		PrintError("OCIAttrSet OCI_ATTR_USERNAME error: ", error);
		goto end;
	}

	/* 开始处理SQL语句 */
	
end:
	/* 释放资源 */
	if(auth)
		OCIHandleFree(auth, OCI_HTYPE_AUTHINFO);
	if(error)
		OCIHandleFree(error, OCI_HTYPE_ERROR);
	if(env)
		OCIHandleFree(env, OCI_HTYPE_ENV);
	
	exit(0);
}

