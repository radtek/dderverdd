/**
 * Copyright (C) 2017-2018 IQIYI
 * All rights reserved.
 *
 * AUTHOR(S)
 *   Zheng Shuxin
 *   E-mail: zhengshuxin@qiyi.com
 * 
 * VERSION
 *   Tue 22 Aug 2017 11:20:34 AM CST
 */

#pragma once
#include "../acl_cpp_define.hpp"
#if !defined(_WIN32) && !defined(_WIN64)
# include <pthread.h>
# ifndef	acl_pthread_cond_t
#  define	acl_pthread_cond_t	pthread_cond_t
# endif
#else
struct acl_pthread_cond_t;
#endif

namespace acl {

class thread_mutex;

/**
 * �߳���������
 */
class ACL_CPP_API thread_cond
{
public:
	/**
	 * ���췽��
	 * @param mutex {thread_mutex*} ���ò����� NULL ʱ���ڲ��Զ����ø��߳�����
	 *  �����ڲ������߳���
	 */
	thread_cond(thread_mutex* mutex = NULL);
	~thread_cond(void);

	/**
	 * �ȴ��߳�������������
	 * @param microseconds {long long} �ȴ��������������ĳ�ʱʱ��(΢�뼶)
	 *   > 0 ʱ��ʾ�ȴ���ʱ��ʱ��
	 *   == 0�����ȴ�
	 *   < 0 ��һֱ�ȴ�ֱ��������������
	 * @param locked {bool} ���������������߳����ǿ�ʱ���ò�����ʾ�ⲿ
	 *  ������߳����Ƿ��Ѿ����ⲿ��������ס������Ѿ�����ס�����ڲ�����
	 *  �ٶԹ����д�����ⲿ�������������ڲ���������ⲿ������������ǰ
	 *  �ٽ��ⲿ�������⣬���������������߳���Ϊ��ʱ���ڲ����Զ��ȼ���
	 *  ��������������ǰ�ٽ��ڲ���
	 * @return {bool} ���� true ��ʾ�������������������ʾ��ʱ��û��֪ͨ
	 */
	bool wait(long long microseconds = -1, bool locked = false);

	/**
	 * ֪ͨһ���򼸸��ȴ����߳����������ϵ��̣߳���ʾ���������ͽ�
	 * @return {bool} ���� false ��ʾ֪ͨʧ��
	 */
	bool notify(void);

	/**
	 * ֪ͨ���еȴ����߳����������ϵ��̣߳���ʾ���������ͽ�
	 * @return {bool} ���� false ��ʾ֪ͨʧ��
	 */
	bool notify_all(void);

	/**
	 * �������߳����������󶨵��̻߳�����
	 * @return {thread_mutex&}
	 */
	thread_mutex& get_mutex(void) const;

	/**
	 * ���ϵͳ���͵��߳�������������
	 * @return {acl_pthread_cond_t*}
	 */
	acl_pthread_cond_t* get_cond(void) const;

private:
	thread_mutex* mutex_;
	thread_mutex* mutex_internal_;
	acl_pthread_cond_t* cond_;

	bool block_wait(bool locked);
	bool timed_wait(long long microseconds, bool locked);
};

} // namespace acl