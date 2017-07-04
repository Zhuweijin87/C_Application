####################################
#	Linux 线程函数说明
####################################

#1. 线程创建
	int pthread_create(	pthread_t *restrict tidp,  /* 线程ID指针 */
						const pthread_attr_t *restrict attr, /* 线程属性*/
						void *(*start_rtn)(void), /* 所附属的函数 */
						void *restrict arg);	/* 函数参数 */


#2. 等待线程结束：
	int pthread_join(	pthread_t thread,  /* 线程ID */
						void **retval);	/* 存储当前线程返回的数据 */


#3. 线程终止
	void pthread_exit(void* retval);

#4. 线程取消
	int pthread_cancel(pthread_t thread);

#5 获取当前线程Id
	pthread_t pthread_self(void);

#6. 分离当前线程
	int pthread_detach(pthread_t thread);
	
	Linux 下线程有两种： Joinable, Unjoinanle
	joinanle(默认): 当线程函数自己返回退出时或pthread_exit时都不会释放线程所占用堆栈和线程描述符（总计8K多）
	unjoinable: 资源在线程函数退出时或pthread_exit时自动会被释放

	如果线程是joinable, 需要调用 pthread_join() 函数来释放; 而unjoinable 可以在pthread_create时设置，或者调用
	pthread_detach() 函数

#7. 比较线程是否为同一个线程
	int pthread_equal(pthread_t thread1, pthread_t thread2);

#8. 线程锁初始化
	int pthread_mutex_init( pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
	
#9. 线程锁释放
	int pthread_mutex_destroy(pthread_mutex_t *mutex);

#10. 线程加锁
	int pthread_mutex_lock(pthread_mutex_t *mutex);

#11. 线程释放锁
	int pthread_mutex_unlock(pthread_mutex_t *mutex);

#12. 线程条件初始化
	int pthread_cond_init(pthread_cond_t *cond, pthread_mutexattr_t *attr);
